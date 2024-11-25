cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp
        testAccounts.cpp
        testManager.cpp)
add_executable(runBankOperationsTests ${TEST_SOURCE_FILES})
target_include_directories(runBankOperationsTests PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(runBankOperationsTests gtest gtest_main core)