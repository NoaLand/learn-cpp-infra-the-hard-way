#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <print>
#include <queue>
#include <thread>

int main() {
    std::mutex task_queue_mutex_;

    std::queue<int> task_queue;
    bool is_producer_done{};
    std::condition_variable cv;

    auto producer = [&task_queue, &task_queue_mutex_, &is_producer_done, &cv](){
        for (std::size_t task = 0; task < 100; ++task) {
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
                task_queue.push(task);
            }
            cv.notify_all();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }

        {
            std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
            is_producer_done = true;
        }
        cv.notify_all();
    };

    auto consumer = [&task_queue_mutex_, &is_producer_done, &task_queue, &cv](){
        while (true) {
            int task{};

            {
                std::unique_lock<std::mutex> lock{task_queue_mutex_};
                cv.wait(lock, [&is_producer_done, &task_queue]{
                    return is_producer_done || !task_queue.empty();
                });

                if (task_queue.empty()) {
                    break;
                }

                task = task_queue.front();
                task_queue.pop();
            }

            std::println("consumer is consuming {}", task);
        }
    };

    std::jthread producer_thread_{producer};
    std::jthread consumer_thread_{consumer};

    producer_thread_.join();
    consumer_thread_.join();

    return 0;
}
