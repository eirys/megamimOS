/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:37:50 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 15:19:12 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "core.h"

namespace ui {

enum class CursorPosResult: u8 {
    Valid,

    PastLeft,
    PastRight,
    PastTop,
    PastBottom
};

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
        u8 m_axis[2];
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
    u8& operator[](const u8 index) {
        return m_axis[index];
    }

    inline
    u8 operator[](const u8 index) const {
        return m_axis[index];
    }

    /* ---------------------------------------- */

    /**
     * @brief Updates the cursor's X position.
     */
    CursorPosResult moveX(const i8 dx) {
        const i8 newX = (i8)m_x + dx;

        m_x = 0U;
        if (newX <= 0)
            return CursorPosResult::PastLeft;
        else if (newX >= vga::WIDTH)
            return CursorPosResult::PastRight;

        m_x = newX;
        return CursorPosResult::Valid;
    }

    /**
     * @brief Updates the cursor's Y position.
     */
    CursorPosResult moveY(const i8 dy) {
        const i8 newY = (i8)m_y + dy;

        m_y = 0U;
        if (newY <= 0)
            return CursorPosResult::PastTop;
        else if (newY >= vga::HEIGHT)
            return CursorPosResult::PastBottom;

        m_y = newY;
        return CursorPosResult::Valid;
    }

    /**
     * @brief Sets the cursor to the given position.
     */
    inline
    void setTo(const i8 x, const i8 y) {
        m_x = x;
        m_y = y;
    }

    inline
    void update() const {
        vga::setCursorPos(m_x, m_y);
    }

}; // class Cursor

} // namespace ui