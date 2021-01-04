project(split_words)

add_library(${PROJECT_NAME} split.cpp)

enable_testing()

add_executable(${PROJECT_NAME}_test main_test.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE test_runner)
add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
