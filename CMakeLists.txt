cmake_minimum_required (VERSION 2.8)
project (learning_computer_graphics)

include_directories(${PROJECT_SOURCE_DIR}/src/base)

add_subdirectory(src/01_get_start)
add_subdirectory(src/02_compile_shader)
add_subdirectory(src/03_draw_triangle)
add_subdirectory(src/04_vertex_attributes)
add_subdirectory(src/05_passing_data)
add_subdirectory(src/06_tessellation_control_shader)
add_subdirectory(src/07_geometry_shader)
add_subdirectory(src/08_draw_cube)
add_subdirectory(src/09_test_shader)
add_subdirectory(src/10_some_cube)
add_subdirectory(src/11_camera)

