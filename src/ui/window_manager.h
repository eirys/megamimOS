/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/12 01:35:43 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "terminal.h"
#include "key_event.h"

namespace ui {

class WindowManager final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    WindowManager() {
        for (u8 id = 0; id < TERMINAL_COUNT; id++) {
            const u8 colorRaw = (u8)id + (u8)vga::Color::Indigo;
            m_terminals[id].setColor((vga::Color)colorRaw);
            m_terminals[id].init(id);
        }
        currentTerminal().draw();
    }

    ~WindowManager() = default;

    WindowManager(WindowManager&& other) = delete;
    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;

    /* ---------------------------------------- */

    inline
    void draw() const {
        currentTerminal().draw();
    }

    /* ---------------------------------------- */

    inline
    void switchToNext() {
        m_currentTerminal = (m_currentTerminal + 1) % TERMINAL_COUNT;
    }

    inline
    void switchToPrevious() {
        m_currentTerminal = (m_currentTerminal + TERMINAL_COUNT - 1) % TERMINAL_COUNT;
    }

    inline
    Terminal& currentTerminal() {
        return m_terminals[static_cast<u8>(m_currentTerminal)];
    }

    inline
    const Terminal& currentTerminal() const {
        return m_terminals[static_cast<u8>(m_currentTerminal)];
    }

    /* ---------------------------------------- */

    inline
    void write(const i8* str) {
        currentTerminal() << str;
    }

    inline
    void write(const vga::Char character) {
        currentTerminal() << character;
    }

    /* ---------------------------------------- */

    inline
    void eraseChar() {
        currentTerminal().eraseChar();
    }

    inline
    void deleteChar() {
        currentTerminal().deleteChar();
    }

    inline
    void newLine() {
        currentTerminal().insertNewline();
    }

    inline
    void prompt() {
        currentTerminal().prompt();
    }

    /* ---------------------------------------- */

    inline
    void scrollUp() {
        currentTerminal().offsetUpward();
    }

    inline
    void scrollDown() {
        currentTerminal().offsetDownward();
    }

    inline
    void moveCursorLeft() {
        currentTerminal().moveCursorLeftward();
    }

    inline
    void moveCursorRight() {
        currentTerminal().moveCursorRightward();
    }

    inline
    void moveCursorToBeginning() {
        currentTerminal().moveCursorToStart();
    }

    inline
    void moveCursorToEnd() {
        currentTerminal().moveCursorToEnd();
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 TERMINAL_COUNT = 5U;

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    Terminal    m_terminals[TERMINAL_COUNT];
    u8          m_currentTerminal = 0U;

}; // class WindowManager

inline
WindowManager& operator<<(WindowManager& wm, const i8* str) {
    wm.write(str);
    return wm;
}

inline
WindowManager& operator<<(WindowManager& wm, const vga::Char character) {
    wm.write(character);
    return wm;
}

} // namespace ui