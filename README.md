# Windowed Application using SDL
## Platform: C++ - SDL2

### Dependencies:
- **GLM:** [https://github.com/g-truc/glm](https://github.com/g-truc/glm)
- **SDL:** [https://www.libsdl.org/](https://www.libsdl.org/)
- **Dear ImGui:** [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)
- **STB Image:** [https://github.com/nothings/stb](https://github.com/nothings/stb)
- **Tiny Obj Loader:** [https://github.com/tinyobjloader/tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
- **Vk Bootstrap:** [https://github.com/charles-lunarg/vk-bootstrap](https://github.com/charles-lunarg/vk-bootstrap/blob/master/src/VkBootstrap.cpp)
- **VMA:** [https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
- **{fmt}:** [https://fmt.dev/latest/index.html](https://fmt.dev/latest/index.html)
- **fastGLTF:** [https://github.com/spnda/fastgltf](https://github.com/spnda/fastgltf)

### Build Instructions (Linux only):
1. Clone dependencies into third_party directory
   ```bash
   git clone https://github.com/g-truc/glm third_party/glm/
   # SDL needs to be installed on the system separately, not build from within this app
   git clone https://github.com/ocornut/imgui third_party/imgui/
   # Clone STB to you machine if you'd like.  Put stb_image.h in your /usr/include.
   git clone https://github.com/tinyobjloader/tinyobjloader third_party/tinyobjloader/
   git clone https://github.com/charles-lunarg/vk-bootstrap.git third_party/vk-bootstrap/
   git clone https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator third_party/VulkanMemoryAllocator/
   # download fmt with package manger
   git clone https://github.com/spnda/fastgltf third_party/fastgltf/
   
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
