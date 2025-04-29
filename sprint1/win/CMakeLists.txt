
add_executable(app_draft_win
    draft.cpp
)

target_include_directories(app_draft_win PRIVATE ${PROJECT_SOURCE_DIR}/wil/include)
