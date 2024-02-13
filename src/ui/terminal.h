/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 10:22:10 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "lib.h"
# include "vga.h"

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
    void init() {
        vga::clearBuffer(m_color);
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
    void putChar(const vga::Char character) {
        focusOnCommandLine();

        if (m_cursor == vga::WIDTH - 1 && m_isPrompt) {
            return;
        }

        if (m_cursor != m_lineLength) {
            if (m_lineLength == vga::WIDTH - 1)
                return;
            _offsetLineByOneToRight();
        }

        m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH] = character;

        m_cursor += 1;
        m_lineLength += 1;

        if (m_cursor == vga::WIDTH) {
            insertNewline();
        }
    }

    /* ---------------------------------------- */

    inline
    void insertNewline() {
        m_isPrompt = false;
        _scrollUp();

        focusOnCommandLine();

        m_cursor = 0U;
        m_lineLength = 0U;
    }

    void eraseChar() {
        focusOnCommandLine();

        if (m_cursor == (m_isPrompt ? LINE_BEGIN : 0))
            return;

        m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH - 1] = (u8)vga::Char::Empty;
        m_cursor -= 1;

        _offsetLineByOneToLeft();
        m_lineLength -= 1;
    }

    void deleteChar() {
        focusOnCommandLine();

        if (m_cursor == m_lineLength) {
            return;
        }

        _offsetLineByOneToLeft();
        m_lineLength -= 1;
    }

    void eraseLine() {
        while (m_cursor != (m_isPrompt ? LINE_BEGIN : 0)) {
            eraseChar();
        }
    }

    /* ---------------------------------------- */

    inline
    void focusOnCommandLine() {
        m_scrollAmount = 0U;
    }

    inline
    void focusOnTopOfBuffer() {
        m_scrollAmount = TERMINAL_HEIGHT - SCREEN_HEIGHT - 1;
    }

    inline
    void offsetDownward() {
        if (m_scrollAmount != 0) {
            m_scrollAmount -= 1;
        }
    }

    inline
    void offsetUpward() {
        if (m_scrollAmount < TERMINAL_HEIGHT - SCREEN_HEIGHT) {
            m_scrollAmount += 1;
        }
    }

    inline
    void moveCursorLeftward() {
        focusOnCommandLine();
        if (m_cursor > (m_isPrompt ? LINE_BEGIN : 0)) {
            m_cursor -= 1;
        }
    }

    inline
    void moveCursorRightward() {
        focusOnCommandLine();
        if (m_cursor < m_lineLength) {
            m_cursor += 1;
        }
    }

    inline
    void moveCursorToStart() {
        focusOnCommandLine();
        m_cursor = m_isPrompt ? LINE_BEGIN : 0;
    }

    inline
    void moveCursorToEnd() {
        focusOnCommandLine();
        m_cursor = m_lineLength;
    }

    void moveCursorToBeginningOfWord() {
        focusOnCommandLine();

        const u8 begin = m_isPrompt ? LINE_BEGIN : 0;

        while (m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH - 1] == vga::Char::Space
               && m_cursor > begin) {
            m_cursor -= 1;
        }

        while (m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH - 1] != vga::Char::Space
               && m_cursor > begin) {
            m_cursor -= 1;
        }
    }

    void moveCursorToEndOfWord() {
        focusOnCommandLine();

        const u8 end = m_lineLength;

        while (m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH + 1] != vga::Char::Space
               && m_cursor < end) {
            m_cursor += 1;
        }

        while (m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH + 1] == vga::Char::Space
               && m_cursor < end) {
            m_cursor += 1;
        }
    }

    /* ---------------------------------------- */

    /**
     * @brief Scrapes the current vga buffer and redraws the terminal.
    */
    void draw() const {
        for (u32 i = vga::WIDTH; i < vga::HEIGHT * vga::WIDTH; i++) {
            vga::BUFFER[2 * i] = m_data[i + (TERMINAL_HEIGHT - m_scrollAmount - vga::HEIGHT) * vga::WIDTH];
            vga::BUFFER[2 * i + 1] = (u8)m_color;
        }

        if (m_scrollAmount == 0)
            vga::setCursorPos(m_cursor, SCREEN_HEIGHT);
        else
            vga::setCursorPos(vga::WIDTH, vga::HEIGHT);
    }

    /* ---------------------------------------- */

    void getCommandLine(i8* const buffer) {


        prompt();
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u32    KERNEL_NAME_LEN = sizeof(KERNEL_NAME);
    static constexpr u8     SCREEN_HEIGHT = vga::HEIGHT - 1;
    static constexpr u8     TERMINAL_HEIGHT = vga::HEIGHT * 2U;
    static constexpr u8     LINE_BEGIN = 2U;

    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    vga::Char       m_data[vga::WIDTH * TERMINAL_HEIGHT] = { vga::Char::Empty };
    vga::Color      m_color = vga::Color::Immaculate;
    u8              m_scrollAmount = 0U;

    u8              m_cursor = 0U;
    u8              m_lineLength = LINE_BEGIN;
    bool            m_isPrompt = true;

    // Prompt          m_prompt;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    /**
     * @brief Moves the screen up by one line.
    */
    void _scrollUp() {
        lib::memmove(m_data, m_data + vga::WIDTH, vga::WIDTH * (TERMINAL_HEIGHT - 1));

        for (u32 i = 0; i < vga::WIDTH; i++) {
            m_data[vga::WIDTH * (TERMINAL_HEIGHT - 1) + i] = (u8)vga::Char::Empty;
        }
    }

    /**
     * @brief From m_cursor, moves the line one character to the right.
    */
    void _offsetLineByOneToRight() {
        for (u32 i = vga::WIDTH - 1; i > m_cursor; --i) {
            const u32 currIndex = i + (TERMINAL_HEIGHT - 1) * vga::WIDTH;
            const u32 prevIndex = i - 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH;

            m_data[currIndex] = m_data[prevIndex];
        }
    }

    /**
     * @brief From m_cursor, moves the line one character to the left.
    */
    void _offsetLineByOneToLeft() {
        for (u32 i = m_cursor; i < m_lineLength; i++) {
            const u32 currIndex = i + (TERMINAL_HEIGHT - 1) * vga::WIDTH;
            const u32 nextIndex = i + 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH;

            m_data[currIndex] = m_data[nextIndex];
        }
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