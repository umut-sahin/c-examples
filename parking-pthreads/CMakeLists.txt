add_executable(
    parking-pthreads

    src/main.c
)

set_target_properties(
    parking-pthreads

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(parking-pthreads)

target_include_directories(parking-pthreads PRIVATE include)

target_link_libraries(parking-pthreads Threads::Threads)
