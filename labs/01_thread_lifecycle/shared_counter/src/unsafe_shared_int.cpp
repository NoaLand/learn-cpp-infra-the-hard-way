#include "labs/threads/shared_counter/unsafe_shared_int.h"

namespace cpp_infra_labs::thread::shared_counter {
    void unsafe_shared_int::run() {
        auto worker = [&sum = counter](std::string name){
            for (int i = 0; i < 100000; ++i) {
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
