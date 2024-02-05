/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 16:03:10 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace vga {

static constexpr const uint8_t VGA_WIDTH = 80;
static constexpr const uint8_t VGA_HEIGHT = 25;

uint8_t* const VGA_BUFFER = (uint8_t*)0xB8000;

/**
 * @brief Keeps track of the current position
 * of the VGA buffer cursor.
*/
class Cursor {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Cursor(): x(0U), y(0U) {}

    ~Cursor() = default;

    Cursor(const Cursor& other) = delete;
    Cursor& operator=(const Cursor& other) = delete;
    Cursor(Cursor&& other) = delete;
    Cursor& operator=(Cursor&& other) = delete;

    /* ---------------------------------------- */

    inline
    uint8_t& operator[](const uint32_t index) {
        return elem[index];
    }

    inline
    const uint8_t& operator[](const uint32_t index) const {
        return elem[index];
    }

    /* ---------------------------------------- */

    inline
    void move(const int32_t dx, const int32_t dy) {
        x += dx;
        y += dy;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    union {
        struct { uint8_t x, y; };
        uint8_t elem[2];
    };

}; // class Cursor

/**
 * @brief The one cursor.
*/
static Cursor cursor;

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
        Heart = 3,
        Diamond = 4,
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Char(uint8_t inner) : inner(inner) {}

    Char() = default;
    ~Char() = default;

    inline
    explicit operator uint8_t() const {
        return inner;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    uint8_t inner = 0U;

}; // class Char

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static inline
void clearBuffer() {
    for (uint32_t i = 0; i < 2 * VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_BUFFER[i] = 0;
    }
}

static inline
void putChar(
    const Char character,
    const uint32_t x,
    const uint32_t y,
    const Color color = Color::Immaculate
) {
    VGA_BUFFER[2 * (y * VGA_WIDTH + x)] = (uint8_t)character;
    VGA_BUFFER[2 * (y * VGA_WIDTH + x) + 1] = (uint8_t)color;
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
void scrollUp() {
    for (uint32_t y = 1; y < VGA_HEIGHT; y++) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            VGA_BUFFER[2 * ((y - 1) * VGA_WIDTH + x)] = VGA_BUFFER[2 * (y * VGA_WIDTH + x)];
            VGA_BUFFER[2 * ((y - 1) * VGA_WIDTH + x) + 1] = VGA_BUFFER[2 * (y * VGA_WIDTH + x) + 1];
        }
    }
    for (uint32_t x = 0; x < VGA_WIDTH; x++) {
        VGA_BUFFER[2 * ((VGA_HEIGHT - 1) * VGA_WIDTH + x)] = 0;
        VGA_BUFFER[2 * ((VGA_HEIGHT - 1) * VGA_WIDTH + x) + 1] = 0;
    }
}

static inline
void scrollDown() {
    for (uint32_t y = VGA_HEIGHT - 1; y > 0; y--) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            VGA_BUFFER[2 * (y * VGA_WIDTH + x)] = VGA_BUFFER[2 * ((y - 1) * VGA_WIDTH + x)];
            VGA_BUFFER[2 * (y * VGA_WIDTH + x) + 1] = VGA_BUFFER[2 * ((y - 1) * VGA_WIDTH + x) + 1];
        }
    }
    for (uint32_t x = 0; x < VGA_WIDTH; x++) {
        VGA_BUFFER[2 * (x)] = 0;
        VGA_BUFFER[2 * (x) + 1] = 0;
    }
}

} // namespace vga