
#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../../common/game.h"
#include "../../common/meshObject.h"
#include "orbitCamera.h"

using namespace ld2016;

class HelloDemo : public Game {
    std::shared_ptr<orbitCamera> camera;
public:
    HelloDemo(int argc, char** argv, glm::vec3&& position, glm::quat&& orientation)
            : Game(argc, argv, "Animation Demo"),
              camera(std::make_shared<orbitCamera>(position, orientation))
    {
        setCamera(camera);
    }
};

void main_loop(void* instance) {
    HelloDemo* demo = (HelloDemo*)instance;
    demo->mainLoop();
}

int main(int argc, char** argv) {
    HelloDemo demo(argc, argv, glm::vec3(), glm::quat());

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, (void*)&demo, 0, 1);
#else
    while (1) {
        main_loop(&demo);
        // TODO: Wait for VSync? Or should we poll input faster than that?
    }
#endif

    return EXIT_SUCCESS;
}
