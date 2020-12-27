project(rational)
enable_testing()

add_executable(${PROJECT_NAME} rational.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE test_runner)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
