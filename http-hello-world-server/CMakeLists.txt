add_executable(
    http-hello-world-server

    src/main.c
)

set_target_properties(
    http-hello-world-server

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)

c_examples_target_compile_warnings(http-hello-world-server)
