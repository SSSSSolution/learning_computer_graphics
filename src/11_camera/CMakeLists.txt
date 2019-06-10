aux_source_directory(. SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable (11_camera ${SRC_LIST})

set(COMMON_LIBS base sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread)
target_link_libraries(11_camera ${COMMON_LIBS})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

