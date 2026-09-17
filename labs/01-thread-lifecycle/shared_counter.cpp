#include <print>
#include <array>
#include <string>
#include <thread>
#include <vector>

int main() {
    int counter{};

    std::array<std::string, 4> worker_names{"alpha", "beta", "charlie", "delta"};
    auto worker = [&counter](std::string name){
        std::println("{} start working", name);
        for (int i = 0; i < 100000; ++i) {
            ++counter;
        }
        std::println("{} stop working", name);
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(worker_names.size());
    for (const auto& name : worker_names) {
        thread_pool.emplace_back(worker, name);
    }

    for (auto& thread : thread_pool) {
        thread.join();
    }

    std::println("in the end the counter is: {}", counter);

    return 0;
}
