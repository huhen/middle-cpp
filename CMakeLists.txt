cmake_minimum_required(VERSION 3.10.0)
project(handbook VERSION 0.1.0 LANGUAGES C CXX)

#clang++ --std=c++20 -O3 -fsanitize=address,undefined -Wall -Wextra -Werror
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

#add_compile_options(-fsanitize=address,undefined -Wall -Wextra -Werror)
#add_link_options(-fsanitize=address,undefined -Wall -Wextra -Werror)
add_compile_options(-fsanitize=address,undefined -Wall -Wextra)
add_link_options(-fsanitize=address,undefined -Wall -Wextra)

add_subdirectory(sprint1)

#include(CTest)
#enable_testing()

#install(TARGETS utils helloworld DESTINATION bin)