/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:37:50 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 19:39:13 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace vga {

static constexpr const uint32_t WIDTH = 80;
static constexpr const uint32_t HEIGHT = 25;

/**
 * @brief Keeps track of the current position
 * of the VGA buffer cursor.
*/
struct Cursor final {
public:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    union {
        struct { uint8_t m_x, m_y; };
        uint8_t m_elem[2];
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Cursor(): m_x(0U), m_y(0U) {}
    Cursor(const uint8_t x, const uint8_t y): m_x(x), m_y(y) {}

    Cursor(Cursor&& other) = default;
    Cursor(const Cursor& other) = default;
    Cursor& operator=(Cursor&& other) = default;
    Cursor& operator=(const Cursor& other) = default;
    ~Cursor() = default;

    /* ---------------------------------------- */

    inline
    uint8_t& operator[](const uint32_t index) {
        return m_elem[index];
    }

    inline
    const uint8_t& operator[](const uint32_t index) const {
        return m_elem[index];
    }

    /* ---------------------------------------- */

    inline
    void move(const uint8_t dx, const uint8_t dy) {
        if (m_x + dx < vga::WIDTH)
            m_x += dx;
        if (m_y + dy < vga::HEIGHT)
            m_y += dy;
    }

    inline
    void update() const {
        uint16_t pos = m_y * WIDTH + m_x;

        ps2::outB(0x3D4, 0x0F);
        ps2::outB(0x3D5, (uint8_t)(pos & 0xFF));
        ps2::outB(0x3D4, 0x0E);
        ps2::outB(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
    }

}; // class Cursor

} // namespace vga