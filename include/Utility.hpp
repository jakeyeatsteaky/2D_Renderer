#ifndef UTILITY_HPP
#define UTILITY_HPP
#include "Logger.hpp"
#include <cstdint>


namespace util
{
    constexpr uint32_t WINDOW_HEIGHT = 800;
    constexpr uint32_t WINDOW_WIDTH = 600;
    constexpr const char* SHADER_SOURCE_DIR_VERT = "/home/jakbak/2D_Renderer/shaders/vertex";
    constexpr const char* SHADER_SOURCE_DIR_FRAG = "/home/jakbak/2D_Renderer/shaders/fragment";
    void TimeDelay_ms(uint32_t ms);
}

#endif //end utility hpp