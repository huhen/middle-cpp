
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# set(BOOST_ROOT "/usr/local/boost-1.88.0")
# set(Boost_INCLUDE_DIR "${BOOST_ROOT}/include")
find_package(Boost COMPONENTS system)

if(Boost_FOUND)
    add_executable(app_scope_guard
        src/main.cpp
    )
    target_include_directories(app_scope_guard PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(app_scope_guard ${Boost_LIBRARIES})

    install(TARGETS app_scope_guard DESTINATION bin)
endif()
