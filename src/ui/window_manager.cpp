/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:24:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 14:02:53 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_manager.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "No name :("
#endif

namespace ui {

/* -------------------------------------------- */
/*                STATIC MEMBERS                */
/* -------------------------------------------- */

Terminal    WindowManager::m_terminals[TERMINAL_COUNT];
u8          WindowManager::m_currentTerminal;

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

WindowManager& WindowManager::get() {
    static WindowManager wm;
    return wm;
}

void WindowManager::init() {
    for (u8 id = 0; id < TERMINAL_COUNT; id++) {
        const u8 colorRaw = (u8)id + (u8)vga::Color::Indigo;
        m_terminals[id].init((vga::Color)colorRaw);
    }
    _currentTerminal().draw();
    _putTitle();
}

void WindowManager::draw() {
    _currentTerminal().draw();
}

Command WindowManager::getCommand() {
    return _currentTerminal().getCommand();
}

/* -------------------------------------------- */

void WindowManager::switchToNext() {
    m_currentTerminal = (m_currentTerminal + 1) % TERMINAL_COUNT;
    _putTitle();
}

void WindowManager::switchToPrevious() {
    m_currentTerminal = (m_currentTerminal + TERMINAL_COUNT - 1) % TERMINAL_COUNT;
    _putTitle();
}

Terminal& WindowManager::_currentTerminal() {
    return m_terminals[m_currentTerminal];
}

/* -------------------------------------------- */

/**
 * @brief Writes a str to terminal internal buffer.
 */
void WindowManager::write(const i8* str) {
    _currentTerminal() << str;
}

/**
 * @brief Writes a char to terminal internal buffer.
 */
void WindowManager::write(const vga::Char character) {
    _currentTerminal() << character;
}

/* -------------------------------------------- */

void WindowManager::eraseChar() {
    _currentTerminal().eraseChar();
}

void WindowManager::eraseLine() {
    _currentTerminal().eraseLine();
}

void WindowManager::deleteChar() {
    _currentTerminal().deleteChar();
}

void WindowManager::newLine() {
    _currentTerminal().insertNewline();
}

void WindowManager::prompt() {
    _currentTerminal().prompt();
}

/* -------------------------------------------- */

void WindowManager::scrollUp() {
    _currentTerminal().offsetUpward();
}

void WindowManager::scrollDown() {
    _currentTerminal().offsetDownward();
}

void WindowManager::moveCursorLeft() {
    _currentTerminal().moveCursorLeftward();
}

void WindowManager::moveCursorRight() {
    _currentTerminal().moveCursorRightward();
}

void WindowManager::moveCursorToBeginning() {
    _currentTerminal().moveCursorToStart();
}

void WindowManager::moveCursorToEnd() {
    _currentTerminal().moveCursorToEnd();
}

void WindowManager::scrollPageDown() {
    _currentTerminal().focusOnCommandLine();
}

void WindowManager::scrollPageUp() {
    _currentTerminal().focusOnTopOfBuffer();
}

void WindowManager::moveCursorToBeginningOfWord() {
    _currentTerminal().moveCursorToBeginningOfWord();
}

void WindowManager::moveCursorToEndOfWord() {
    _currentTerminal().moveCursorToEndOfWord();
}

void WindowManager::clearScreen() {
    _currentTerminal().resetInner();
    _putTitle();
}

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

void WindowManager::_putStr(u8 x, u8 y, const i8* str) {
    while (*str) {
        vga::putChar(vga::Char(*str), x, y, vga::Color::Carbon);
        ++str;
        ++x;
    }
}

void WindowManager::_putNbr(u8 x, u8 y, u32 nbr) {
    i8  buf[32];
    u32 cur = 32;

    if (nbr == 0) {
        vga::putChar('0', x, y, vga::Color::Carbon);
        return;
    }
    while (nbr) {
        --cur;
        buf[cur] = '0' + (nbr % 10);
        nbr /= 10;
    }

    for (u32 i = cur; i < 32; i++) {
        vga::putChar(buf[i], x + i - cur, y, vga::Color::Carbon);
    }
}

void WindowManager::_putTitle() {
    static constexpr u32 KERNEL_NAME_LEN = sizeof(KERNEL_NAME) - 1;
    _putStr(0, 0, KERNEL_NAME);
    vga::putChar(vga::Char::Heart, KERNEL_NAME_LEN + 1, 0, vga::Color::Crimson);
    vga::putChar(vga::Char::Hash, KERNEL_NAME_LEN + 3, 0, vga::Color::Carbon);
    _putNbr(KERNEL_NAME_LEN + 4, 0, (u32)m_currentTerminal);

    for (u8 i = 0; i < vga::WIDTH; ++i) {
        vga::setBgColor(i, 0, vga::Color::Cloud);
    }
}

/* -------------------------------------------- */
/*                     OTHER                    */
/* -------------------------------------------- */

WindowManager& operator<<(WindowManager& wm, const i8* str) {
    wm.write(str);
    return wm;
}

WindowManager& operator<<(WindowManager& wm, const vga::Char character) {
    wm.write(character);
    return wm;
}

} // namespace ui