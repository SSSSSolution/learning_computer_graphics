cmake_minimum_required (VERSION 2.8)
project (learning_computer_graphics)

include_directories(${PROJECT_SOURCE_DIR}/src/base)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")

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
add_subdirectory(src/12_light_source)
add_subdirectory(src/13_diffuse_light)
add_subdirectory(src/14_material)
add_subdirectory(src/15_lighting_maps)
add_subdirectory(src/16_light_casters)
add_subdirectory(src/17_multiple_light)
add_subdirectory(src/18_load_model)

