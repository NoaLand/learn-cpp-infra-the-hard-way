#pragma once

#include "labs/threads/shared_counter/shared_counter.h"

namespace cpp_infra_labs::thread::shared_counter {
    struct local_reduce : public shared_counter {
        void run() override;
    };
}
