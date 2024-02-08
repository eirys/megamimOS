/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 18:08:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.h"
#include "cursor.h"
#include "history.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "No name :("
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

    inline
    void setId(const u32 id) {
        m_id = id;
    }

    /* ---------------------------------------- */

    inline
    void putString(const i8* str) {
        while (*str)
            putChar(vga::Char(*str++));
    }

    inline
    void putNbr(u32 nbr) {
        i8 buf[32];
        u32 cur = 32;

        if (nbr == 0) {
            putChar('0');
            return;
        }
        while (nbr) {
            --cur;
            buf[cur] = '0' + (nbr % 10);
            nbr /= 10;
        }

        for (u32 i = cur; i < 32; i++) {
            putChar(buf[i]);
        }
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
        m_cursor.setTo(
            (i32)(vga::WIDTH / 2) - 1,
            (i32)(vga::HEIGHT / 2) - 1);
        putString("42");
        constexpr u32 halfKernelNameLength = (KERNEL_NAME_LEN  + 3) /* For the extra ' #{id}' */ / 2U;
        m_cursor.setTo(
            (i32)(vga::WIDTH / 2) - halfKernelNameLength,
            (i32)(vga::HEIGHT / 2));
        putString(KERNEL_NAME);
        putString(" #");
        putNbr(m_id);
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

    inline
    void offsetDownward() {
        insertNewline(); // For now, just insert a newline
    }

    inline
    void offsetUpward() {
        vga::scrollDown(m_color);
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
    u32             m_id;

}; // class Terminal

Terminal& operator<<(Terminal& term, const i8* str) {
    term.putString(str);
    return term;
}

Terminal& operator<<(Terminal& term, const vga::Char character) {
    term.putChar(character);
    return term;
}

Terminal& operator<<(Terminal& term, const u32 nbr) {
    term.putNbr(nbr);
    return term;
}

} // namespace ui