#include <print>
#include <semaphore>
#include <thread>

int main() {
    std::binary_semaphore ping{1};
    std::binary_semaphore pong{0};

    auto player_a = [&ping, &pong](){
        for (int i = 0; i < 5; ++i) {
            ping.acquire();
            std::println("A: ping {}", i + 1);
            pong.release();
        }
    };

    auto player_b = [&ping, &pong](){
        for (int i = 0; i < 5; ++i) {
            pong.acquire();
            std::println("B: pong {}", i + 1);
            ping.release();
        }
    };

    auto a = std::jthread{player_a};
    auto b = std::jthread{player_b};

    a.join();
    b.join();

    return 0;
}
