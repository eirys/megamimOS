#include "pit.h"
#include "core.h"

namespace kfs {

u32 microsecondsSinceBoot;

void sleep(u32 microseconds) {
    u32 end = microsecondsSinceBoot + microseconds;
    while (microsecondsSinceBoot < end) {
        core::hlt();
    }
}

}
