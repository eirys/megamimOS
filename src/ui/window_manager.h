/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:57:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 14:02:45 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "terminal.h"

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

    static WindowManager&   get();

    static void         init();
    static void         draw();
    static Command      getCommand();

    /* ---------------------------------------- */

    static void         switchToNext();
    static void         switchToPrevious();

    /* ---------------------------------------- */

    static void         write(const i8* str);
    static void         write(const vga::Char character);

    /* ---------------------------------------- */

    static void         eraseChar();
    static void         eraseLine();
    static void         deleteChar();
    static void         newLine();
    static void         prompt();

    /* ---------------------------------------- */

    static void         scrollUp();
    static void         scrollDown();
    static void         moveCursorLeft();
    static void         moveCursorRight();
    static void         moveCursorToBeginning();
    static void         moveCursorToEnd();
    static void         scrollPageDown();
    static void         scrollPageUp();
    static void         moveCursorToBeginningOfWord();
    static void         moveCursorToEndOfWord();
    static void         clearScreen();

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

    /* ---------------------------------------- */

    static Terminal&    _currentTerminal();

    static void         _putStr(u8 x, u8 y, const i8* str);
    static void         _putNbr(u8 x, u8 y, u32 nbr);
    static void         _putTitle();

}; // class WindowManager

WindowManager& operator<<(WindowManager& wm, const i8* str);
WindowManager& operator<<(WindowManager& wm, const vga::Char character);

} // namespace ui