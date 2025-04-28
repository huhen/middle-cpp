add_executable(app_with_mem_leaks
    src/main.cpp
)

target_link_libraries(app_with_mem_leaks
    PRIVATE
    jemalloc
)

install(TARGETS app_with_mem_leaks DESTINATION bin)