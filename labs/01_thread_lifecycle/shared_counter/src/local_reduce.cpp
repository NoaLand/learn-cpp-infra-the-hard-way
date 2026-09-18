#include "labs/threads/shared_counter/local_reduce.h"

#include <numeric>
#include <vector>

namespace cpp_infra_labs::thread::shared_counter {
    void local_reduce::run() {
        std::vector<int> counter_for_each_thread(worker_names.size());
        auto worker = [&counter_for_each_thread](std::string name, std::size_t index){
            int local_sum{};
            for (int i = 0; i < 100000; ++i) {
                ++local_sum;
            }
            counter_for_each_thread[index] = local_sum;
        };

        thread_pool.reserve(worker_names.size());

        for (std::size_t i = 0; i < worker_names.size(); ++i) {
            thread_pool.emplace_back(worker, worker_names[i], i);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }

        counter = std::accumulate(counter_for_each_thread.begin(), counter_for_each_thread.end(), 0);
    }
}
