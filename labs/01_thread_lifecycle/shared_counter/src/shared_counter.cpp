#include "labs/threads/shared_counter/shared_counter.h"
#include <chrono>
#include <concepts>
#include <functional>
#include <print>

#include "labs/threads/shared_counter/unsafe_shared_int.h"
#include "labs/threads/shared_counter/mutex_per_increment.h"
#include "labs/threads/shared_counter/atomic_shared_int.h"
#include "labs/threads/shared_counter/local_reduce.h"

template<typename T>
concept shared_counter = std::derived_from<T, cpp_infra_labs::thread::shared_counter::shared_counter>
    && std::default_initializable<T>;

template<shared_counter T>
void benchmark(std::string test_name, const std::function<int(const T&)>& get_counter) {
    std::println("Start {}", test_name);
    auto test_start_ = std::chrono::steady_clock::now();
    auto test_case_ = T{};
    test_case_.run();
    auto test_end_ = std::chrono::steady_clock::now();
    std::println("Stop {} with counter: {}", test_name, get_counter(test_case_));
    std::println("{} duration {}\n", test_name, std::chrono::duration<double, std::milli>(test_end_ - test_start_));
}

int main() {
    benchmark<cpp_infra_labs::thread::shared_counter::unsafe_shared_int>("unsafe shared int", [](const auto& instance){
        return instance.counter;
    });

    benchmark<cpp_infra_labs::thread::shared_counter::mutex_per_increment>("mutex per increment", [](const auto& instance){
        return instance.counter;
    });

    benchmark<cpp_infra_labs::thread::shared_counter::atomic_shared_int>("atomic shared int", [](const auto& instance){
        return instance.counter.load();
    });

    benchmark<cpp_infra_labs::thread::shared_counter::local_reduce>("local reduce", [](const auto& instance){
        return instance.counter;
    });

    return 0;
}
