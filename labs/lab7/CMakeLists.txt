cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME lab7)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (SOURCES 
      main.cpp
      animal.cpp
      animal_counter.cpp
      home_animal_factory.cpp
      wild_animal_factory.cpp
    )


add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# # compile test

set (TEST_SOURCES 
      animal.cpp
      animal_counter.cpp
      home_animal_factory.cpp
      wild_animal_factory.cpp
      animal_test.cpp
    )

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_test ${CONAN_LIBS})