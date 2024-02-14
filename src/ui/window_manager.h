/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:34:37 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "terminal.h"
# include "vga.h"

namespace ui {

class WindowManager final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    WindowManager();

    ~WindowManager() = default;

    WindowManager(WindowManager&& other) = delete;
    WindowManager(const WindowManager& other) = delete;
    WindowManager& operator=(WindowManager&& other) = delete;
    WindowManager& operator=(const WindowManager& other) = delete;

    /* ---------------------------------------- */

    void            draw() const;

    /* ---------------------------------------- */

    void            switchToNext();
    void            switchToPrevious();

    Terminal&       currentTerminal();
    const Terminal& currentTerminal() const;

    /* ---------------------------------------- */

    void handleInput() {
        // CommandHandler command;
    }

    /* ---------------------------------------- */

    void            write(const i8* str);
    void            write(const vga::Char character);

    /* ---------------------------------------- */

    void            eraseChar();
    void            eraseLine();
    void            deleteChar();
    void            newLine();
    void            prompt();

    /* ---------------------------------------- */

    void            scrollUp();
    void            scrollDown();
    void            moveCursorLeft();
    void            moveCursorRight();
    void            moveCursorToBeginning();
    void            moveCursorToEnd();
    void            scrollPageDown();
    void            scrollPageUp();
    void            moveCursorToBeginningOfWord();
    void            moveCursorToEndOfWord();

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

    void            _putStr(const u8 begin, const i8* str) const;
    void            _putNbr(const u8 begin, u32 nbr) const;
    void            _putTitle() const;

}; // class WindowManager

WindowManager& operator<<(WindowManager& wm, const i8* str);
WindowManager& operator<<(WindowManager& wm, const vga::Char character);

} // namespace ui