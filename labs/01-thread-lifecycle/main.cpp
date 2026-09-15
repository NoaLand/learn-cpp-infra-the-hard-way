#include <latch>
#include <print>
#include <string>
#include <thread>
#include <array>
#include <vector>


void greeting(std::string_view name) {
    std::println("hello from {}", name);
}

int main() {
    std::array<std::string, 3> worker_names{"a", "b", "c"};
    std::vector<std::jthread> thread_pool;

    std::latch work_done{worker_names.size()};

    for (const auto& name : worker_names) {
        thread_pool.emplace_back(std::jthread{[&work_done, name](){
            using namespace std::chrono_literals;
            greeting("worker-" + name);
            work_done.count_down();
            std::this_thread::sleep_for(3s);
            std::println("do more work from worker-{}", name);
        }});
    }

    // Make sure that the code will print worker first and then main
    // solution 1: use join
    // worker.join();

    // solution 2: use latch
    work_done.wait();

    greeting("main");

    return 0;
}
