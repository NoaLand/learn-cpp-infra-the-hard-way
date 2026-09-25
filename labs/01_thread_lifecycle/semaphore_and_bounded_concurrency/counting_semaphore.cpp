#include <mutex>
#include <print>
#include <semaphore>
#include <array>
#include <thread>
#include <vector>

template<typename T>
concept semaphore = requires (T& slots) {
    { slots.acquire() };
    { slots.release() };
};

template<semaphore T>
class slots_guard {
public:
    explicit slots_guard(T& slots) : slots_{slots} {
        slots.acquire();
    }

    slots_guard(const slots_guard&) = delete;
    slots_guard& operator= (const slots_guard&) = delete;

    ~slots_guard() {
        slots_.release();
    }

private:
    T& slots_;
};

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
        slots_guard guard{slots};
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
