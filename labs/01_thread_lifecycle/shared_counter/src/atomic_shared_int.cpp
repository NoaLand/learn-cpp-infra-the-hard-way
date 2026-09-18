#include "labs/threads/shared_counter/atomic_shared_int.h"

#include <atomic>

namespace cpp_infra_labs::thread::shared_counter {
    void atomic_shared_int::run() {
        thread_pool.reserve(worker_names.size());

        for (const auto& name : worker_names) {
            thread_pool.emplace_back(&atomic_shared_int::worker, this, name);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }
    }

    void atomic_shared_int::worker(std::string name) {
        for (int i = 0; i < run_times; ++i) {
            counter.fetch_add(1);
        }
    }
}
