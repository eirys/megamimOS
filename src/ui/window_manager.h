/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 10:17:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "terminal.h"
# include "key_event.h"

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
            m_terminals[id].init();
        }
        currentTerminal().draw();
        _putTitle();
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
        _putTitle();
    }

    inline
    void switchToPrevious() {
        m_currentTerminal = (m_currentTerminal + TERMINAL_COUNT - 1) % TERMINAL_COUNT;
        _putTitle();
    }

    inline
    Terminal& currentTerminal() {
        return m_terminals[m_currentTerminal];
    }

    inline
    const Terminal& currentTerminal() const {
        return m_terminals[m_currentTerminal];
    }

    /* ---------------------------------------- */

    void handleInput() {
        // CommandHandler command;
    }

    /* ---------------------------------------- */

    /**
     * @brief Writes a str to terminal internal buffer.
     */
    inline
    void write(const i8* str) {
        currentTerminal() << str;
    }

    /**
     * @brief Writes a char to terminal internal buffer.
     */
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
    void eraseLine() {
        currentTerminal().eraseLine();
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

    inline
    void scrollPageDown() {
        currentTerminal().focusOnCommandLine();
    }

    inline
    void scrollPageUp() {
        currentTerminal().focusOnTopOfBuffer();
    }

    inline
    void moveCursorToBeginningOfWord() {
        currentTerminal().moveCursorToBeginningOfWord();
    }

    inline
    void moveCursorToEndOfWord() {
        currentTerminal().moveCursorToEndOfWord();
    }

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 TERMINAL_COUNT = 5U;

    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    Terminal    m_terminals[TERMINAL_COUNT];
    u8          m_currentTerminal = 0U;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void _putStr(const u8 begin, const i8* str) const {
        for (u8 i = begin; str[i] != 0; ++i) {
            vga::putChar(vga::Char(str[i]), i, 0, vga::Color::Carbon);
        }
    }

    inline
    void _putNbr(const u8 begin, u32 nbr) const {
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

    void _putTitle() const {
        _putStr(0, "megamimsOS");
        vga::putChar(vga::Char::Heart, 11, 0, vga::Color::Crimson);
        vga::putChar(vga::Char::Hash, 13, 0, vga::Color::Carbon);
        _putNbr(14, (u32)m_currentTerminal);

        for (u8 i = 0; i < vga::WIDTH; ++i) {
            vga::setBgColor(i, 0, vga::Color::Cloud);
        }
    }

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