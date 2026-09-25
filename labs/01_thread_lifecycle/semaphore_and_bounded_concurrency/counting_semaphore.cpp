#include <mutex>
#include <print>
#include <semaphore>
#include <array>
#include <thread>
#include <vector>

int main() {
    std::counting_semaphore<3> slots{3};
    std::mutex worker_mutex_;
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

    auto worker = [&slots, &worker_mutex_, &in_flight](std::string name){
        slots.acquire();
        {
            std::lock_guard<std::mutex> lock_guard{worker_mutex_};
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
        slots.release();
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
