
#pragma once

#include "utils.h"
#include "types.h"

namespace kfs {

/// A signal that can be delivered.
enum class Signal {
    /// A user-defined signal.
    User1,
    /// A user-defined signal.
    User2,

    First = User1,
    Last = User2,
};

/// The signal manager is responsible for handling signals within
/// the kernel.
///
/// When a signal is scheduled to be delivered within the kernel, a
/// routine in the signal manager is invoked to handle the signal.
///
/// The default routine is always triggers a kernel panic to avoid
/// undefined behavior.
class SignalManager final {
public:
    /// The signal handler is a function that is invoked when a signal
    /// is delivered.
    using SignalHandler = void(*)();

    /// Sets the signal handler for a given signal.
    void registerHandler(Signal signal, SignalHandler handler);

    /// Schedules a signal to be delivered to the appropriate signal
    /// handler on the next tick.
    bool schedule(Signal signal);

    /// Updates the signal manager, delivering any pending signals
    /// to the appropriate signal handlers.
    void update();

    /// Returns the global signal manager.
    static inline
    SignalManager& get() {
        static SignalManager instance;
        return instance;
    }

private:
    /// The signal handlers for each signal.
    SignalHandler m_handlers[enumSize<Signal>()] = { 0 };
    /// A bitfield of pending signals.
    ///
    /// Each pending signal is represented by a bit in the bitfield.
    u32 m_pending = 0;
};

}
