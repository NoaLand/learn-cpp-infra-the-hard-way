#include "labs/threads/shared_counter/shared_counter.h"
#include <cassert>
#include <chrono>
#include <concepts>
#include <functional>
#include <numeric>
#include <print>

#include "labs/threads/shared_counter/unsafe_shared_int.h"
#include "labs/threads/shared_counter/mutex_per_increment.h"
#include "labs/threads/shared_counter/atomic_shared_int.h"
#include "labs/threads/shared_counter/local_reduce.h"

template<typename T>
concept shared_counter = std::derived_from<T, cpp_infra_labs::thread::shared_counter::shared_counter>
    && std::default_initializable<T>;

template<shared_counter T>
std::chrono::duration<double, std::milli> runnable(std::string test_name, const std::function<void(const T&)>& assertion) {
    auto test_case_ = T{};

    auto test_start_ = std::chrono::steady_clock::now();
    test_case_.run();
    auto test_end_ = std::chrono::steady_clock::now();

    assertion(test_case_);

    return std::chrono::duration<double, std::milli>(test_end_ - test_start_);
}

template<shared_counter T>
void benchmark(std::string test_name, const std::function<void(const T&)>& assertion) {
    constexpr std::size_t run_times{10};
    std::vector<std::chrono::duration<double, std::milli>> durations;
    durations.reserve(run_times);
    for (std::size_t i = 0; i < run_times; ++i) {
        durations.emplace_back(runnable(test_name, assertion));
    }

    std::sort(durations.begin(), durations.end());

    std::println("{} min running time is: {}", test_name, durations.at(0));
    std::println("{} max running time is: {}", test_name, durations.at(run_times - 1));
    std::println("{}'s average running time is: {}", test_name, std::accumulate(durations.begin(), durations.end(), std::chrono::duration<double, std::milli>{}) / run_times);
    std::println("{}'s median running time is: {}\n\n", test_name, (durations.at(4) + durations.at(5)) / 2);
}

int main() {
    benchmark<cpp_infra_labs::thread::shared_counter::unsafe_shared_int>("[unsafe shared int]", [](const auto& instance){
        std::println("data race with counter: {}", instance.counter);
    });

    benchmark<cpp_infra_labs::thread::shared_counter::mutex_per_increment>("[mutex per increment]", [](const auto& instance){
        assert(instance.counter == instance.expected);
    });

    benchmark<cpp_infra_labs::thread::shared_counter::atomic_shared_int>("[atomic shared int]", [](const auto& instance){
        assert(instance.counter.load() == instance.expected);
    });

    benchmark<cpp_infra_labs::thread::shared_counter::local_reduce>("[local reduce]", [](const auto& instance){
        assert(instance.counter == instance.expected);
    });

    return 0;
}
