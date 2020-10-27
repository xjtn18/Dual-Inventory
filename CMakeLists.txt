cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)


project(app)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${app_SOURCE_DIR}/bin)
set(CMAKE_PREFIX_PATH "C:/dev/packages/SDL2-2.0.12;C:/dev/packages/SDL2_image-2.0.5;C:/dev/packages/SDL2_mixer-2.0.4")

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-variable -std=c++17")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -Wl,-subsystem,windows -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 -Wno-unused-parameter")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(include)

# Look in the Lesson0 subdirectory to find its CMakeLists.txt so we can build the executable
# add_subdirectory(app)




add_executable(app 
	src/main.cpp
	src/View.cpp
	src/mySDL.cpp
	src/debug.cpp
	src/Items.cpp
	src/ItemBuffer.cpp
	src/Inventory.cpp
)

target_link_libraries(app ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY})

install(TARGETS app RUNTIME DESTINATION ${BIN_DIR})

