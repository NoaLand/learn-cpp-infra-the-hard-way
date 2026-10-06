#include <print>
#include <future>
#include <thread>

int main() {
    std::promise<int> p;
    std::future f{p.get_future()};

    auto worker = [](std::promise<int>&& p){
        std::println("get into worker, working...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        std::this_thread::sleep_for(500ms);
        std::println("exiting from worker");
    };
    auto worker_thread = std::jthread{worker, std::move(p)};

    try {
        std::println("worker's result is {}", f.get());
    } catch (const std::exception& ex) {
        std::println("{}", ex.what());
    }

    worker_thread.join();

    return 0;
}
