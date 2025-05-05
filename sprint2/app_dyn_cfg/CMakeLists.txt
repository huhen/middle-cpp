add_executable(app_dyn_cfg
    src/main.cpp
)

# target_link_libraries(app_dyn_cfg
#     PRIVATE
#     jemalloc
# )

install(TARGETS app_dyn_cfg DESTINATION bin)