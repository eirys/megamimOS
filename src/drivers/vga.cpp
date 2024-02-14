/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:36:28 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:38:46 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vga.h"

namespace vga {

void putChar(
    const Char character,
    const u8 x,
    const u8 y,
    const Color fontColor
) {
    BUFFER[2 * (y * WIDTH + x)] = (u8)character;
    BUFFER[2 * (y * WIDTH + x) + 1] = (u8)fontColor;
}

void setBgColor(
    const u8 x,
    const u8 y,
    const Color bgColor
) {
    BUFFER[2 * (y * WIDTH + x) + 1] = (u8)BUFFER[2 * (y * WIDTH + x) + 1] | (u8)bgColor << 4;
}

void clearBuffer(Color color) {
    for (u8 i = 0; i < WIDTH; i++) {
        for (u8 j = 0; j < HEIGHT; j++) {
            putChar(Char::Empty, i, j, color);
        }
    }
}

/* ------------------ CURSOR ------------------ */

void enableCursor(u8 cursorStart, u8 cursorEnd) {
	core::outB(CONTROL_PORT, 0x0A);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xC0) | cursorStart);

	core::outB(CONTROL_PORT, 0x0B);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xE0) | cursorEnd);
}

void disableCursor() {
	core::outB(CONTROL_PORT, 0x0A);
	core::outB(DATA_PORT, 0x20);
}

void setCursorPos(u8 x, u8 y) {
    const u16 pos = y * WIDTH + x;

    // Set low cursor byte
    core::outB(CONTROL_PORT, 0x0F);
    core::outB(DATA_PORT, (u8)(pos & 0xFF));

    // Set high cursor byte
    core::outB(CONTROL_PORT, 0x0E);
    core::outB(DATA_PORT, (u8)((pos >> 8) & 0xFF));
}

} // namespace vga