#include <print>

#include "labs/threads/shared_counter/unsafe_shared_int.h"
#include "labs/threads/shared_counter/mutex_per_increment.h"
#include "labs/threads/shared_counter/atomic_shared_int.h"
#include "labs/threads/shared_counter/local_reduce.h"


int main() {
    std::println("Start unsafe shared int\n");
    auto unsafe_shared_int_ = cpp_infra_labs::thread::shared_counter::unsafe_shared_int{};
    unsafe_shared_int_.run();
    std::println("\nStop unsafe shared int\n");

    std::println("Start mutex per increment\n");
    auto mutex_per_increment_ = cpp_infra_labs::thread::shared_counter::mutex_per_increment{};
    mutex_per_increment_.run();
    std::println("\nStop mutex per increment\n");

    std::println("Start atomic shared int\n");
    auto atomic_shared_int_ = cpp_infra_labs::thread::shared_counter::atomic_shared_int{};
    atomic_shared_int_.run();
    std::println("\nStop atomic shared int\n");

    std::println("Start local reduce\n");
    auto local_reduce_ = cpp_infra_labs::thread::shared_counter::local_reduce{};
    local_reduce_.run();
    std::println("\nStop local reduce\n");

    return 0;
}
