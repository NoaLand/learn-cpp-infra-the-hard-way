#include "labs/threads/shared_counter/mutex_per_increment.h"

#include <mutex>

namespace cpp_infra_labs::thread::shared_counter {
    void mutex_per_increment::run() {
        auto worker = [&sum = counter, &mutex = increment_mutex](std::string name){
            for (int i = 0; i < 100000; ++i) {
                std::lock_guard<std::mutex> lock_guard(mutex);
                ++sum;
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
