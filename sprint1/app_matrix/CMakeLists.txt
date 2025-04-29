add_executable(app_matrix
    src/main.cpp
)

# target_link_libraries(app_matrix
#     PRIVATE
#     jemalloc
# )

install(TARGETS app_matrix DESTINATION bin)