project(palindrome)

add_executable(${PROJECT_NAME} palindrome.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE test_runner)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
