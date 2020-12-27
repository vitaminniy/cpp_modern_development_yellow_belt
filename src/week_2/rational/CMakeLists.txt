project(rational)
enable_testing()

add_executable(${PROJECT_NAME} rational.cpp)
add_test(${PROJECT_NAME} ${PROJECT_NAME})
