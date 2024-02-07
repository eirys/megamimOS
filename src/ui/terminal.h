/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 01:26:56 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.h"
#include "input_manager.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "undefined kernel name :("
#endif

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

    inline
    void setColor(const vga::Color color) {
        m_color = color;
    }

    /* ---------------------------------------- */

    inline
    void putString(const i8* str) {
        while (*str)
            putChar(vga::Char(*str++));
    }

    inline
    void putChar(const vga::Char character) {
        vga::putChar(character, m_cursor.m_x, m_cursor.m_y, m_color);
        if (m_cursor.moveX(1U))
            vga::scrollUp(m_color);
        m_cursor.update();
    }

    inline
    void reset() {
        vga::clearBuffer(m_color);
        m_cursor.move(vga::WIDTH / 2U, vga::HEIGHT / 2U);
        putString((i8*)KERNEL_NAME);
        m_cursor.move(0U, vga::HEIGHT - 1U);
        m_cursor.update();
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    // History         m_history;
    // InputManager    m_inputManager;
    vga::Cursor     m_cursor;
    vga::Color      m_color;

}; // class Terminal

Terminal& operator<<(Terminal& term, const i8* str) {
    term.putString(str);
    return term;
}

Terminal& operator<<(Terminal& term, const vga::Char character) {
    term.putChar(character);
    return term;
}

} // namespace ui