/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:37:50 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 23:34:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "core.h"

namespace vga {

static constexpr const u32 WIDTH = 80;
static constexpr const u32 HEIGHT = 25;

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
        struct { u8 m_x, m_y; };
        u8 m_elem[2];
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Cursor(): m_x(0U), m_y(0U) {}
    Cursor(const u8 x, const u8 y): m_x(x), m_y(y) {}

    Cursor(Cursor&& other) = default;
    Cursor(const Cursor& other) = default;
    Cursor& operator=(Cursor&& other) = default;
    Cursor& operator=(const Cursor& other) = default;
    ~Cursor() = default;

    /* ---------------------------------------- */

    inline
    u8& operator[](const u32 index) {
        return m_elem[index];
    }

    inline
    const u8& operator[](const u32 index) const {
        return m_elem[index];
    }

    /* ---------------------------------------- */

    inline
    void move(const u8 dx, const u8 dy) {
        if (m_x + dx < vga::WIDTH)
            m_x += dx;
        if (m_y + dy < vga::HEIGHT)
            m_y += dy;
    }

    inline
    void update() const {
        u16 pos = m_y * WIDTH + m_x;

        core::outB(0x3D4, 0x0F);
        core::outB(0x3D5, (u8)(pos & 0xFF));
        core::outB(0x3D4, 0x0E);
        core::outB(0x3D5, (u8)((pos >> 8) & 0xFF));
    }

}; // class Cursor

} // namespace vga