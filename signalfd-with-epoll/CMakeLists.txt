add_executable(
    signalfd-with-epoll

    src/main.c
)

set_target_properties(
    signalfd-with-epoll

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)

c_examples_target_compile_warnings(signalfd-with-epoll)
