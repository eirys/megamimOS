/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 17:48:00 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "terminal.h"
#include "key_event.h"

namespace ui {

enum class TerminalID: u8 {
    User0 = 0,
    User1,
    User2,
    User3,
    User4,

    First = User0,
    Last = User4
};

class WindowManager final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    WindowManager() {
        for (u8 id = 0; id < TERMINAL_COUNT; id++) {
            const u8 colorRaw = (u8)id + (u8)vga::Color::Indigo;
            m_terminals[id].setColor((vga::Color)colorRaw);
            m_terminals[id].setId(id);
        }
        currentTerminal().reset();
    }

    ~WindowManager() = default;

    WindowManager(WindowManager&& other) = delete;
    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;

    /* ---------------------------------------- */

    inline
    Terminal& operator[](const TerminalID id) {
        return m_terminals[static_cast<u8>(id)];
    }

    inline
    const Terminal& operator[](const TerminalID id) const {
        return m_terminals[static_cast<u8>(id)];
    }

    /* ---------------------------------------- */

    inline
    void switchToNext() {
        m_current = static_cast<TerminalID>((static_cast<u8>(m_current) + 1) % TERMINAL_COUNT);
        currentTerminal().reset();
    }

    inline
    void switchToPrevious() {
        m_current = static_cast<TerminalID>((static_cast<u8>(m_current) + TERMINAL_COUNT - 1) % TERMINAL_COUNT);
        currentTerminal().reset();
    }

    inline
    Terminal& currentTerminal() {
        return m_terminals[static_cast<u8>(m_current)];
    }

    inline
    const Terminal& currentTerminal() const {
        return m_terminals[static_cast<u8>(m_current)];
    }

    /* ---------------------------------------- */

    inline
    void write(const char* str) {
        currentTerminal() << str;
    }

    inline
    void write(const vga::Char character) {
        currentTerminal() << character;
    }

    inline
    void eraseChar() {
        currentTerminal().eraseChar();
    }

    inline
    void newLine() {
        currentTerminal().insertNewline();
    }

    inline
    void scrollUp() {
        currentTerminal().offsetUpward();
    }

    inline
    void scrollDown() {
        currentTerminal().offsetDownward();
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 TERMINAL_COUNT = enumSize<TerminalID>();

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    Terminal    m_terminals[TERMINAL_COUNT];
    TerminalID  m_current = TerminalID::First;

}; // class WindowManager

inline
WindowManager& operator<<(WindowManager& wm, const char* str) {
    wm.write(str);
    return wm;
}

inline
WindowManager& operator<<(WindowManager& wm, const vga::Char character) {
    wm.write(character);
    return wm;
}

} // namespace ui