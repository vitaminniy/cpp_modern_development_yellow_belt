project(person)

add_executable(${PROJECT_NAME} person.cpp)

# testing
enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
