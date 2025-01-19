# Windowed Application using SDL
## Platform: C++ - SDL2

### Dependencies:
- **SDL:** [https://www.libsdl.org/](https://www.libsdl.org/)
- **Dear ImGui:** [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)

### Build Instructions (Linux only):
1. Clone dependencies 
   ```bash
   git clone https://github.com/g-truc/glm third_party/glm/

   git clone https://github.com/ocornut/imgui third_party/imgui/
   ```
   
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
