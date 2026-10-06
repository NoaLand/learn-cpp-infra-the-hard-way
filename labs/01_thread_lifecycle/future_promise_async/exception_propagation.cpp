#include <exception>
#include <future>
#include <print>
#include <stdexcept>
#include <thread>

int main() {
    std::promise<int> p;
    std::future f{p.get_future()};

    auto worker = [&p](){
        std::println("get into worker, working...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        try {
            throw std::runtime_error{"worker calculation error"};
        } catch (...) {
            p.set_exception(std::current_exception());
        }

        std::this_thread::sleep_for(500ms);
        std::println("exiting from worker");
    };

    auto worker_thread = std::jthread{worker};
    try {
        std::println("worker's result is {}", f.get());
    } catch (const std::exception& ex) {
        std::println("exception from worker: {}", ex.what());
    }

    worker_thread.join();

    return 0;
}
