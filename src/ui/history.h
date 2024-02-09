/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:14:28 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 17:06:12 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "vga.h"
#include "lib.h"

namespace ui {

/**
 * @brief Maximum number of lines in the history.
*/
static constexpr u8 HISTORY_SIZE = vga::HEIGHT * 2;

/**
 * @brief Buffer containing the history of inputs.
 * @note Instead of being written to the VGA buffer,
 * inputs are written to this buffer, and then retrieved by the terminal.
*/
class HistoryInternal final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    HistoryInternal() = default;
    HistoryInternal(const HistoryInternal& other) = default;
    HistoryInternal& operator=(const HistoryInternal& other) = default;
    ~HistoryInternal() = default;

    HistoryInternal(HistoryInternal&& other) = delete;
    HistoryInternal& operator=(HistoryInternal&& other) = delete;

    /* ---------------------------------------- */

    void saveChar(const vga::Char c) {
        m_data[m_cursor.m_y][m_cursor.m_x] = (u8)c;
        if (m_cursor.moveX(1) == CursorPosResult::PastRight) {
            if (m_cursor.moveY(1) == CursorPosResult::PastBottom) {
                _moveDataUp();
                m_cursor.m_y = vga::HEIGHT - 1;
            }
        }
    }

    // inline
    // void retrieve(u8* buffer) const {
    //     for (u8 i = 0; i < vga::HEIGHT; i++) {
    //         lib::strcpy(buffer, m_data[i]);
    //     }
    // }

    inline
    vga::Char getChar(const u8 x, const u8 y) const {
        return (vga::Char)m_data[y][x];
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u8      m_data[HISTORY_SIZE][vga::WIDTH + 1];
    Cursor  m_cursor;
    u8      m_offset = 0U;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void _moveDataUp() {
        for (u16 i = 0; i < HISTORY_SIZE - 1; i++) {
            lib::strcpy(m_data[i], m_data[i + 1]);
        }
        ++m_offset;
    }

};

/**
 * @brief Wrapper for a shell history.
 * The history is a buffer of (vga::HEIGHT * 2) * (vga::WIDTH) characters.
 * It'll be used to remember the scrolled up lines.
 */
class History final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    History() = default;
    History(const History& other) = default;
    History& operator=(const History& other) = default;
    ~History() = default;

    History(History&& other) = delete;
    History& operator=(History&& other) = delete;

    /* ---------------------------------------- */

    inline
    void save(const vga::Char c) {
        m_internal.saveChar(c);
    }

    inline
    vga::Char getChar(const u8 x, const u8 y) const {
        return m_internal.getChar(x, y);
    }

    // inline
    // void putString(const i8* str) {
    //     while (*str)
    //         putChar(vga::Char(*str++));
    // }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    HistoryInternal     m_internal;
    u8                  m_offset = 0U;

}; // class History

} // namespace ui