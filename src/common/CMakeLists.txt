add_subdirectory(ecs)

add_library(common STATIC
    camera.cpp
    debug.cpp
    game.cpp
    glError.cpp
    loadCubeMap.cpp
    meshObject.cpp
    perspectiveCamera.cpp
    scene.cpp
    sceneObject.cpp
    shaderProgram.cpp
    shaders.cpp
    shaders.cpp
    transform.cpp
    transformRAII.cpp
    transformStack.cpp
    wasdCamera.cpp
    skyBox.cpp
    )

target_link_libraries(common
    ecs
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(DEFINED ENV{EMSCRIPTEN} AND EMSCRIPTEN_ENABLED)
  set(EMSCRIPTEN_FLAGS
      "-s USE_SDL=2"
     )
  string (REPLACE ";" " " EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS}")
  set_target_properties(common PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_FLAGS}"
      )
else()
  set_property(TARGET common PROPERTY CXX_STANDARD 11)
  set_property(TARGET common PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Convert all of our shaders to C header files
file(GLOB_RECURSE shaders
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.frag"
    )
foreach(shader ${shaders})
  file(RELATIVE_PATH shader_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${shader}")
  string(REPLACE "/" "_" shader_target "${shader_rel}.c")
  get_filename_component(shader_dir "${shader_rel}" DIRECTORY)
  add_custom_target("s_${shader_target}"
      COMMAND xxd -include ${shader_rel} > "${CMAKE_CURRENT_BINARY_DIR}/${shader_target}"
      DEPENDS "${shader}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      )
  add_dependencies(common
      "s_${shader_target}"
      )
endforeach()
