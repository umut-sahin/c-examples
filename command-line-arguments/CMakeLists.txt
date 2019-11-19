add_executable(
    command-line-arguments

    src/main.c
)

set_target_properties(
    command-line-arguments

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(command-line-arguments)
