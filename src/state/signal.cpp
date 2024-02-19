/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:12:48 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:40:36 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "panic.h"
#include "window_manager.h"

namespace kfs {

/* -------------------------------------------- */
/*                STATIC MEMBERS                */
/* -------------------------------------------- */

SignalManager::SignalHandler    SignalManager::m_handlers[SIGNAL_COUNT] = { nullptr };
u32                             SignalManager::m_pending = 0;

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

static
void _basicSignalHandler() {
    ui::WindowManager::get() << "Signal received!";
}

void SignalManager::init() {
    registerHandler(Signal::User1, _basicSignalHandler);
}

/* -------------------------------------------- */

void SignalManager::registerHandler(Signal signal, SignalHandler handler) {
    m_handlers[(u32)signal] = handler;
}

bool SignalManager::schedule(Signal signal) {
    if (m_pending & (1 << (u32)signal)) {
        return false;
    }

    m_pending |= (1 << (u32)signal);
    return true;
}

void SignalManager::update() {
    for (u32 rawSignal = (u32)Signal::First; rawSignal < SIGNAL_COUNT; ++rawSignal) {
        if (m_pending & (1 << rawSignal)) {
            SignalHandler handler = m_handlers[rawSignal];
            if (!handler) {
                return beginKernelPanic("Received a signal without an associated handler.");
            }

            handler();
        }
    }

    m_pending = 0;
}

} // namespace kfs