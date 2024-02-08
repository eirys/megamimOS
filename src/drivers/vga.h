/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 20:44:46 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace vga {

static constexpr const u16 CONTROL_PORT = 0x3D4;
static constexpr const u16 DATA_PORT = 0x3D5;

static constexpr const u32 WIDTH = 80;
static constexpr const u32 HEIGHT = 25;

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

    inline
    bool operator==(const Char& other) const {
        return m_inner == other.m_inner;
    }

    inline
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
void clearBuffer(Color color = Color::Immaculate) {
    for (u32 i = 0; i < WIDTH; i++) {
        for (u32 j = 0; j < HEIGHT; j++) {
            putChar(Char::Empty, i, j, color);
        }
    }
}

/* ------------------ CURSOR ------------------ */

/**
 * @brief Moves the screen up by one line.
*/
static
void scrollUp(Color color) {
    for (u32 y = 1; y < HEIGHT; y++) {
        for (u32 x = 0; x < WIDTH; x++) {
            BUFFER[2 * ((y - 1) * WIDTH + x)] = BUFFER[2 * (y * WIDTH + x)];
            BUFFER[2 * ((y - 1) * WIDTH + x) + 1] = BUFFER[2 * (y * WIDTH + x) + 1];
        }
    }
    for (u32 x = 0; x < WIDTH; x++) {
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x)] = 0;
        BUFFER[2 * ((HEIGHT - 1) * WIDTH + x) + 1] = (u8)color;
    }
}

/**
 * @brief Moves the screen down by one line.
*/
static
void scrollDown(Color color) {
    for (u32 y = HEIGHT - 1; y > 0; y--) {
        for (u32 x = 0; x < WIDTH; x++) {
            BUFFER[2 * (y * WIDTH + x)] = BUFFER[2 * ((y - 1) * WIDTH + x)];
            BUFFER[2 * (y * WIDTH + x) + 1] = BUFFER[2 * ((y - 1) * WIDTH + x) + 1];
        }
    }
    for (u32 x = 0; x < WIDTH; x++) {
        BUFFER[2 * (x)] = 0;
        BUFFER[2 * (x) + 1] = (u8)color;
    }
}

static
void enableCursor(u8 cursorStart, u8 cursorEnd) {
	core::outB(CONTROL_PORT, 0x0A);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xC0) | cursorStart);

	core::outB(CONTROL_PORT, 0x0B);
	core::outB(DATA_PORT, (core::inB(DATA_PORT) & 0xE0) | cursorEnd);
}

static inline
void disableCursor() {
	core::outB(CONTROL_PORT, 0x0A);
	core::outB(DATA_PORT, 0x20);
}

static inline
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