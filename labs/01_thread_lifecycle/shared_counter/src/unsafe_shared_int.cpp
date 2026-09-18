#include "labs/threads/shared_counter/unsafe_shared_int.h"

#include <print>

namespace cpp_infra_labs::thread::shared_counter {
    void unsafe_shared_int::run() {
        int counter{};
        auto worker = [&counter](std::string name){
            std::println("{} start working", name);
            for (int i = 0; i < 100000; ++i) {
                ++counter;
            }
            std::println("{} stop working", name);
        };
        thread_pool.reserve(worker_names.size());

        for (const auto& name : worker_names) {
            thread_pool.emplace_back(worker, name);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }

        std::println("counter: {}", counter);
    }
}
