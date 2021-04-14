cmake_minimum_required(VERSION 3.0)

project(visualisation)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

set(SOURCES
  src/image_DXT.c
  src/image_helper.c
  src/SOIL.c
  src/stb_image_aug.c
  src/graph.cpp
  src/vertex.cpp
  src/edge.cpp
  src/number_pool.cpp
  src/gl_context.cpp
  src/framework.cpp
  src/window.cpp
  src/visualisation.cpp
  src/renderer.cpp
  src/graph_renderer.cpp
  src/gui_renderer.cpp
  src/generic_shader.cpp
  src/vertex_buffer.cpp
  src/camera.cpp
  src/input_dispositor.cpp
  src/font_loader.cpp
  src/font_renderer.cpp
  src/font.cpp
  src/texture.cpp
  src/tileset.cpp
  src/gui.cpp
  src/button.cpp
  src/log_window.cpp
  src/textfield.cpp
  src/query_box.cpp
  src/wire_square_template.cpp
  src/graph_helpers.cpp
  src/graph_algorithm.cpp
  src/kruskal.cpp
  src/dijkstra.cpp
  src/bfs.cpp
  src/dfs.cpp
  src/biparite.cpp
)

set(INCLUDES
  inc/number_pool.hpp
  inc/graph.hpp
  inc/vertex.hpp
  inc/edge.hpp
  inc/color.hpp
  #kaniec testow
  inc/gl_context.hpp
  inc/event.hpp
  inc/event_handler.hpp
  inc/event_handler_registrar.hpp
  inc/event_sink.hpp
  inc/window_event_dispatcher.hpp
  inc/framework.hpp
  inc/window.hpp
  inc/application.hpp
  inc/visualisation.hpp
  inc/renderer.hpp
  inc/graph_renderer.hpp
  inc/gui_renderer.hpp
  inc/generic_shader.hpp
  inc/vertex_buffer.hpp
  inc/camera.hpp
  inc/input_dispositor.hpp
  inc/font_loader.hpp
  inc/font_renderer.hpp
  inc/font.hpp
  inc/texture.hpp
  inc/tileset.hpp
  inc/gui.hpp
  inc/widget.hpp
  inc/gui_brush.hpp
  inc/button.hpp
  inc/log_window.hpp
  inc/textfield.hpp
  inc/query_box.hpp
  inc/binary_deserializer.hpp
  inc/wire_square_template.hpp
  inc/gui_event_dispatcher.hpp
  inc/game_event_dispatcher.hpp
  inc/floating_element.hpp
  inc/graph_helpers.hpp
  inc/graph_algorithm.hpp
  inc/kruskal.hpp
  inc/dijkstra.hpp
  inc/bfs.hpp
  inc/dfs.hpp
  inc/biparite.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp ${INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE inc ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${OPENGL_LIBRARIES} GLEW::GLEW)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLM_ENABLE_EXPERIMENTAL) #glm 2d transforms are marked as experimental

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/rsrc
  ${CMAKE_CURRENT_BINARY_DIR}/rsrc
)
