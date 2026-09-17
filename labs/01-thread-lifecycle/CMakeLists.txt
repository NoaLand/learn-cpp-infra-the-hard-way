add_executable(learn_cpp_the_hard_way_lab_01_latch
    latch.cpp
)
add_executable(cpp:infra::lab::01::latch ALIAS learn_cpp_the_hard_way_lab_01_latch)

add_executable(learn_cpp_the_hard_way_lab_01_notify
    notify.cpp
)
add_executable(cpp:infra::lab::01::notify ALIAS learn_cpp_the_hard_way_lab_01_notify)

add_executable(learn_cpp_the_hard_way_lab_01_sync_points
    sync_points.cpp
)
add_executable(cpp:infra::lab::01::sync_points ALIAS learn_cpp_the_hard_way_lab_01_sync_points)

add_executable(learn_cpp_the_hard_way_lab_01_shared_counter
    shared_counter.cpp
)
add_executable(cpp:infra::lab::01::shared_counter ALIAS learn_cpp_the_hard_way_lab_01_shared_counter)
