add_executable(
    write-to-console

    src/main.c
)

set_target_properties(
    write-to-console

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(write-to-console)
