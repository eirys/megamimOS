/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:14:28 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 14:38:14 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "vga.h"

namespace ui {

static constexpr u8 HISTORY_SIZE = 10;

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

    inline
    void replaceLine(const i8* line, const u8 lineIndex) {
        u8 index = 0;
        while (line[index] && index < vga::WIDTH) {
            m_data[lineIndex][index] = line[index];
            index++;
        }
        m_data[lineIndex][index] = '\0';
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u8  m_data[HISTORY_SIZE][vga::WIDTH + 1];
    u8  m_currentLine = 0;

};

/**
 * @brief Wrapper for a shell history.
 * The history is a buffer of 10 lines of vga::WIDTH characters.
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


private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    HistoryInternal     m_internal;

}; // class History

} // namespace ui