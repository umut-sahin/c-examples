add_executable(
    pthreads

    src/main.c
)

set_target_properties(
    pthreads

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(pthreads)

target_link_libraries(pthreads Threads::Threads)
