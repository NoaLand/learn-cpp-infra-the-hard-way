#include <condition_variable>
#include <mutex>
#include <print>
#include <string>
#include <thread>
#include <array>
#include <vector>

int main() {
    std::mutex worker_mutex_;
    std::condition_variable cv;
    int in_flight{};

    std::array<std::string, 8> worker_names{
        "alpha",
        "beta",
        "charlie",
        "delta",
        "eva",
        "frank",
        "george",
        "henry"
    };

    auto worker = [&worker_mutex_, &cv, &in_flight](std::string name){
        {
            std::unique_lock<std::mutex> lock{worker_mutex_};
            cv.wait(lock, [&in_flight]{
                return in_flight < 3;
            });

            ++in_flight;
            std::println("{} entered, in flight={}", name, in_flight);
        }

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        {
            std::lock_guard<std::mutex> lock_guard{worker_mutex_};
            --in_flight;
            std::println("{} leaving, in flight={}", name, in_flight);
        }

        cv.notify_one();
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(worker_names.size());
    for (const auto& name : worker_names) {
        thread_pool.emplace_back(worker, name);
    }

    for (auto& worker : thread_pool) {
        worker.join();
    }

    return 0;
}
