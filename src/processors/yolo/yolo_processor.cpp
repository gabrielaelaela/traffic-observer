#include "yolo_processor.h"

YoloProcessor::YoloProcessor(const std::string& cfg, const std::string& weights, const std::string& names) {
    m_net = cv::dnn::readNetFromDarknet(cfg, weights);
    m_net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    m_net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    std::ifstream file(names);
    std::string line;
    while (std::getline(file, line)) {
        m_classes.push_back(line);
    }
}

void YoloProcessor::process(Frame& frame) {
    cv::Mat img(frame.height, frame.width, CV_8UC3, frame.data.data());
    cv::Mat blob;

    cv::dnn::blobFromImage(img, blob, 1.0 / 255.0, cv::Size(416, 416), cv::Scalar(), true,  false);
    m_net.setInput(blob);
    std::vector<cv::Mat> outputs;
    m_net.forward(outputs, m_net.getUnconnectedOutLayersNames());

    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;
    std::vector<int> classIds;
    
    for (auto& output : outputs) {
        for (int i = 0; i < output.rows; i++) {

            const float* data = output.ptr<float>(i);

            float objectness = data[4];
            if (objectness < 0.3f) continue;

            int bestClass = -1;
            float bestScore = 0.0f;

            for (int c = 5; c < 85; c++) {
                if (data[c] > bestScore) {
                    bestScore = data[c];
                    bestClass = c - 5;
                }
            }

            float confidence = objectness * bestScore;
            if (confidence < 0.3f) continue;

            int centerX = (int)(data[0] * frame.width);
            int centerY = (int)(data[1] * frame.height);
            int w = (int)(data[2] * frame.width);
            int h = (int)(data[3] * frame.height);

            int x = centerX - w / 2;
            int y = centerY - h / 2;

            boxes.emplace_back(x, y, w, h);
            confidences.push_back(confidence);
            classIds.push_back(bestClass);
        }
    }

    std::vector<int> indices;

    cv::dnn::NMSBoxes(
        boxes,
        confidences,
        0.3f,
        0.4f,
        indices
    );

    frame.detections.clear();

    for (int idx : indices) {
        frame.detections.push_back({
            boxes[idx].x,
            boxes[idx].y,
            boxes[idx].width,
            boxes[idx].height,
            m_classes[classIds[idx]],
            confidences[idx]
        });
    }

    m_tracker.update(frame.detections);
    
}

