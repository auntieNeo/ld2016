add_subdirectory("./ecs")

add_executable(hello
        main.cpp
        orbitCamera.cpp orbitCamera.h
        )

target_link_libraries(hello
        common
        ecs
        ${ASSIMP_LIBRARIES}
    )

if(DEFINED ENV{EMSCRIPTEN} AND EMSCRIPTEN_ENABLED)
  set(EMSCRIPTEN_FLAGS
      "-s USE_SDL=2"
      "-s USE_BULLET=1"
     )
  string (REPLACE ";" " " EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS}")
  set_target_properties(hello PROPERTIES
      SUFFIX ".html"
      COMPILE_FLAGS "${EMSCRIPTEN_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_FLAGS}"
      )
  install(TARGETS hello
      RUNTIME DESTINATION html
      )
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/hello.js"
      DESTINATION html
      )
else()
  target_link_libraries(hello
          ${BULLET_LIBRARIES}
          ${SDL2_LIBRARY}
          ${SDL2_IMAGE_LIBRARY}
          ${GLEW_LIBRARY}
          ${OPENGL_LIBRARIES}
          ${ASSIMP_LIBRARY}
          )

  #Copy assets to the build folder.
  add_custom_command(TARGET hello PRE_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/src/sandbox/animation/assets $<TARGET_FILE_DIR:hello>/assets)
endif()
