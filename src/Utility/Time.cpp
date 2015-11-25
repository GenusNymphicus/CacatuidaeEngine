#include "Utility/Time.h"

#include <chrono>

using namespace std::chrono;
unsigned int cac::Time::getTimeInMs()
{
    std::chrono::milliseconds currentMs = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    return currentMs.count();
}