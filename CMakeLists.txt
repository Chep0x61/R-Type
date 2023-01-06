cmake_minimum_required(VERSION 3.0)
project(r-type_client)

set(CMAKE_CXX_STANDARD 17)

include(cmake/conan.cmake)
run_conan()
link_directories(${CONAN_LIB_DIRS})
link_libraries(${CONAN_LIBS})
include_directories(SYSTEM "${CONAN_INCLUDE_DIRS}")

if (WIN32)
    add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR} COMMAND copy /y ${PROJECT_BINARY_DIR}/conan/bin/*.dll ${PROJECT_BINARY_DIR})
endif()

file(GLOB CLIENT src/client/*.cpp )

file(GLOB UTILS src/utils/*.cpp)

add_executable(r-type_client
        src/ecs/EntityManager.cpp
        src/ecs/SystemManager.cpp
        src/ecs/ComponentManager.cpp
        src/ecs/Coordinator.cpp
        ${CLIENT}
        ${UTILS})

set(BUILD_SHARED_LIBS FALSE)

project(r-type_server)

add_executable(r-type_server
        src/ecs/EntityManager.cpp
        src/ecs/SystemManager.cpp
        src/ecs/ComponentManager.cpp
        src/ecs/Coordinator.cpp
        src/ecs_entities/Enemy.cpp
        src/network/Network.cpp
        src/network/Protocol.cpp
        src/network/main_network.cpp
        src/server/Server.cpp
        ${UTILS})

include_directories(inc)

project(r-type_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests
        tests/tests.cpp
        tests/ecs/test_ecs.cpp
        )

include_directories(src)

target_link_libraries(runTests gtest_main)