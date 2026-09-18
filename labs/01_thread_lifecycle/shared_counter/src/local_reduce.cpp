#include "labs/threads/shared_counter/local_reduce.h"

#include <numeric>
#include <vector>

namespace cpp_infra_labs::thread::shared_counter {
    void local_reduce::run() {
        thread_pool.reserve(worker_names.size());

        std::vector<int> counter_for_each_thread(worker_names.size());
        for (std::size_t i = 0; i < worker_names.size(); ++i) {
            thread_pool.emplace_back(&local_reduce::worker, this, worker_names[i], std::ref(counter_for_each_thread), i);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }

        counter = std::accumulate(counter_for_each_thread.begin(), counter_for_each_thread.end(), 0);
    }

    void local_reduce::worker(std::string name, std::vector<int>& counter_for_each_thread, std::size_t index) {
        int local_sum{};
        for (int i = 0; i < run_times; ++i) {
            ++local_sum;
        }
        counter_for_each_thread[index] = local_sum;
    }
}
