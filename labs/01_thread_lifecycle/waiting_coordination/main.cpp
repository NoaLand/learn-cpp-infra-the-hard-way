#include <print>
#include <queue>
#include <thread>
#include <mutex>
#include <vector>

std::mutex task_queue_mutex_;

int main() {
    std::println("start working on waiting and coordination V1");

    std::queue<int> task_queue;
    bool is_producer_done{};
    auto producer = [&task_queue, &is_producer_done](){
        for (size_t task = 0; task < 100; ++task) {
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
                task_queue.push(task);
            }

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }

        {
            std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
            is_producer_done = true;
        }
    };

    auto consumer = [&task_queue, &is_producer_done](){
        while (true) {
            int task{-1};
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};

                if (!task_queue.empty()) {
                    task = task_queue.front();
                    task_queue.pop();
                } else if (is_producer_done) {
                    break;
                } else {
                    continue;
                }
            }

            std::println("consumer is consuming {}", task);
        }
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(2);
    thread_pool.emplace_back(producer);
    thread_pool.emplace_back(consumer);

    for (auto& thread : thread_pool) {
        thread.join();
    }

    return 0;
}
