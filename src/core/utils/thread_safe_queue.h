#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = delete;
    explicit ThreadSafeQueue(size_t maxSize) : m_maxSize(maxSize) {}

    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

    void push(T value) {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_cvPush.wait(lock, [this](){return m_queue.size() < m_maxSize || m_stopped;});
        if (m_stopped) return;

        m_queue.push(std::move(value));
        lock.unlock();
        m_cvPop.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_cvPop.wait(lock, [this](){return !m_queue.empty() || m_stopped;});
        if(m_queue.empty()) return false;

        value = std::move(m_queue.front());

        m_queue.pop();
        lock.unlock();
        m_cvPush.notify_one();
        return true;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_stopped = true;
        }
        
        m_cvPush.notify_all();
        m_cvPop.notify_all();
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cvPush;
    std::condition_variable m_cvPop;
    bool m_stopped = false;
    size_t m_maxSize;
};