#include <print>
#include <semaphore>
#include <thread>

int main() {
    std::binary_semaphore permission{0};

    auto producer = [&permission](){
        std::println("producer is running");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        std::println("data ready");

        permission.release();
    };

    auto consumer = [&permission](){
        std::println("consumer is running");
        permission.acquire();

        std::println("consumer started");

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        std::println("consumer finished");
    };

    auto producer_thread = std::jthread{producer};
    auto consumer_thread = std::jthread{consumer};

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
