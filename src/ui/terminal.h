/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 02:36:08 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "vga.h"
# include "commands.h"

namespace ui {

/**
 * @brief Virtual console to run a pseudo-shell.
*/
class Terminal final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Terminal() = default;
    Terminal(const Terminal& other) = default;
    Terminal& operator=(const Terminal& other) = default;
    ~Terminal() = default;

    Terminal(Terminal&& other) = delete;
    Terminal& operator=(Terminal&& other) = delete;

    /* ---------------------------------------- */

    void        init(const vga::Color color);
    void        prompt();
    void        draw() const;
    Command     getCommand() const;

    /* ---------------------------------------- */

    void        putString(const i8* str);
    void        putNbr(u32 nbr);
    void        putChar(const vga::Char character);

    /* ------------ ADVANCED INPUT ------------ */

    void        insertNewline();
    void        resetInner();
    void        deleteChar();
    void        eraseChar();
    void        eraseLine();

    /* ---------------- SCROLL ---------------- */

    void        focusOnCommandLine();
    void        focusOnTopOfBuffer();
    void        offsetDownward();
    void        offsetUpward();
    void        moveCursorLeftward();
    void        moveCursorRightward();
    void        moveCursorToStart();
    void        moveCursorToEnd();
    void        moveCursorToBeginningOfWord();
    void        moveCursorToEndOfWord();

    /* ---------------- GETTER ---------------- */

    vga::Color  getColor() const;

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8     SCREEN_HEIGHT = vga::HEIGHT - 1;
    static constexpr u8     TERMINAL_HEIGHT = vga::HEIGHT * 2U;
    static constexpr u8     LINE_BEGIN = 2U;

    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    vga::Char       m_data[vga::WIDTH * TERMINAL_HEIGHT] = { vga::Char::Empty };
    vga::Color      m_color = vga::Color::Immaculate;
    u8              m_scrollAmount = 0U;

    u8              m_cursor = 0U;
    u8              m_lineLength = LINE_BEGIN;
    bool            m_isPrompt = false;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void            _scrollUp();
    void            _offsetLineByOneToRight();
    void            _offsetLineByOneToLeft();

}; // class Terminal

Terminal& operator<<(Terminal& term, const i8* str);
Terminal& operator<<(Terminal& term, const vga::Char character);
Terminal& operator<<(Terminal& term, const u32 nbr);

} // namespace ui