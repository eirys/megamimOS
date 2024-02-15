#include "window_manager.h"
#include "types.h"
#include "core.h"
#include "vga.h"

/// Prints the provided string to the terminal.
///
/// This function volontarily avoids using the regular terminal API
/// in case it has been corrupted.
static
void vgaPanicPrint(char const *msg) noexcept
{
    static u8 x = 0;
    static u8 y = 0;

    while (*msg)
    {
        if (*msg == '\n')
            x = vga::WIDTH;
        
        if (x == vga::WIDTH)
        {
            x = 0;
            y += 1;
        }
        else
        {
            vga::putChar(*msg, x, y, vga::Color::Immaculate, vga::Color::Crimson);
            x += 1;
        }

        ++msg;
    }
}

/// Stops the kernel.
void beginKernelPanic() noexcept
{
    // Make sure that interrupts won't trigger and maybe
    // corrupt the state even more.
    core::cli();

    vga::clearBuffer(vga::Color::Immaculate, vga::Color::Crimson);
    vga::disableCursor();

    vgaPanicPrint("Something has gone wrong within the kernel.\n");
    vgaPanicPrint("You may submit an issue at:\n");
    vgaPanicPrint("\n");
    vgaPanicPrint("    https://github.com/eirys/megamimOS/issues/new\n");
    vgaPanicPrint("\n");
    vgaPanicPrint("\n");
    vgaPanicPrint("       |\\__/,|   (`\\\n");
    vgaPanicPrint("       |o o  |__ _) |\n");
    vgaPanicPrint("     _.( T   )  `  /\n");
    vgaPanicPrint("    ((_ `^--' /_<  \\\n");
    vgaPanicPrint("    `` `-'(((/  (((/\n");

    // Stop the CPU until the user manually restarts the system.
    for (;;) core::hlt();
}
