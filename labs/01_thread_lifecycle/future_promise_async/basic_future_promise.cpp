#include <future>
#include <print>
#include <thread>

int main() {
    std::promise<int> p;
    std::future<int> f{p.get_future()};
    auto worker = [&p](){
        std::println("get into worker, working...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        p.set_value(42);

        std::this_thread::sleep_for(500ms);
        std::println("exiting from worker");
    };
    auto worker_thread = std::jthread{worker};

    std::println("waiting in main...");

    f.wait();
    std::println("worker's result is {}", f.get());

    worker_thread.join();

    return 0;
}
