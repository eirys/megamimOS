/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 21:18:45 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.h"
#include "cursor.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "undefined kernel name :("
#endif

namespace ui {

/**
 * @brief Virtual console to run a pseudo-shell.
*/
class Terminal final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Terminal() = default;
    Terminal(const Terminal& other) = default;
    Terminal& operator=(const Terminal& other) = default;
    ~Terminal() = default;

    Terminal(Terminal&& other) = delete;
    Terminal& operator=(Terminal&& other) = delete;

    /* ---------------------------------------- */

    inline
    void setColor(const vga::Color color) {
        m_color = color;
    }

    /* ---------------------------------------- */

    inline
    void putString(const i8* str) {
        while (*str)
            putChar(vga::Char(*str++));
    }

    inline
    void putChar(const vga::Char character) {
        vga::putChar(character, m_cursor.m_x, m_cursor.m_y, m_color);
        if (m_cursor.moveX(1) == vga::CursorPosResult::PastRight)
            vga::scrollUp(m_color);
        m_cursor.update();
    }

    void reset() {
        vga::clearBuffer(m_color);
        constexpr u32 halfKernelNameLength = KERNEL_NAME_LEN / 2U;
        m_cursor.setTo(
            (i32)(vga::WIDTH / 2) - halfKernelNameLength,
            (i32)(vga::HEIGHT / 2));

        putString((i8*)KERNEL_NAME);
        m_cursor.setTo(0U, vga::HEIGHT - 1);
        m_cursor.update();
    }

    inline
    void eraseChar() {
        m_cursor.moveX(-1);
        vga::putChar(vga::Char::Empty, m_cursor.m_x, m_cursor.m_y, m_color);
        m_cursor.update();
    }

    inline
    void insertNewline() {
        vga::scrollUp(m_color);
        m_cursor.setTo(0U, vga::HEIGHT - 1);
        m_cursor.update();
    }


private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u32  KERNEL_NAME_LEN = sizeof(KERNEL_NAME);

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    // History         m_history;
    vga::Cursor     m_cursor;
    vga::Color      m_color;

}; // class Terminal

Terminal& operator<<(Terminal& term, const i8* str) {
    term.putString(str);
    return term;
}

Terminal& operator<<(Terminal& term, const vga::Char character) {
    term.putChar(character);
    return term;
}

} // namespace ui