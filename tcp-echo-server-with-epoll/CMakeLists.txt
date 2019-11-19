add_executable(
    tcp-echo-server-with-epoll

    src/main.c
)

set_target_properties(
    tcp-echo-server-with-epoll

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)

c_examples_target_compile_warnings(tcp-echo-server-with-epoll)
