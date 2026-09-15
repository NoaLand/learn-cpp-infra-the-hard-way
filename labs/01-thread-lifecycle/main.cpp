#include <print>
#include <string>
#include <thread>

void greeting(std::string_view name) {
    std::println("hello from {}", name);
}

int main() {
    std::jthread worker = std::jthread([](){
        greeting("worker");
    });

    // Make sure that the code will print worker first and then main
    // solution 1
    worker.join();

    greeting("main");

    return 0;
}
