
#include "window.h"
#include "history.h"
#include "ps2.h"
#include "vga.h"

#define KERNEL_NAME         "megamimOS"
#define KERNEL_NAME_LEN     9

/**
 * @todo :P)
*/
struct MultibootInfo {
};

static inline
void _init() {
    vga::clearBuffer();
    ps2::readData();
}

/* -------------------------------------------- */

// Enable ASM linkage
extern "C"
void megamimOS_cpp(const MultibootInfo& info);

void megamimOS_cpp(const MultibootInfo& info) {
    _init();

    ps2::poll();
    ps2::read();

    vga::putString(KERNEL_NAME, 0, 0);
    vga::putChar(vga::Char::Heart, KERNEL_NAME_LEN + 1, 0, vga::Color::Cherry);

    // Testing lol
    // ps2::poll();
    // vga::scrollDown();
}