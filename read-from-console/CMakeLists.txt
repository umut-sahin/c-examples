add_executable(
    read-from-console

    src/main.c
)

set_target_properties(
    read-from-console

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(read-from-console)
