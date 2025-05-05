cmake_minimum_required(VERSION 3.28.3)
project(handbook VERSION 0.1.0 LANGUAGES C CXX)

#clang++ --std=c++20 -O3 -fsanitize=address,undefined -Wall -Wextra -Werror
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# message(STATUS "Using compiler: ${CMAKE_CXX_COMPILER_ID}")
# message(STATUS "Compiler path: ${CMAKE_CXX_COMPILER}")

# add_compile_options(-fsanitize=address,undefined -Wall -Wextra -Werror)
# add_link_options(-fsanitize=address,undefined -Wall -Wextra -Werror)
# add_compile_options(-fsanitize=address,undefined -Wall -Wextra)
# add_link_options(-fsanitize=address,undefined -Wall -Wextra)
# add_compile_options(-Wall -Wextra)
# add_link_options(-Wall -Wextra)

# Флаги только для Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Стандартные флаги Clang
    # add_compile_options(
    #     -Wall -Wextra -Werror
    #     -O3
    #     -UNDEBUG
    # )

    if(WIN32)
        add_compile_options(
            # /std:c++23
            /W4 /WX
            # /O3 /DNDEBUG
            /DDEBUG
            /D_WIN32_WINNT=0x0A00
            /EHsc
            /Zc:__cplusplus
        )

        add_link_options(/SUBSYSTEM:CONSOLE /INCREMENTAL:NO)
    else()
        add_compile_options(-stdlib=libc++ -O3 -Wall -Wextra)
        add_link_options(-stdlib=libc++)
    endif()

else()
    message(FATAL_ERROR "This project requires Clang compiler.")
endif()


add_subdirectory(sprint1)
add_subdirectory(sprint2)

#include(CTest)
#enable_testing()

#install(TARGETS utils helloworld DESTINATION bin)