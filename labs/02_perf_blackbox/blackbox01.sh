#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_FILE="${SCRIPT_DIR}/.blackbox01.cpp"
OUTPUT_FILE="${SCRIPT_DIR}/blackbox01"

cleanup() {
    rm -f "${SOURCE_FILE}"
}

trap cleanup EXIT

cat > "${SOURCE_FILE}" <<'EOF'
#include <array>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

int main() {
    constexpr std::size_t iterations = 250000;

    std::array<char, 64> payload{};
    for (std::size_t i = 0; i < payload.size(); ++i) {
        payload[i] = static_cast<char>('A' + (i % 26));
    }

    std::uint64_t completed = 0;

    for (std::size_t i = 0; i < iterations; ++i) {
        const int fd = ::open("/dev/null", O_WRONLY | O_CLOEXEC);
        if (fd < 0) {
            throw std::runtime_error(std::strerror(errno));
        }

        const auto written =
            ::write(fd, payload.data(), payload.size());

        if (written != static_cast<ssize_t>(payload.size())) {
            const int saved_errno = errno;
            ::close(fd);
            throw std::runtime_error(std::strerror(saved_errno));
        }

        if (::close(fd) != 0) {
            throw std::runtime_error(std::strerror(errno));
        }

        ++completed;
    }

    std::cout << "completed=" << completed << '\n';
    return 0;
}
EOF

clang++ \
    -std=c++23 \
    -g \
    "${SOURCE_FILE}" \
    -o "${OUTPUT_FILE}"

echo "Built: ${OUTPUT_FILE}"
echo "Do not inspect the generated source. Start profiling the executable."
