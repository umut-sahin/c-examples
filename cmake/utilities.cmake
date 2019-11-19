function(c_examples_target_compile_warnings target)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(
            ${target}

            PRIVATE

            /permissive
            /Wall
            /WX
        )
    else ()
        target_compile_options(
            ${target}

            PRIVATE

            -Wall
            -Wextra
            -Wpedantic
            -Werror
        )
    endif ()
endfunction()
