cmake_minimum_required(VERSION 3.16)
project(npc_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# Для Windows: не переопределять настройки компилятора MSVC
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основной исполняемый файл
add_executable(npc_demo
    src/main.cpp
    src/npc_system.cpp
)
target_include_directories(npc_demo PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Копируем data/ рядом с exe после каждой сборки
add_custom_command(TARGET npc_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:npc_demo>/data
)

# Тесты
add_executable(npc_tests
    tests/npc_test.cpp
    src/npc_system.cpp
)
target_include_directories(npc_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(npc_tests PRIVATE GTest::gtest_main)

add_custom_command(TARGET npc_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:npc_tests>/data
)

enable_testing()
add_test(NAME npc_tests COMMAND npc_tests)

target_include_directories(npc_demo PRIVATE ${CMAKE_SOURCE_DIR}/third_party)
target_include_directories(npc_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
