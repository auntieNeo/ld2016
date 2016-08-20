{ stdenv, fetchgit, cmake, assimp, glew, glm, SDL2, SDL2_image, doxygen,
  emscripten, cacert, nodejs, cgdb, lua, lcov, gprof2dot }:

stdenv.mkDerivation rec {
  name = "crepuscule-${version}";
  version = "git";

  buildInputs = [
    cmake glew glm SDL2 SDL2_image doxygen emscripten cacert nodejs cgdb lua
      lcov gprof2dot
  ];
}
