add_executable(animation
    main.cpp
    )
target_link_libraries(animation
    common
    ${ASSIMP_LIBRARIES}
    )

if(DEFINED ENV{EMSCRIPTEN})
  set(EMSCRIPTEN_FLAGS
      "-s USE_SDL=2"
      "-s USE_BULLET=1"
     )
  string (REPLACE ";" " " EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS}")
  set_target_properties(animation PROPERTIES
      SUFFIX ".html"
      COMPILE_FLAGS "${EMSCRIPTEN_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_FLAGS}"
      )
  install(TARGETS animation
      RUNTIME DESTINATION html
      )
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/animation.js"
      DESTINATION html
      )
else()
target_link_libraries(animation
    ${BULLET_LIBRARIES}
    )
endif()
