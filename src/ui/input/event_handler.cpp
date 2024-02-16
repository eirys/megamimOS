/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:58:04 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 02:56:53 by etran            ###   ########.fr       */
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

void EventHandler::insertScancode(const u8 scancode) {
    if (m_scancodeCount < MAX_SCANCODES) {
        m_scancodes[m_scancodeCount] = scancode;
        ++m_scancodeCount;
    }
}

/* -------------------------------------------- */

void EventHandler::copyTo(u8* out, u8& count) {
    lib::memcpy(out, m_scancodes, m_scancodeCount);
    count = m_scancodeCount;
    m_scancodeCount = 0;
}

} // namespace ui