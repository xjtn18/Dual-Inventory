project(Project0)
add_executable(Project0 src/main.cpp)
target_link_libraries(Project0 ${SDL2_LIBRARY})
install(TARGETS Project0 RUNTIME DESTINATION ${BIN_DIR})
