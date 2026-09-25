#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_FILE="${SCRIPT_DIR}/.blackbox02.cpp"
OUTPUT_FILE="${SCRIPT_DIR}/blackbox02"

cleanup() {
    rm -f "${SOURCE_FILE}"
}

trap cleanup EXIT

cat > "${SOURCE_FILE}" <<'EOF'
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

int main() {
    using namespace std::chrono_literals;

    std::mutex mutex;
    std::condition_variable cv;
    std::queue<int> queue;
    bool done = false;
    std::size_t completed = 0;

    auto producer = [&] {
        for (int task = 0; task < 240; ++task) {
            {
                std::lock_guard lock{mutex};
                queue.push(task);
            }

            cv.notify_all();
            std::this_thread::sleep_for(3ms);
        }

        {
            std::lock_guard lock{mutex};
            done = true;
        }

        cv.notify_all();
    };

    auto worker = [&] {
        while (true) {
            int task = 0;

            {
                std::unique_lock lock{mutex};

                cv.wait(lock, [&] {
                    return done || !queue.empty();
                });

                if (queue.empty()) {
                    return;
                }

                task = queue.front();
                queue.pop();
            }

            std::this_thread::sleep_for(1ms);

            {
                std::lock_guard lock{mutex};
                ++completed;
            }
        }
    };

    std::jthread producer_thread{producer};

    std::vector<std::jthread> workers;
    workers.reserve(8);

    for (int i = 0; i < 8; ++i) {
        workers.emplace_back(worker);
    }

    producer_thread.join();

    for (auto& worker_thread : workers) {
        worker_thread.join();
    }

    std::cout << "completed=" << completed << '\n';

    return completed == 240 ? 0 : 1;
}
EOF

clang++ \
    -std=c++23 \
    -O2 \
    -g \
    -pthread \
    "${SOURCE_FILE}" \
    -o "${OUTPUT_FILE}"

echo "Built: ${OUTPUT_FILE}"
echo "Do not inspect the generated source. Start profiling the executable."
