/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 20:09:30 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include "cursor.h"

namespace vga {

uint8_t* const  BUFFER = (uint8_t*)0xB8000;

/* -------------------------------------------- */

enum class Color: uint8_t {
    Carbon = 0x0,
    Marine = 0x1,
    Grass = 0x2,
    Teal = 0x3,
    Crimson = 0x4,
    Grape = 0x5,
    Poop = 0x6,
    Cloud = 0x7,
    Ash = 0x8,
    Indigo = 0x9,
    Chartreuse = 0xA,
    Sky = 0xB,
    Cherry = 0xC,
    Barbie = 0xD,
    Daffodil = 0xE,
    Immaculate = 0xF
};

class Char {
public:
    /* ---------------------------------------- */
    /*                   ENUMS                  */
    /* ---------------------------------------- */

    enum: uint8_t {
        Empty = 0,
        Heart = 3,
        Diamond = 4,

        First = Empty,
        Last = Diamond
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Char(uint8_t inner) : m_inner(inner) {}

    Char() = default;
    ~Char() = default;

    inline
    explicit operator uint8_t() const {
        return m_inner;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    uint8_t m_inner = 0U;

}; // class Char

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static inline
void putChar(
    const Char character,
    const uint32_t x,
    const uint32_t y,
    const Color color = Color::Immaculate
) {
    BUFFER[2 * (y * WIDTH + x)] = (uint8_t)character;
    BUFFER[2 * (y * WIDTH + x) + 1] = (uint8_t)color;
}

static inline
void putString(
    const char* string,
    const uint32_t x_begin,
    const uint32_t y_begin,
    const Color color = Color::Immaculate
) {
    for (uint32_t i = 0; string[i] != 0; i++) {
        putChar(string[i], x_begin + i, y_begin, color);
    }
}

static inline
void clearBuffer() {
    for (uint32_t i = 0; i < WIDTH; i++) {
        for (uint32_t j = 0; j < HEIGHT; j++) {
            putChar(Char::Empty, i, j, Color::Immaculate);
        }
    }
}

/* ------------------ CURSOR ------------------ */

static inline
void scrollUp() {
    for (uint32_t y = 1; y < HEIGHT; y++) {
        for (uint32_t x = 0; x < WIDTH; x++) {
            BUFFER[2 * ((y - 1) * WIDTH + x)] = BUFFER[2 * (y * WIDTH + x)];
            BUFFER[2 * ((y - 1) * WIDTH + x) + 1] = BUFFER[2 * (y * WIDTH + x) + 1];
        }
    }
    for (uint32_t x = 0; x < WIDTH; x++) {
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x)] = 0;
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x) + 1] = 0;
    }
    // g_cursor.move(0, -1);
}

static inline
void scrollDown() {
    for (uint32_t y = HEIGHT - 1; y > 0; y--) {
        for (uint32_t x = 0; x < WIDTH; x++) {
            BUFFER[2 * (y * WIDTH + x)] = BUFFER[2 * ((y - 1) * WIDTH + x)];
            BUFFER[2 * (y * WIDTH + x) + 1] = BUFFER[2 * ((y - 1) * WIDTH + x) + 1];
        }
    }
    for (uint32_t x = 0; x < WIDTH; x++) {
        BUFFER[2 * (x)] = 0;
        BUFFER[2 * (x) + 1] = 0;
    }
    // g_cursor.move(0, 1);
}

static inline
void enableCursor(uint8_t cursorStart, uint8_t cursorEnd) {
	ps2::outB(0x3D4, 0x0A);
	ps2::outB(0x3D5, (ps2::inB(0x3D5) & 0xC0) | cursorStart);

	ps2::outB(0x3D4, 0x0B);
	ps2::outB(0x3D5, (ps2::inB(0x3D5) & 0xE0) | cursorEnd);
}

static inline
void disableCursor() {
	ps2::outB(0x3D4, 0x0A);
	ps2::outB(0x3D5, 0x20);
}

static inline
void updateCursor(const uint8_t x, const uint8_t y) {
	uint16_t pos = y * WIDTH + x;

	ps2::outB(0x3D4, 0x0F);
	ps2::outB(0x3D5, (uint8_t)(pos & 0xFF));
	ps2::outB(0x3D4, 0x0E);
	ps2::outB(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

} // namespace vga