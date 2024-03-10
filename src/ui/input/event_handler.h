/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:29:58 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:16:51 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace ui {

class EventHandler final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    EventHandler(EventHandler&& other) = default;
    EventHandler(const EventHandler& other) = default;
    EventHandler& operator=(EventHandler&& other) = default;
    EventHandler& operator=(const EventHandler& other) = default;
    ~EventHandler() = default;

    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 MAX_SCANCODES = 16;

    /* ---------------------------------------- */

    static void     init();
    static void     insertScancode(const u8 scancode);

    /* ---------------------------------------- */

    static void     copyTo(u8* out, u8& count);

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    static u8   m_scancodes[MAX_SCANCODES];
    static u8   m_scancodeCount;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    EventHandler() = default;

}; // class EventHandler

} // namespace ui