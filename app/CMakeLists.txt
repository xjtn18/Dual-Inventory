project(app)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
# Link this lesson against SDL2 and SDL2_image

add_executable(app 
	src/main.cpp
	src/debug.cpp
	)

target_include_directories(app PUBLIC inc)
target_link_libraries(app ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS app RUNTIME DESTINATION ${BIN_DIR})
