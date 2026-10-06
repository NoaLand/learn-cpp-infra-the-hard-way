# Learn C++ Infra the Hard Way

A hands-on lab for learning C++ infrastructure by building, breaking, observing, and measuring real systems.

The focus is on practical C++ infra topics such as:

- Threads and concurrency
- Memory and ownership
- Linux processes and system behaviour
- Build toolchains
- Debugging and profiling
- CPU cache and performance
- I/O and networking

The goal is simple: learn by experiments instead of only reading about concepts.

## Environment

- Ubuntu Server
- C++20/23
- Clang / GCC
- CMake / Ninja
- GDB / LLDB
- perf / strace / valgrind
- Neovim
- Zellij

## Roadmap

### 1. Concurrency & Synchronization
- Thread / jthread lifecycle
- Latch / barrier
- Mutex / atomic
- Condition variable
- Semaphore
- Future / promise / async
- Cancellation with stop_token
- CAS & memory ordering
- Thread pool / executor
- Coroutine fundamentals

### 2. Performance & Profiling
- perf stat / record / report / annotate
- strace
- Benchmark methodology
- Busy-wait vs blocking
- Context switches / scheduling
- Cache locality / false sharing
- Oversubscription / affinity
- Profiling-driven optimization

### 3. Linux Systems Fundamentals
- Process vs thread
- Syscalls
- Futex
- Virtual memory / page faults
- File descriptors
- mmap
- Scheduler basics
- Signals

### 4. Build System, Toolchain & Linking
- CMake target model
- Ninja / compile_commands
- Compile vs link
- Static / shared libraries
- Symbols / name mangling
- ODR / link order
- RPATH / RUNPATH
- Dynamic loading

### 5. Debugging & Binary Inspection
- GDB / LLDB
- nm / objdump / readelf / ldd
- Debug symbols / stripping
- ASan / UBSan / TSan
- LTO / PGO

### 6. Memory & Allocation
- Stack / heap / virtual memory
- Object lifetime
- Placement new
- Alignment
- malloc / new
- Arena / pool allocation
- Fragmentation / locality
- Build a mini allocator
- Benchmark against system allocator

### 7. LLVM / Clang / libc++ / LLDB
- Build llvm-project
- Understand major source layout
- Run targeted libc++ tests
- Learn lit testing
- Trace WG21 / LWG issues into implementation
- Review real upstream PRs
- Make at least one upstream contribution

### 8. Infra Integration
- Blocking / bounded queue
- Scoped resource guards
- Task abstraction
- Thread pool
- Executor / scheduler
- Cancellation
- Future-based result propagation
- Build a small integrated C++ runtime

## Lab pinciple

Each lab should be hands-on:

> build → run → measure → inspect → explain → improve

Prefer experiments over memorization.

## License

Licensed under the Apache License 2.0.

*Copyright © 2026 Edward NoaLand*
