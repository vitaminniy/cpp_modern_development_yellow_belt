add_executable(equation equation.cpp)
target_link_libraries(equation PRIVATE test_runner)

enable_testing()
add_test(Equation equation)
