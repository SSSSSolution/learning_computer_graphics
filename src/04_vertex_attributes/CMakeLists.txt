aux_source_directory(. SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable (04_vertex_attributes ${SRC_LIST})

set(COMMON_LIBS sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread)
target_link_libraries(04_vertex_attributes ${COMMON_LIBS})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

