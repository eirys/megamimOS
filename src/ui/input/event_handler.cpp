/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:58:04 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:25:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"
#include "window_manager.h"
#include "command_handler.h"
#include "lib.h"

#include "debug.h"

namespace ui {

/* -------------------------------------------- */
/*                STATIC MEMBERS                */
/* -------------------------------------------- */

u8      EventHandler::m_scancodes[EventHandler::MAX_SCANCODES];
u8      EventHandler::m_scancodeCount;

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

void EventHandler::init() {
    m_scancodeCount = 0;
}

/// @brief Inserts a scancode into the event handler.
/// @attention This function must be called while interrupts are disabled.
void EventHandler::insertScancode(const u8 scancode) {
    if (m_scancodeCount < MAX_SCANCODES) {
        m_scancodes[m_scancodeCount] = scancode;
        ++m_scancodeCount;
    }
}

/* -------------------------------------------- */

/// @brief Copies the scane-codes currently buffered in the event
/// handler to the provided buffer.
/// @attention This function must be called while interrupts are disabled.
/// @note The mumber of bytes copied is written to `count`.
/// @note Note that at most `MAX_SCANCODES` bytes can be written
/// regardless of the initial value of `count`.
void EventHandler::copyTo(u8* out, u8& count) {
    lib::memcpy(out, m_scancodes, m_scancodeCount);
    count = m_scancodeCount;
    m_scancodeCount = 0;
}

} // namespace ui