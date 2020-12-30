project(phone_number)

add_library(${PROJECT_NAME} phone_number.cpp)

enable_testing()

add_executable(${PROJECT_NAME}_test phone_number_test.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test PRIVATE test_runner)

add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
