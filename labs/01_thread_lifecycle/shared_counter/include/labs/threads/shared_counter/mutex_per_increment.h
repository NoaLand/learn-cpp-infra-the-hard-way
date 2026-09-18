#pragma once

#include "labs/threads/shared_counter/shared_counter.h"

#include <mutex>

namespace cpp_infra_labs::thread::shared_counter {
    struct mutex_per_increment : public shared_counter {
        void run() override;

        int counter{};
    private:
        void worker(std::string name);
        std::mutex increment_mutex;
    };
}
