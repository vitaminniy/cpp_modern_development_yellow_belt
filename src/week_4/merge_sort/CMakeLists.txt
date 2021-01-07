project(merge_sort)

add_library(${PROJECT_NAME}
	merge_by_two.cpp
	merge_by_three.cpp
)

enable_testing()

add_executable(by_two_test by_two_test.cpp)
target_link_libraries(by_two_test PRIVATE test_runner)

add_test(${PROJECT_NAME}_by_two by_two_test)

add_executable(by_three_test by_three_test.cpp)
target_link_libraries(by_three_test PRIVATE test_runner)

add_test(${PROJECT_NAME}_by_three by_three_test)
