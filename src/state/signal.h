/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:37:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:38:01 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.h"
#include "types.h"

namespace kfs {

/**
 * @brief A signal that can be delivered.
 */
enum class Signal {
    User1,     // A user-defined signal.
    User2,     // A user-defined signal.

    First = User1,
    Last = User2,
};

/**
 * @brief The signal manager is responsible for handling signals within
 * the kernel.
 *
 * @note When a signal is scheduled to be delivered within the kernel, a
 * routine in the signal manager is invoked to handle the signal.
 *
 * @note The default routine is always triggers a kernel panic to avoid
 * undefined behavior.
 */
class SignalManager final {
public:
    /* ---------------------------------------- */
    /*                 TYPEDEFS                 */
    /* ---------------------------------------- */

    /// The signal handler is a function that is invoked when a signal
    /// is delivered.
    using SignalHandler = void(*)();

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    ~SignalManager() = default;

    SignalManager(SignalManager&& other) = delete;
    SignalManager(const SignalManager& other) = delete;
    SignalManager& operator=(SignalManager&& other) = delete;
    SignalManager& operator=(const SignalManager& other) = delete;

    /* ---------------------------------------- */

    static void init();

    /* ---------------------------------------- */

    /**
     * @brief Registers a signal handler for a given signal.
    */
    static void registerHandler(Signal signal, SignalHandler handler);

    /**
     * @brief Schedules a signal to be delivered to the appropriate signal
     * handler on the next tick.
     */
    static bool schedule(Signal signal);

    /**
     * @brief Updates the signal manager, delivering any pending signals
     * to the appropriate signal handlers.
     */
    static void update();


private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u32    SIGNAL_COUNT = enumSize<Signal>();

    /**
     * @brief The signal handlers for each signal.
    */
    static SignalHandler    m_handlers[SIGNAL_COUNT];

    /**
     * @brief A bitfield of pending signals.
     *
     * @note Each pending signal is represented by a bit in the bitfield.
    */
    static u32              m_pending;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    SignalManager() = default;

};

} // namespace kfs