#pragma once

#include <array>
#include <string>
#include <vector>
#include <thread>

namespace cpp_infra_labs::thread::shared_counter {
    struct shared_counter {
        std::array<std::string, 4> worker_names{"alpha", "beta", "charlie", "delta"};
        std::vector<std::thread> thread_pool;
        virtual void run() = 0;

        virtual ~shared_counter() = default;
    };
}
