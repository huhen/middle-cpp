add_executable(app_with_placement_new
    src/main.cpp
)

target_link_libraries(app_with_placement_new
    PRIVATE
    jemalloc
)

install(TARGETS app_with_placement_new DESTINATION bin)