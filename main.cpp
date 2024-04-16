#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include "MessageQueue.h"

int main()
{
    MessageQueue messageQueue;

    auto f1 = std::async(std::launch::async, [&messageQueue]
    {
        for(int i = 0; i < 5; i++)
        {
            messageQueue.enqueue("Hello " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        messageQueue.abort();
    });

    auto f2 = std::async(std::launch::async, [&messageQueue]
    {
        while(1)
        {
            std::string result = messageQueue.dequeue();
            std::cout << "message received: " << result << std::endl;
            if (MessageQueue::EXIT_MSG == result)
            {
                break;
            }
        }
    });

    return 0;
}