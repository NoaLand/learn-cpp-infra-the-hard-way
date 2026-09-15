#include <latch>
#include <print>
#include <string>
#include <thread>

void greeting(std::string_view name) {
    std::println("hello from {}", name);
}

int main() {
    std::latch work_done{1};

    std::jthread worker = std::jthread([&work_done](){
        greeting("worker");
        work_done.count_down();
    });

    // Make sure that the code will print worker first and then main
    // solution 1: use join
    // worker.join();

    // solution 2: use latch
    work_done.wait();

    greeting("main");

    return 0;
}
