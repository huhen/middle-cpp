add_executable(app_shared_ptr
    src/main.cpp
)

# target_link_libraries(app_shared_ptr
#     PRIVATE
#     jemalloc
# )

install(TARGETS app_shared_ptr DESTINATION bin)