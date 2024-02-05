/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 00:03:43 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cursor.h"

namespace vga {

u8* const  BUFFER = (u8*)0xB8000;

/* -------------------------------------------- */

enum class Color: u8 {
    Carbon      = 0x0,
    Marine      = 0x1,
    Grass       = 0x2,
    Teal        = 0x3,
    Crimson     = 0x4,
    Grape       = 0x5,
    Poop        = 0x6,
    Cloud       = 0x7,
    Ash         = 0x8,
    Indigo      = 0x9,
    Chartreuse  = 0xA,
    Sky         = 0xB,
    Cherry      = 0xC,
    Barbie      = 0xD,
    Daffodil    = 0xE,
    Immaculate  = 0xF,

    First       = Carbon,
    Last        = Immaculate
};

class Char {
public:
    /* ---------------------------------------- */
    /*                   ENUMS                  */
    /* ---------------------------------------- */

    enum: u8 {
        Empty       = 0,
        Heart       = 3,
        Diamond     = 4
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Char(u8 inner) : m_inner(inner) {}

    Char() = default;
    Char(Char&& other) = default;
    Char(const Char& other) = default;
    Char& operator=(Char&& other) = default;
    Char& operator=(const Char& other) = default;
    ~Char() = default;

    inline
    explicit operator u8() const {
        return m_inner;
    }

    /* ---------------------------------------- */

    bool operator==(const Char& other) const {
        return m_inner == other.m_inner;
    }

    bool operator!=(const Char& other) const {
        return m_inner != other.m_inner;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u8 m_inner = Empty;

}; // class Char

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static inline
void putChar(
    const Char character,
    const u32 x,
    const u32 y,
    const Color color = Color::Immaculate
) {
    BUFFER[2 * (y * WIDTH + x)] = (u8)character;
    BUFFER[2 * (y * WIDTH + x) + 1] = (u8)color;
}

static inline
void putString(
    const char* string,
    const u32 x_begin,
    const u32 y_begin,
    const Color color = Color::Immaculate
) {
    for (u32 i = 0; string[i] != 0; i++) {
        putChar(string[i], x_begin + i, y_begin, color);
    }
}

static inline
void clearBuffer() {
    for (u32 i = 0; i < WIDTH; i++) {
        for (u32 j = 0; j < HEIGHT; j++) {
            putChar(Char::Empty, i, j, Color::Immaculate);
        }
    }
}

/* ------------------ CURSOR ------------------ */

static inline
void scrollUp() {
    for (u32 y = 1; y < HEIGHT; y++) {
        for (u32 x = 0; x < WIDTH; x++) {
            BUFFER[2 * ((y - 1) * WIDTH + x)] = BUFFER[2 * (y * WIDTH + x)];
            BUFFER[2 * ((y - 1) * WIDTH + x) + 1] = BUFFER[2 * (y * WIDTH + x) + 1];
        }
    }
    for (u32 x = 0; x < WIDTH; x++) {
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x)] = 0;
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x) + 1] = 0;
    }
    // g_cursor.move(0, -1);
}

static inline
void scrollDown() {
    for (u32 y = HEIGHT - 1; y > 0; y--) {
        for (u32 x = 0; x < WIDTH; x++) {
            BUFFER[2 * (y * WIDTH + x)] = BUFFER[2 * ((y - 1) * WIDTH + x)];
            BUFFER[2 * (y * WIDTH + x) + 1] = BUFFER[2 * ((y - 1) * WIDTH + x) + 1];
        }
    }
    for (u32 x = 0; x < WIDTH; x++) {
        BUFFER[2 * (x)] = 0;
        BUFFER[2 * (x) + 1] = 0;
    }
    // g_cursor.move(0, 1);
}

static inline
void enableCursor(u8 cursorStart, u8 cursorEnd) {
	core::outB(0x3D4, 0x0A);
	core::outB(0x3D5, (core::inB(0x3D5) & 0xC0) | cursorStart);

	core::outB(0x3D4, 0x0B);
	core::outB(0x3D5, (core::inB(0x3D5) & 0xE0) | cursorEnd);
}

static inline
void disableCursor() {
	core::outB(0x3D4, 0x0A);
	core::outB(0x3D5, 0x20);
}

static inline
void updateCursor(const u8 x, const u8 y) {
	u16 pos = y * WIDTH + x;

	core::outB(0x3D4, 0x0F);
	core::outB(0x3D5, (u8)(pos & 0xFF));
	core::outB(0x3D4, 0x0E);
	core::outB(0x3D5, (u8)((pos >> 8) & 0xFF));
}

} // namespace vga