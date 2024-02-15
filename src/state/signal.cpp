#include "signal.h"
#include "panic.h"

namespace kfs {

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
