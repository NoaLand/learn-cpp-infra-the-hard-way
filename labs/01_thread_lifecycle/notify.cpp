#include <latch>
#include <print>
#include <array>
#include <vector>
#include <thread>

int main() {
    std::array<std::string, 3> worker_names{"worker-a", "worker-b", "worker-c"};
    std::latch ready{worker_names.size()};
    std::latch go_start{1};
    auto worker = [&ready, &go_start](const auto& name){
        std::println("{}: ready", name);
        ready.count_down();
        go_start.wait();
        std::println("{}: go", name);
    };

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(worker_names.size());
    for (const auto& name : worker_names) {
        thread_pool.emplace_back(worker, name);
    }

    ready.wait();
    std::println("main: go");
    go_start.count_down();

    return 0;
}
