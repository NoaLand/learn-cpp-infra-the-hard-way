#include <barrier>
#include <print>
#include <string>
#include <array>
#include <vector>
#include <thread>

int main() {
    std::array<std::string, 3> worker_names = {"worker-a", "worker-b", "worker-c"};
    auto on_completion = []() noexcept {
        static auto stage = "go\n";
        std::println("main: {}", stage);
    };

    std::barrier sync_point{worker_names.size(), on_completion};

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(worker_names.size());
    for (const auto& name : worker_names) {
        thread_pool.emplace_back(
            [&sync_point](std::string name){
                std::println("{}: ready", name);

                sync_point.arrive_and_wait();

                std::println("{}: working", name);
            },
            name
        );
    }

    return 0;
}
