cmake_minimum_required(VERSION 3.28)
project(myBankOperations)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(test)

add_executable(myBankOperations main.cpp)

set( SOURCE_FILES
        Account.cpp
        Account.h
        MoneyTransfer.cpp
        MoneyTransfer.h
        Manager.cpp
        Manager.h
)

add_library(core ${SOURCE_FILES})
target_link_libraries(myBankOperations core)