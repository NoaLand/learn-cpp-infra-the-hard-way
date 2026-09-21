#include <condition_variable>
#include <cstddef>
#include <queue>
#include <mutex>
#include <thread>
#include <print>

int main() {
    std::queue<int> task_queue;
    bool is_producer_done{};
    std::mutex task_queue_mutex_;
    std::condition_variable cv;

    auto producer = [&task_queue, &is_producer_done, &task_queue_mutex_, &cv](){
        for (std::size_t task = 0; task < 100; ++task) {
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
                task_queue.push(task);
            }
            cv.notify_one();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }

        {
            std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
            is_producer_done = true;
        }
        cv.notify_all();
    };

    auto consumer = [&task_queue_mutex_, &cv, &is_producer_done, &task_queue](std::string name){
        std::size_t working_time{};
        while (true) {
            int task{};
            {
                std::unique_lock<std::mutex> lock{task_queue_mutex_};
                cv.wait(lock, [&is_producer_done, &task_queue]{
                    return is_producer_done || !task_queue.empty();
                });

                if (task_queue.empty()) {
                    std::println("{} worked {} times", name, working_time);
                    return;
                }

                task = task_queue.front();
                task_queue.pop();
                ++working_time;
            }
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(15ms);
            std::println("{} is consuming: {}", name, task);
        }
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(5);
    thread_pool.emplace_back(producer);
    thread_pool.emplace_back(consumer, "alpha");
    thread_pool.emplace_back(consumer, "beta");
    thread_pool.emplace_back(consumer, "charlie");
    thread_pool.emplace_back(consumer, "delta");

    for (auto& thread : thread_pool) {
        thread.join();
    }

    return 0;
}
