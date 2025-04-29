
add_subdirectory(app_with_mem_leaks)
add_subdirectory(app_with_placement_new)
add_subdirectory(app_matrix)

add_subdirectory(win)

add_executable(app_draft_linux
    draft.cpp
)