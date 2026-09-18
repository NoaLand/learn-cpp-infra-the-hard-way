#include "labs/threads/shared_counter/atomic_shared_int.h"

#include <atomic>

namespace cpp_infra_labs::thread::shared_counter {
    void atomic_shared_int::run() {
        auto worker = [&sum = counter](std::string name){
            for (int i = 0; i < 100000; ++i) {
                sum.fetch_add(1);
            }
        };

        thread_pool.reserve(worker_names.size());

        for (const auto& name : worker_names) {
            thread_pool.emplace_back(worker, name);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }
    }
}
