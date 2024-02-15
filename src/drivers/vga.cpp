/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:36:28 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:42:03 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vga.h"

namespace vga {

/* -------------------------------------------- */
/*                     CHAR                     */
/* -------------------------------------------- */

Char::operator u8() const {
    return m_inner;
}

/* -------------------------------------------- */

bool Char::operator==(const Char& other) const {
    return m_inner == other.m_inner;
}

bool Char::operator!=(const Char& other) const {
    return m_inner != other.m_inner;
}

bool Char::isAlpha() const {
    return  (m_inner >= (u8)'A' && m_inner <= (u8)'Z') ||
            (m_inner >= (u8)'a' && m_inner <= (u8)'z');
}

bool Char::isNum() const {
    return m_inner >= (u8)'0' && m_inner <= (u8)'9';
}

bool Char::isAlphanum() const {
    return isAlpha() || isNum();
}

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static
void _enableCursor(u8 cursorStart, u8 cursorEnd) {
	core::outB(CONTROL_PORT, 0x0A);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xC0) | cursorStart);

	core::outB(CONTROL_PORT, 0x0B);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xE0) | cursorEnd);
}

void init() {
    clearBuffer();
    _enableCursor(0xe, 0xe);
}

/* -------------------------------------------- */

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