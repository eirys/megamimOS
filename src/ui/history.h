/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:14:28 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 21:20:21 by etran            ###   ########.fr       */
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
static constexpr u8 HISTORY_SIZE = vga::HEIGHT * 2U;

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

    /**
     * @brief Append a line to the data buffer.
    */
    void putChar(const u8 c) {
        // _moveDataUp();
        // if (m_offset < HISTORY_SIZE) {
        //     lib::strcpy(m_data[HISTORY_SIZE - m_offset], line);
        //     ++m_offset;
        // } else {
        // }
    }

    /**
     * @brief Retrieve a line from the history.
    */
    inline
    u8 copy(u8* buffer) {
        if (m_offset != 0U) {
            lib::strcpy(buffer, m_data[m_offset]);
            --m_offset;
            return (u8)lib::strlen(buffer);
        }
        return 0U;
    }

    inline
    void clear() {
        m_offset = 0U;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u8  m_data[HISTORY_SIZE][vga::WIDTH + 1];
    u8  m_offset = 0U;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void _moveDataUp() {
        for (u16 i = 0; i < HISTORY_SIZE - 1; i++) {
            lib::strcpy(m_data[i], m_data[i + 1]);
        }
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
    void clear() {
        m_internal.clear();
        m_offset = 0U;
    }

    // inline
    // void (u8* buffer) {
    //     m_internal.pop(buffer);
    // }

    inline
    void appendLine(const u8* line) {
        // m_internal.appendLine(line);
    }

    inline
    void moveUp() {
        if (m_offset <= HISTORY_SIZE) {
            ++m_offset;
        }
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    HistoryInternal     m_internal;
    u8                  m_offset = 0U;

}; // class History

} // namespace ui