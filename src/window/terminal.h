/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:42:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 20:03:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include "utils.h"

/**
 * @brief Virtual console to run a pseudo-shell.
*/
class Terminal final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Terminal(): m_cursor(0U, vga::HEIGHT - 2U) {}

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
    void putString(const char* str) const {
        vga::putString(str, m_cursor.m_x, m_cursor.m_y, m_color);
    }

    inline
    void putChar(const vga::Char character) const {
        vga::putChar(character, m_cursor.m_x, m_cursor.m_y, m_color);
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    // History         m_history;
    vga::Cursor     m_cursor;
    vga::Color      m_color;

}; // class Terminal

Terminal& operator<<(Terminal& term, const char* str) {
    term.putString(str);
    return term;
}

Terminal& operator<<(Terminal& term, const vga::Char character) {
    term.putChar(character);
    return term;
}