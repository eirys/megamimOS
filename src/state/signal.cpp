/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:12:48 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:13:03 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "panic.h"
#include "window_manager.h"

namespace kfs {

/* -------------------------------------------- */
/*                    STATIC                    */
/* -------------------------------------------- */

static
void _basicSignalHandler() {
    ui::WindowManager::get() << "Signal received!";
}

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

void SignalManager::init() {
    registerHandler(kfs::Signal::User1, _basicSignalHandler);
}

/* -------------------------------------------- */

bool SignalManager::schedule(Signal signal) {
    if (m_pending & (1 << (u32)signal)) {
        return false;
    }

    m_pending |= (1 << (u32)signal);
    return true;
}

void SignalManager::update() {
    for (u32 rawSignal = (u32)Signal::First; rawSignal <= (u32)Signal::Last; ++rawSignal) {
        if (m_pending & (1 << rawSignal)) {
            SignalHandler handler = m_handlers[rawSignal];
            if (!handler) {
                beginKernelPanic("Received a signal without an associated handler.");
            }

            handler();
        }
    }

    m_pending = 0;
}

void SignalManager::registerHandler(Signal signal, SignalHandler handler) {
    m_handlers[(u32)signal] = handler;
}

}
