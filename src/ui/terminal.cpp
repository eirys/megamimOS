/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:17:38 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:25:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "lib.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

void Terminal::setColor(const vga::Color color) {
    m_color = color;
}

void Terminal::init() {
    vga::clearBuffer(m_color);
    prompt();
}

void Terminal::prompt() {
    insertNewline();

    putString((i8*)"$ ");
    m_cursor = LINE_BEGIN;
    m_lineLength = LINE_BEGIN;
    m_isPrompt = true;
}

/**
 * @brief Scrapes the current vga buffer and redraws the terminal.
*/
void Terminal::draw() const {
    for (u32 i = vga::WIDTH; i < vga::HEIGHT * vga::WIDTH; i++) {
        vga::BUFFER[2 * i] = m_data[i + (TERMINAL_HEIGHT - m_scrollAmount - vga::HEIGHT) * vga::WIDTH];
        vga::BUFFER[2 * i + 1] = (u8)m_color;
    }

    if (m_scrollAmount == 0)
        vga::setCursorPos(m_cursor, SCREEN_HEIGHT);
    else
        vga::setCursorPos(vga::WIDTH, vga::HEIGHT);
}

/* -------------------------------------------- */

void Terminal::putString(const i8* str) {
    while (*str)
        putChar(vga::Char(*str++));
}

void Terminal::putNbr(u32 nbr) {
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
void Terminal::putChar(const vga::Char character) {
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

/* -------------------------------------------- */

void Terminal::insertNewline() {
    m_isPrompt = false;
    _scrollUp();

    focusOnCommandLine();

    m_cursor = 0U;
    m_lineLength = 0U;
}

void Terminal::eraseChar() {
    focusOnCommandLine();

    if (m_cursor == (m_isPrompt ? LINE_BEGIN : 0))
        return;

    m_data[m_cursor + (TERMINAL_HEIGHT - 1) * vga::WIDTH - 1] = (u8)vga::Char::Empty;
    m_cursor -= 1;

    _offsetLineByOneToLeft();
    m_lineLength -= 1;
}

void Terminal::deleteChar() {
    focusOnCommandLine();

    if (m_cursor == m_lineLength) {
        return;
    }

    _offsetLineByOneToLeft();
    m_lineLength -= 1;
}

void Terminal::eraseLine() {
    while (m_cursor != (m_isPrompt ? LINE_BEGIN : 0)) {
        eraseChar();
    }
}

/* -------------------------------------------- */

void Terminal::focusOnCommandLine() {
    m_scrollAmount = 0U;
}

void Terminal::focusOnTopOfBuffer() {
    m_scrollAmount = TERMINAL_HEIGHT - SCREEN_HEIGHT - 1;
}

void Terminal::offsetDownward() {
    if (m_scrollAmount != 0) {
        m_scrollAmount -= 1;
    }
}

void Terminal::offsetUpward() {
    if (m_scrollAmount < TERMINAL_HEIGHT - SCREEN_HEIGHT) {
        m_scrollAmount += 1;
    }
}

void Terminal::moveCursorLeftward() {
    focusOnCommandLine();
    if (m_cursor > (m_isPrompt ? LINE_BEGIN : 0)) {
        m_cursor -= 1;
    }
}

void Terminal::moveCursorRightward() {
    focusOnCommandLine();
    if (m_cursor < m_lineLength) {
        m_cursor += 1;
    }
}

void Terminal::moveCursorToStart() {
    focusOnCommandLine();
    m_cursor = m_isPrompt ? LINE_BEGIN : 0;
}

void Terminal::moveCursorToEnd() {
    focusOnCommandLine();
    m_cursor = m_lineLength;
}

void Terminal::moveCursorToBeginningOfWord() {
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

void Terminal::moveCursorToEndOfWord() {
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

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

/**
 * @brief Moves the screen up by one line.
*/
void Terminal::_scrollUp() {
    lib::memmove(m_data, m_data + vga::WIDTH, vga::WIDTH * (TERMINAL_HEIGHT - 1));

    for (u32 i = 0; i < vga::WIDTH; i++) {
        m_data[vga::WIDTH * (TERMINAL_HEIGHT - 1) + i] = (u8)vga::Char::Empty;
    }
}

/**
 * @brief From m_cursor, moves the line one character to the right.
*/
void Terminal::_offsetLineByOneToRight() {
    for (u32 i = vga::WIDTH - 1; i > m_cursor; --i) {
        const u32 currIndex = i + (TERMINAL_HEIGHT - 1) * vga::WIDTH;
        const u32 prevIndex = i - 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH;

        m_data[currIndex] = m_data[prevIndex];
    }
}

/**
 * @brief From m_cursor, moves the line one character to the left.
*/
void Terminal::_offsetLineByOneToLeft() {
    for (u32 i = m_cursor; i < m_lineLength; i++) {
        const u32 currIndex = i + (TERMINAL_HEIGHT - 1) * vga::WIDTH;
        const u32 nextIndex = i + 1 + (TERMINAL_HEIGHT - 1) * vga::WIDTH;

        m_data[currIndex] = m_data[nextIndex];
    }
}

/* -------------------------------------------- */
/*                     OTHER                    */
/* -------------------------------------------- */

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

}  // namespace ui