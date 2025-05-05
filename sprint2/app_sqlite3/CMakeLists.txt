add_executable(app_sqlite3
    src/main.cpp
)

target_link_libraries(app_sqlite3
    PRIVATE
    sqlite3
)

install(TARGETS app_sqlite3 DESTINATION bin)