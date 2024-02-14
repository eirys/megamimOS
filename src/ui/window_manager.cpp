/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:24:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:34:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_manager.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "No name :("
#endif

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

WindowManager::WindowManager() {
    for (u8 id = 0; id < TERMINAL_COUNT; id++) {
        const u8 colorRaw = (u8)id + (u8)vga::Color::Indigo;
        m_terminals[id].setColor((vga::Color)colorRaw);
        m_terminals[id].init();
    }
    currentTerminal().draw();
    _putTitle();
}

/* -------------------------------------------- */

void WindowManager::draw() const {
    currentTerminal().draw();
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

Terminal& WindowManager::currentTerminal() {
    return m_terminals[m_currentTerminal];
}

const Terminal& WindowManager::currentTerminal() const {
    return m_terminals[m_currentTerminal];
}

/* -------------------------------------------- */

/**
 * @brief Writes a str to terminal internal buffer.
 */
void WindowManager::write(const i8* str) {
    currentTerminal() << str;
}

/**
 * @brief Writes a char to terminal internal buffer.
 */
void WindowManager::write(const vga::Char character) {
    currentTerminal() << character;
}

/* -------------------------------------------- */

void WindowManager::eraseChar() {
    currentTerminal().eraseChar();
}

void WindowManager::eraseLine() {
    currentTerminal().eraseLine();
}

void WindowManager::deleteChar() {
    currentTerminal().deleteChar();
}

void WindowManager::newLine() {
    currentTerminal().insertNewline();
}

void WindowManager::prompt() {
    currentTerminal().prompt();
}

/* -------------------------------------------- */

void WindowManager::scrollUp() {
    currentTerminal().offsetUpward();
}

void WindowManager::scrollDown() {
    currentTerminal().offsetDownward();
}

void WindowManager::moveCursorLeft() {
    currentTerminal().moveCursorLeftward();
}

void WindowManager::moveCursorRight() {
    currentTerminal().moveCursorRightward();
}

void WindowManager::moveCursorToBeginning() {
    currentTerminal().moveCursorToStart();
}

void WindowManager::moveCursorToEnd() {
    currentTerminal().moveCursorToEnd();
}

void WindowManager::scrollPageDown() {
    currentTerminal().focusOnCommandLine();
}

void WindowManager::scrollPageUp() {
    currentTerminal().focusOnTopOfBuffer();
}

void WindowManager::moveCursorToBeginningOfWord() {
    currentTerminal().moveCursorToBeginningOfWord();
}

void WindowManager::moveCursorToEndOfWord() {
    currentTerminal().moveCursorToEndOfWord();
}

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

void WindowManager::_putStr(const u8 begin, const i8* str) const {
    for (u8 i = begin; str[i] != 0; ++i) {
        vga::putChar(vga::Char(str[i]), i, 0, vga::Color::Carbon);
    }
}

void WindowManager::_putNbr(const u8 begin, u32 nbr) const {
    i8  buf[32];
    u32 cur = 32;

    if (nbr == 0) {
        vga::putChar('0', begin, 0, vga::Color::Carbon);
        return;
    }
    while (nbr) {
        --cur;
        buf[cur] = '0' + (nbr % 10);
        nbr /= 10;
    }

    for (u32 i = cur; i < 32; i++) {
        vga::putChar(buf[i], begin + i - cur, 0, vga::Color::Carbon);
    }
}

void WindowManager::_putTitle() const {
    _putStr(0, KERNEL_NAME);
    vga::putChar(vga::Char::Heart, 11, 0, vga::Color::Crimson);
    vga::putChar(vga::Char::Hash, 13, 0, vga::Color::Carbon);
    _putNbr(14, (u32)m_currentTerminal);

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