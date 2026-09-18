#include <chrono>
#include <numeric>
#include <print>

#include "labs/threads/shared_counter/unsafe_shared_int.h"
#include "labs/threads/shared_counter/mutex_per_increment.h"
#include "labs/threads/shared_counter/atomic_shared_int.h"
#include "labs/threads/shared_counter/local_reduce.h"


int main() {
    std::println("Start unsafe shared int\n");
    auto unsafe_shared_int_start_ = std::chrono::high_resolution_clock::now();
    cpp_infra_labs::thread::shared_counter::unsafe_shared_int{}.run();
    auto unsafe_shared_int_end_ = std::chrono::high_resolution_clock::now();
    std::println("\nStop unsafe shared int\n");

    std::println("Start mutex per increment\n");
    auto mutex_per_increment_start_ = std::chrono::high_resolution_clock::now();
    cpp_infra_labs::thread::shared_counter::mutex_per_increment{}.run();
    auto mutex_per_increment_end_ = std::chrono::high_resolution_clock::now();
    std::println("\nStop mutex per increment\n");

    std::println("Start atomic shared int");
    auto atomic_shared_int_start_ = std::chrono::high_resolution_clock::now();
    auto atomic_shared_int_ = cpp_infra_labs::thread::shared_counter::atomic_shared_int{};
    atomic_shared_int_.run();
    auto atomic_shared_int_end_ = std::chrono::high_resolution_clock::now();
    std::println("Stop atomic shared int with counter: {}\n", atomic_shared_int_.counter.load());

    std::println("Start local reduce");
    auto local_reduce_start_ = std::chrono::high_resolution_clock::now();
    auto local_reduce_ = cpp_infra_labs::thread::shared_counter::local_reduce{};
    local_reduce_.run();
    auto local_reduce_end_ = std::chrono::high_resolution_clock::now();
    std::println("Stop local reduce with counter: {}\n", local_reduce_.counter);

    std::println("Unsafe shared int duration {}", std::chrono::duration<double, std::milli>(unsafe_shared_int_end_ - unsafe_shared_int_start_));
    std::println("Mutex per increment duration {}", std::chrono::duration<double, std::milli>(mutex_per_increment_end_ - mutex_per_increment_start_));
    std::println("Atomic shared int duration {}", std::chrono::duration<double, std::milli>(atomic_shared_int_end_ - atomic_shared_int_start_));
    std::println("Local reduce duration {}", std::chrono::duration<double, std::milli>(local_reduce_end_ - local_reduce_start_));

    return 0;
}
