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

    greeting("main");

    return 0;
}
