#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>
#include <thread>

namespace cpp_infra_labs::thread::shared_counter {
    struct shared_counter {
        virtual void run() = 0;

        virtual ~shared_counter() = default;

        std::array<std::string, 4> worker_names{"alpha", "beta", "charlie", "delta"};
        std::vector<std::thread> thread_pool;
        std::size_t run_times{10000000};
        std::size_t expected{run_times * worker_names.size()};
    };
}
