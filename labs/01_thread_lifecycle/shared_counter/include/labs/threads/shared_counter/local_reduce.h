#pragma once

#include "labs/threads/shared_counter/shared_counter.h"

#include <vector>

namespace cpp_infra_labs::thread::shared_counter {
    struct local_reduce : public shared_counter {
        void run() override;

        int counter{};
    private:
        void worker(std::string name, std::vector<int>& counter_for_each_thread, std::size_t index);
    };
}
