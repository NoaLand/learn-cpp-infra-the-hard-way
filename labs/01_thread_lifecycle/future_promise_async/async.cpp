#include <print>
#include <future>
#include <thread>

void with_default_launch_policy() {
    auto res = std::async([](){
        std::println("{} - start worker", std::this_thread::get_id());
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        return 42;
    });

    std::println("{} - main doing something", std::this_thread::get_id());
    std::println("{} - get worker output: {}", std::this_thread::get_id(), res.get());
}

void with_async_launch_policy() {
    auto res = std::async(std::launch::async, [](){
        std::println("{} - start worker", std::this_thread::get_id());
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        return 42;
    });

    std::println("{} - main doing something", std::this_thread::get_id());
    std::println("{} - get worker output: {}", std::this_thread::get_id(), res.get());
}

void with_defered_launch_policy() {
    auto res = std::async(std::launch::deferred, [](){
        std::println("{} - start worker", std::this_thread::get_id());
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        return 42;
    });

    std::println("{} - main doing something", std::this_thread::get_id());
    std::println("{} - get worker output: {}", std::this_thread::get_id(), res.get());
}

int main() {
    std::println("with default launch policy");
    with_default_launch_policy();

    std::println("\nwith async launch policy");
    with_async_launch_policy();

    std::println("\nwith defered launch policy");
    with_defered_launch_policy();

    return 0;
}
