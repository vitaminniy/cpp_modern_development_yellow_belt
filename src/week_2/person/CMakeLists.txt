project(person)

add_executable(${PROJECT_NAME} person.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE test_runner)

# testing
enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
