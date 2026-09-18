#include <print>

#include "labs/threads/shared_counter/unsafe_shared_int.h"


int main() {
    std::println("Start unsafe shared int\n");
    auto unsafe_shared_int_ = cpp_infra_labs::thread::shared_counter::unsafe_shared_int {};
    unsafe_shared_int_.run();
    std::println("\nStop unsafe shared int\n");

    return 0;
}
