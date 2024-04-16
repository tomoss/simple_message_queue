#pragma once

#include <queue>
#include <atomic>
#include <string>
#include <mutex>
#include <condition_variable>

class MessageQueue
{
public:
    MessageQueue();
    ~MessageQueue() = default;

    void enqueue(std::string p_message);
    std::string dequeue();
    void abort();

    static const std::string EXIT_MSG;

private:
    std::queue<std::string> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
    std::atomic<bool> m_abort;
};