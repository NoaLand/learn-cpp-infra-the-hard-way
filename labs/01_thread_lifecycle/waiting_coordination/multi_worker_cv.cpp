#include <condition_variable>
#include <cstddef>
#include <queue>
#include <mutex>
#include <thread>
#include <print>

int main() {
    std::queue<int> task_queue;
    bool is_producer_done{};
    std::size_t in_flight{};
    std::mutex task_queue_mutex_;
    std::condition_variable work_cv;
    std::condition_variable monitor_cv;

    auto producer = [&task_queue, &is_producer_done, &task_queue_mutex_, &work_cv, &monitor_cv](){
        for (std::size_t task = 0; task < 100; ++task) {
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
                task_queue.push(task);
            }
            work_cv.notify_one();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }

        {
            std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
            is_producer_done = true;
        }
        work_cv.notify_all();
        monitor_cv.notify_all();
    };

    auto consumer = [&task_queue_mutex_, &work_cv, &monitor_cv, &is_producer_done, &task_queue, &in_flight](std::string name){
        std::size_t working_time{};
        while (true) {
            int task{};
            {
                std::unique_lock<std::mutex> lock{task_queue_mutex_};
                work_cv.wait(lock, [&is_producer_done, &task_queue]{
                    return is_producer_done || !task_queue.empty();
                });

                if (task_queue.empty()) {
                    std::println("{} worked {} times", name, working_time);
                    return;
                }

                task = task_queue.front();
                task_queue.pop();
                ++in_flight;
                ++working_time;
                monitor_cv.notify_one();
            }
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(30ms);
            std::println("{} is consuming: {}", name, task);
            {
                std::lock_guard<std::mutex> lock_guard{task_queue_mutex_};
                --in_flight;
                monitor_cv.notify_one();
            }
        }
    };

    auto monitor = [&task_queue_mutex_, &monitor_cv, &is_producer_done, &task_queue, &in_flight](){
        int old{};

        while (true) {
            {
                std::unique_lock<std::mutex> lock{task_queue_mutex_};
                monitor_cv.wait(lock, [&is_producer_done, &in_flight, &old,&task_queue]{
                    return (is_producer_done && task_queue.empty() && in_flight == 0) || (old != in_flight);
                });

                if (is_producer_done && task_queue.empty() && in_flight == 0) {
                    std::println("[monitor] all work done");
                    return;
                }

                if (old != in_flight) {
                    std::println("[monitor] current working {} tasks", in_flight);
                    old = in_flight;
                }
            }
        }
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(6);
    thread_pool.emplace_back(producer);
    thread_pool.emplace_back(monitor);
    thread_pool.emplace_back(consumer, "alpha");
    thread_pool.emplace_back(consumer, "beta");
    thread_pool.emplace_back(consumer, "charlie");
    thread_pool.emplace_back(consumer, "delta");

    for (auto& thread : thread_pool) {
        thread.join();
    }

    return 0;
}
