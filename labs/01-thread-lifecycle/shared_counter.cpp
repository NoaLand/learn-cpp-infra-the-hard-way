#include <print>
#include <array>
#include <string>
#include <thread>
#include <vector>
#include <latch>

int main() {
    int counter{};

    std::array<std::string, 4> worker_names{"alpha", "beta", "charlie", "delta"};
    std::latch waiting_all_threads_done{worker_names.size()};
    auto worker = [&counter, &waiting_all_threads_done](std::string name){
        std::println("{} start working", name);
        for (int i = 0; i < 100000; ++i) {
            ++counter;
        }
        waiting_all_threads_done.count_down();
        std::println("{} stop working", name);
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(worker_names.size());
    for (const auto& name : worker_names) {
        thread_pool.emplace_back(worker, name);
    }

    waiting_all_threads_done.wait();
    std::println("in the end the counter is: {}", counter);

    return 0;
}
