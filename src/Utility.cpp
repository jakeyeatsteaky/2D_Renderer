#include "Utility.hpp"
#include <chrono>
#include <thread>


void util::TimeDelay_ms(uint32_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));     
}