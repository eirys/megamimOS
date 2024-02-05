/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 20:10:00 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "terminal.h"

enum class TerminalID: uint8_t {
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
        for (uint8_t id = 0; id < TERMINAL_COUNT; id++) {
            const uint8_t colorRaw = (uint8_t)id + (uint8_t)vga::Color::Indigo;
            m_terminals[id].setColor((vga::Color)colorRaw);
        }
    }

    ~WindowManager() = default;

    WindowManager(WindowManager&& other) = delete;
    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;

    /* ---------------------------------------- */

    inline
    Terminal& operator[](const TerminalID id) {
        return m_terminals[static_cast<uint8_t>(id)];
    }

    inline
    const Terminal& operator[](const TerminalID id) const {
        return m_terminals[static_cast<uint8_t>(id)];
    }

    /* ---------------------------------------- */

    inline
    void switchTo(const TerminalID id) {
        m_current = id;
    }

    inline
    Terminal& currentTerminal() {
        return m_terminals[static_cast<uint8_t>(m_current)];
    }

    inline
    const Terminal& currentTerminal() const {
        return m_terminals[static_cast<uint8_t>(m_current)];
    }

    /* ---------------------------------------- */

    inline
    void write(const char* str) const {
        m_terminals[static_cast<uint8_t>(m_current)].putString(str);
    }

    inline
    void write(const vga::Char character) const {
        m_terminals[static_cast<uint8_t>(m_current)].putChar(character);
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static const constexpr uint8_t TERMINAL_COUNT = enumSize<TerminalID>();

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    Terminal    m_terminals[TERMINAL_COUNT];
    TerminalID  m_current = TerminalID::First;

}; // class WindowManager

WindowManager& operator<<(WindowManager& wm, const char* str) {
    wm.write(str);
    return wm;
}

WindowManager& operator<<(WindowManager& wm, const vga::Char character) {
    wm.write(character);
    return wm;
}