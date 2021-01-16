project(database LANGUAGES CXX)

set(SRC
	condition_parser.cpp
	condition_parser_test.cpp
	database.cpp
	date.cpp
	node.cpp
	token.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC test_runner)

enable_testing()
