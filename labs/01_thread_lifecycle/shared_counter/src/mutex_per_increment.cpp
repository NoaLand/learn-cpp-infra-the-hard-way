#include "labs/threads/shared_counter/mutex_per_increment.h"

#include <mutex>

namespace cpp_infra_labs::thread::shared_counter {
    void mutex_per_increment::run() {
        thread_pool.reserve(worker_names.size());

        for (const auto& name : worker_names) {
            thread_pool.emplace_back(&mutex_per_increment::worker, this, name);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }
    }

    void mutex_per_increment::worker(std::string name) {
        for (int i = 0; i < run_times; ++i) {
            std::lock_guard<std::mutex> lock_guard(increment_mutex);
            ++counter;
        }
    }
}
