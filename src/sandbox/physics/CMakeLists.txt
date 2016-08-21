add_executable(physics
    main.cpp
    )

if(DEFINED ENV{EMSCRIPTEN} AND DEFINED ENV{EMSCRIPTEN_ENABLED})
  set(EMSCRIPTEN_FLAGS
      "-s USE_SDL=2"
      "-s USE_BULLET=1"
     )
  string (REPLACE ";" " " EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS}")
  set_target_properties(physics PROPERTIES
      SUFFIX ".html"
      COMPILE_FLAGS "${EMSCRIPTEN_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_FLAGS}"
      )
  install(TARGETS physics
      RUNTIME DESTINATION html
      )
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/physics.js"
      DESTINATION html
      )
else()
target_link_libraries(physics
      ${BULLET_LIBRARIES}
      ${SDL2_LIBRARY}
    )
endif()
