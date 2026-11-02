cmake_minimum_required(VERSION 3.16)
project(npc_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(npc_demo
    src/main.cpp
    src/npc_system.cpp
)

# --- Подключаем Google Test через FetchContent ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0  # стабильная версия
)
# Для Windows: отключаем тесты самого GTest, чтобы не мешали
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(npc_tests
    tests/npc_test.cpp
    src/npc_system.cpp   # логика, которую тестируем
)

target_link_libraries(npc_tests PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME NpcTests COMMAND npc_tests)