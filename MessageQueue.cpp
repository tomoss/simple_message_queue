#include "MessageQueue.h"

const std::string MessageQueue::EXIT_MSG = "EXIT_MSG";

MessageQueue::MessageQueue() : m_queue(), m_mutex(), m_cv(), m_abort(false)
{

}

void MessageQueue::enqueue(std::string p_message)
{
    std::lock_guard<std::mutex> l_lock(m_mutex);
    m_queue.push(p_message);
    m_cv.notify_one();
}

std::string MessageQueue::dequeue()
{
    std::unique_lock<std::mutex> l_lock(m_mutex);
    std::string l_result;
    while (m_queue.empty() && !m_abort.load())
    {
        m_cv.wait(l_lock);
    }

    if (m_abort.load())
    {
        l_result = EXIT_MSG;
    }
    else
    {
        l_result = m_queue.front();
        m_queue.pop();
    }
    return l_result;
}

void MessageQueue::abort()
{
    std::lock_guard<std::mutex> l_lock(m_mutex);
    m_abort.store(true);
    m_cv.notify_one();
}