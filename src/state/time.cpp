#include "pit.h"
#include "core.h"

namespace kfs {

u32 tickCountSinceBoot;

void sleep(u32 microseconds) {
    const u32 usPerTick = pit::tickDurationMicros;
    u32 end = tickCountSinceBoot * usPerTick + microseconds;
    while (tickCountSinceBoot * usPerTick < end) {
        core::hlt();
    }
}

}
