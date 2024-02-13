/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 22:22:20 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "terminal.h"
# include "key_event.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "No name :("
#endif

#include "debug.h"

namespace ui {

class WindowManager final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    ~WindowManager() = default;

    WindowManager(WindowManager&& other) = delete;
    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;

    /* ---------------------------------------- */

    static
    void init() {
        m_currentTerminal = 0U;
        for (u8 id = 0; id < TERMINAL_COUNT; id++) {
            const u8 colorRaw = (u8)id + (u8)vga::Color::Indigo;
            m_terminals[id].init((vga::Color)colorRaw);
        }
        currentTerminal().draw();
        _putTitle();
    }


    static
    WindowManager* get() {
        static WindowManager wm;
        return &wm;
    }

    /* ---------------------------------------- */

    static inline
    void draw() {
        currentTerminal().draw();
    }

    /* ---------------------------------------- */

    static inline
    void switchToNext() {
        m_currentTerminal = (m_currentTerminal + 1) % TERMINAL_COUNT;
        _putTitle();
    }

    static inline
    void switchToPrevious() {
        m_currentTerminal = (m_currentTerminal + TERMINAL_COUNT - 1) % TERMINAL_COUNT;
        _putTitle();
    }

    static inline
    Terminal& currentTerminal() {
        return m_terminals[m_currentTerminal];
    }

    /* ---------------------------------------- */

    static
    void handleInput() {
        currentTerminal().getCommandLine();
    }

    /* ---------------------------------------- */

    /**
     * @brief Writes a str to terminal internal buffer.
     */
    static inline
    void write(const i8* str) {
        currentTerminal() << str;
    }

    /**
     * @brief Writes a char to terminal internal buffer.
     */
    static inline
    void write(const vga::Char character) {
        currentTerminal() << character;
    }

    /* ---------------------------------------- */

    static inline
    void eraseChar() {
        currentTerminal().eraseChar();
    }

    static inline
    void eraseLine() {
        currentTerminal().eraseLine();
    }

    static inline
    void deleteChar() {
        currentTerminal().deleteChar();
    }

    static inline
    void newLine() {
        currentTerminal().insertNewline();
    }

    static inline
    void prompt() {
        currentTerminal().prompt();
    }

    /* ---------------------------------------- */

    static inline
    void scrollUp() {
        currentTerminal().offsetUpward();
    }

    static inline
    void scrollDown() {
        currentTerminal().offsetDownward();
    }

    static inline
    void moveCursorLeft() {
        currentTerminal().moveCursorLeftward();
    }

    static inline
    void moveCursorRight() {
        currentTerminal().moveCursorRightward();
    }

    static inline
    void moveCursorToBeginning() {
        currentTerminal().moveCursorToStart();
    }

    static inline
    void moveCursorToEnd() {
        currentTerminal().moveCursorToEnd();
    }

    static inline
    void scrollPageDown() {
        currentTerminal().focusOnCommandLine();
    }

    static inline
    void scrollPageUp() {
        currentTerminal().focusOnTopOfBuffer();
    }

    static inline
    void moveCursorToBeginningOfWord() {
        currentTerminal().moveCursorToBeginningOfWord();
    }

    static inline
    void moveCursorToEndOfWord() {
        currentTerminal().moveCursorToEndOfWord();
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 TERMINAL_COUNT = 5U;

    static Terminal    m_terminals[TERMINAL_COUNT];
    static u8          m_currentTerminal;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    WindowManager() = default;

    static
    void _putStr(const u8 begin, const i8* str) {
        for (u8 i = begin; str[i] != 0; ++i) {
            vga::putChar(vga::Char(str[i]), i, 0, vga::Color::Carbon);
        }
    }

    static inline
    void _putNbr(const u8 begin, u32 nbr) {
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

    static
    void _putTitle() {
        _putStr(0, KERNEL_NAME);
        vga::putChar(vga::Char::Heart, 11, 0, vga::Color::Crimson);
        vga::putChar(vga::Char::Hash, 13, 0, vga::Color::Carbon);
        _putNbr(14, (u32)m_currentTerminal);

        const vga::Color  terminalColor = currentTerminal().getColor();
        for (u8 i = 0; i < vga::WIDTH; ++i) {
            vga::setBgColor(i, 0, terminalColor);
        }
    }

}; // class WindowManager

Terminal    WindowManager::m_terminals[TERMINAL_COUNT];
u8          WindowManager::m_currentTerminal;

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