#include "labs/threads/shared_counter/atomic_shared_int.h"

#include <print>
#include <atomic>

namespace cpp_infra_labs::thread::shared_counter {
    void atomic_shared_int::run() {
        std::atomic<int> counter{};
        auto worker = [&counter](std::string name){
            std::println("{} start working", name);
            for (int i = 0; i < 100000; ++i) {
                counter.fetch_add(1);
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

        std::println("counter: {}", counter.load());
    }
}
