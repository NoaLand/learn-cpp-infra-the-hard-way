#include <chrono>
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

    std::println("Start atomic shared int\n");
    auto atomic_shared_int_start_ = std::chrono::high_resolution_clock::now();
    cpp_infra_labs::thread::shared_counter::atomic_shared_int{}.run();
    auto atomic_shared_int_end_ = std::chrono::high_resolution_clock::now();
    std::println("\nStop atomic shared int\n");

    std::println("Start local reduce\n");
    auto local_reduce_start_ = std::chrono::high_resolution_clock::now();
    cpp_infra_labs::thread::shared_counter::local_reduce{}.run();
    auto local_reduce_end_ = std::chrono::high_resolution_clock::now();
    std::println("\nStop local reduce\n");

    std::println("Unsafe shared int duration {}", std::chrono::duration<double, std::milli>(unsafe_shared_int_end_ - unsafe_shared_int_start_));
    std::println("Mutex per increment duration {}", std::chrono::duration<double, std::milli>(mutex_per_increment_end_ - mutex_per_increment_start_));
    std::println("Atomic shared int duration {}", std::chrono::duration<double, std::milli>(atomic_shared_int_end_ - atomic_shared_int_start_));
    std::println("Local reduce duration {}", std::chrono::duration<double, std::milli>(local_reduce_end_ - local_reduce_start_));

    return 0;
}
