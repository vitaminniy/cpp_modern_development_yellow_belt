project(palindrome)

add_executable(${PROJECT_NAME} palindrome.cpp)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
