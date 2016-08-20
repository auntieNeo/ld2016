add_library(common STATIC
    scene.cpp
    sceneObject.cpp
    )

if(DEFINED ENV{EMSCRIPTEN})
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
