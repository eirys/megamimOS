/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 17:23:02 by etran            ###   ########.fr       */
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
        if (m_cursor == vga::WIDTH) {
            insertNewline();
        }

        m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = character;
        m_cursor += 1;
    }

    /* ---------------------------------------- */

    /**
     * @brief Moves the screen up by one line.
    */
    void scrollUp() {
        lib::memmove(m_data, m_data + vga::WIDTH, vga::WIDTH * (TERMINAL_HEIGHT - 1));

        for (u32 i = 0; i < vga::WIDTH; i++) {
            m_data[vga::WIDTH * (TERMINAL_HEIGHT - 1) + i] = (u8)vga::Char::Empty;
        }
    }

    void reset() {
        vga::clearBuffer(m_color);
        _putTitle();
    }

    inline
    void insertNewline() {
        scrollUp();
        m_cursor = 0;
    }

    /* ---------------------------------------- */

    inline
    void offsetDownward() {
        if (m_scrollAmount != 0) {
            m_scrollAmount -= 1;
        }
    }

    inline
    void offsetUpward() {
        if (m_scrollAmount < TERMINAL_HEIGHT - vga::HEIGHT) {
            m_scrollAmount += 1;
        }
    }

    /* ---------------------------------------- */

    void draw() const {
        for (u32 i = 0; i < vga::HEIGHT * vga::WIDTH; i++) {
            vga::BUFFER[2 * i] = m_data[i + (TERMINAL_HEIGHT - m_scrollAmount - vga::HEIGHT) * vga::WIDTH];
            vga::BUFFER[2 * i + 1] = (u8)m_color;
        }

        if (m_scrollAmount == 0)
            vga::setCursorPos(m_cursor, vga::HEIGHT - 1);
        else
            vga::setCursorPos(vga::WIDTH, vga::HEIGHT);
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u32  KERNEL_NAME_LEN = sizeof(KERNEL_NAME);
    static constexpr u8 TERMINAL_HEIGHT = 50U;

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    vga::Char       m_data[vga::WIDTH * TERMINAL_HEIGHT];
    u32             m_id;
    u32             m_cursor;
    vga::Color      m_color;
    u32             m_scrollAmount = 0U;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    inline
    void _putTitle() {
        for (u32 i = 0; i < vga::WIDTH / 2 - KERNEL_NAME_LEN / 2; ++i)
            putChar(' ');
        putString(KERNEL_NAME);
        putChar(' ');
        putChar(vga::Char::Heart);
        putChar(' ');
        putNbr(m_id);
        for (u32 i = 0; i < vga::HEIGHT / 2; ++i)
            insertNewline();
    }

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