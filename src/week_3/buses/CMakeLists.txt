project(buses)

set(
	SRC
	bus_manager.cpp
	query.cpp
	responses.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})
