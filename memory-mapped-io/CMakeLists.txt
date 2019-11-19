add_executable(
    memory-mapped-io

    src/main.c
)

set_target_properties(
    memory-mapped-io

    PROPERTIES

    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

c_examples_target_compile_warnings(memory-mapped-io)
