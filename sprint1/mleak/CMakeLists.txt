add_executable(mleak
    src/main.cpp
)

target_link_libraries(mleak
    PRIVATE
    jemalloc
)

install(TARGETS mleak DESTINATION bin)