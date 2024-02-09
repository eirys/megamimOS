/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 22:44:21 by etran            ###   ########.fr       */
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
    void init(const u32 id) {
        vga::clearBuffer(m_color);
        _putTitle(id);
        prompt();
    }

    inline
    void prompt() {
        insertNewline();

        putString((i8*)"$ ");
        m_cursor = LINE_BEGIN;
        m_lineLength = LINE_BEGIN;
        m_isPrompt = true;
    }

    /* ---------------------------------------- */

    inline
    void putString(const i8* str) {
        while (*str)
            putChar(vga::Char(*str++));
    }

    inline
    void putNbr(u32 nbr) {
        i8  buf[32];
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

    /**
     * @brief Puts a character in the buffer.
     *
     * @note If the screen is full, it'll scroll up.
     * @note If the screen is scrolled up, and the function is called,
     * the screen will be scrolled down to the input line.
    */
    inline
    void putChar(const vga::Char character) {
        m_scrollAmount = 0U;

        m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = character;
        m_cursor += 1;
        m_lineLength += 1;

        if (m_cursor == vga::WIDTH) {
            insertNewline();
        }
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

    inline
    void insertNewline() {
        m_isPrompt = false;
        scrollUp();

        m_cursor = 0U;
        m_scrollAmount = 0U;
        m_lineLength = 0U;
    }

    void eraseChar() {
        if (m_cursor == LINE_BEGIN)
            return;

        m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH - 1] = (u8)vga::Char::Empty;
        m_cursor -= 1;
        m_lineLength -= 1;
    }

    void deleteChar() {
        if (m_cursor == m_lineLength)
            return;

        for (u32 i = m_cursor; i < m_lineLength; i++) {
            m_data[i + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = m_data[i + 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH];
        }
        m_lineLength -= 1;
    }

    // void insertCharAtCursor(const vga::Char character) {
    //     for (u32 i = m_cursor; i > m_lineLength - m_cursor; i--) {
    //         m_data[i + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = m_data[i + 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH];
    //     }
    //     m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = character;
    //     m_cursor += 1;
    //     m_lineLength += 1;
    // }

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

    inline
    void moveCursorLeftward() {
        if (m_cursor > (m_isPrompt ? LINE_BEGIN : 0)) {
            m_cursor -= 1;
        }
    }

    inline
    void moveCursorRightward() {
        if (m_cursor < m_lineLength) {
            m_cursor += 1;
        }
    }

    /* ---------------------------------------- */

    /**
     * @brief Scrapes the current vga buffer and redraws the terminal.
    */
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

    static constexpr u32    KERNEL_NAME_LEN = sizeof(KERNEL_NAME);
    static constexpr u8     TERMINAL_HEIGHT = vga::HEIGHT * 2U;
    static constexpr u8     LINE_BEGIN = 2U;

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    vga::Char       m_data[vga::WIDTH * TERMINAL_HEIGHT];
    vga::Color      m_color = vga::Color::Immaculate;
    u8              m_cursor = 0U;
    u8              m_scrollAmount = 0U;
    u8              m_lineLength = LINE_BEGIN;
    bool            m_isPrompt = true;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    inline
    void _putTitle(const u32 id) {
        for (u32 i = 0; i < vga::WIDTH / 2U - KERNEL_NAME_LEN / 2U; ++i)
            putChar(' ');
        putString(KERNEL_NAME);
        putChar(' ');
        putChar(vga::Char::Heart);
        putChar(' ');
        putNbr(id);
        for (u32 i = 0; i < vga::HEIGHT / 2; ++i)
            scrollUp();
        m_cursor = 0U;
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