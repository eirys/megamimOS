/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:00:21 by nmathieu          #+#    #+#             */
/*   Updated: 2024/02/15 13:00:21 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_manager.h"
#include "types.h"
#include "core.h"
#include "vga.h"


static u8 x = 0;
static u8 y = 0;
static vga::Color fg = vga::Color::Immaculate;

/// @brief Prinst the provided string to the VGA buffer *without using the
/// regular terminal interface. This prevents the kernel from using a
/// potentially corrupted state while it is already panicking.
/// @param msg The message to be printed.
static
void vgaPanicPrint(char const *msg) noexcept
{
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
            vga::putChar(*msg, x, y, fg, vga::Color::Crimson);
            x += 1;
        }

        ++msg;
    }
}

/// @brief Stops the kernel with the provided message.
/// @param msg A message explaining what has gone wrong.
void beginKernelPanic(char const *msg) noexcept
{
    // Make sure that interrupts won't trigger and maybe
    // corrupt the state even more.
    core::cli();

    vga::clearBuffer(fg, vga::Color::Crimson);
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
    vgaPanicPrint("\n");
    fg = vga::Color::Ash;
    vgaPanicPrint(msg);
    fg = vga::Color::Immaculate;
    vgaPanicPrint("\n");

    // Stop the CPU until the user manually restarts the system.
    for (;;) core::hlt();
}