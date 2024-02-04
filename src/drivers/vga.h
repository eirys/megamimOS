/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/04 22:38:30 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

namespace vga {

#define VGA_BUFFER ((uint8_t*)0xB8000)

class Cursor {
private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    union {
        struct { uint8_t x, y; };
        uint8_t elem[2];
    };

public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Cursor(): x(0U), y(0U) {}

    Cursor(const Cursor& other) = delete;

    /* ---------------------------------------- */

    uint8_t& operator[](const uint32_t index) {
        return elem[index];
    }

    const uint8_t& operator[](const uint8_t index) const {
        return elem[index];
    }
};

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
private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    uint8_t inner;

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

    explicit operator uint8_t() const {
        return inner;
    }
};

static inline
void clearBuffer() {
    for (int i = 0; i < 2 * 80 * 25; i++) {
        VGA_BUFFER[i] = 0;
    }
}

static inline
void putchar(Char character, int x, int y, Color color = Color::Immaculate) {
    VGA_BUFFER[2 * (y * 80 + x)] = (uint8_t)character;
    VGA_BUFFER[2 * (y * 80 + x) + 1] = (uint8_t)color;
}

static inline
void putString(const uint8_t* string, int x, int y, Color color = Color::Immaculate) {
    for (int i = 0; string[i] != 0; i++) {
        putchar(string[i], x + i, y, color);
    }
}

} // namespace vga