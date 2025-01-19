#include <SDL2/SDL.h>
#include "Logger.hpp"

#include "App.hpp"

int main(int /*argc*/, char** /*argv[]*/) {

    App app;

    try {
        app.Run();
    } catch (const std::runtime_error& e)  {
        const char* error = e.what();
        ERR("Runtime error has occured", error);
        return -1;
    } catch (const std::exception& e) {
        ERR("Exception has occured", e.what());
        return -2;
    }

    return 0;
}
