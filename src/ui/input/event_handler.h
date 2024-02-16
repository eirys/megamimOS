/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:29:58 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 02:59:41 by etran            ###   ########.fr       */
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

    /// Inserts a scancode into the event handnler.
    ///
    /// # Critical Section
    ///
    /// This function must be called while interrupts are disabled.
    static void     insertScancode(const u8 scancode);

    /* ---------------------------------------- */

    /// Copies the scane-codes currently buffered in the event
    /// handler to the provided buffer.
    ///
    /// The mumber of bytes copied is written to `count`.
    ///
    /// Note that at most `MAX_SCANCODES` bytes can be written
    /// regardless of the initial value of `count`.
    ///
    /// # Critical Section
    ///
    /// This function must be called while interrupts are disabled.
    static void    copyTo(u8* out, u8& count);

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