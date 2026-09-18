add_executable(learn_cpp_the_hard_way_lab_01_shared_counter
    src/shared_counter.cpp
    src/unsafe_shared_int.cpp
)

target_include_directories(learn_cpp_the_hard_way_lab_01_shared_counter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(cpp:infra::lab::01::shared_counter ALIAS learn_cpp_the_hard_way_lab_01_shared_counter)
