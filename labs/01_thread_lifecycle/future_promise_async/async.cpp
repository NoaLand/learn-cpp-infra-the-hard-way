#include <print>
#include <future>
#include <thread>

std::string_view get_status(std::future_status status) {
    switch (status) {
    case std::future_status::ready:
        return "ready";
    case std::future_status::timeout:
        return "timeout";
    case std::future_status::deferred:
        return "deferred";
    }

    return "unknown";
}

void with_default_launch_policy() {
    auto res = std::async([](){
        std::println("{} - start worker", std::this_thread::get_id());
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        return 42;
    });
    using namespace std::chrono_literals;
    auto status = res.wait_for(0s);
    std::println("{} - res status: {}", std::this_thread::get_id(), get_status(status));

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
    using namespace std::chrono_literals;
    auto status = res.wait_for(0s);
    std::println("{} - res status: {}", std::this_thread::get_id(), get_status(status));

    std::println("{} - main doing something", std::this_thread::get_id());
    std::println("{} - get worker output: {}", std::this_thread::get_id(), res.get());
}

void with_deferred_launch_policy() {
    auto res = std::async(std::launch::deferred, [](){
        std::println("{} - start worker", std::this_thread::get_id());
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);

        return 42;
    });
    using namespace std::chrono_literals;
    auto status = res.wait_for(0s);
    std::println("{} - res status: {}", std::this_thread::get_id(), get_status(status));

    std::println("{} - main doing something", std::this_thread::get_id());
    std::println("{} - get worker output: {}", std::this_thread::get_id(), res.get());
}

int main() {
    std::println("with default launch policy");
    with_default_launch_policy();

    std::println("\nwith async launch policy");
    with_async_launch_policy();

    std::println("\nwith deferred launch policy");
    with_deferred_launch_policy();

    return 0;
}
