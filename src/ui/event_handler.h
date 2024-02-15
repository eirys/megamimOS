/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:29:58 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 21:41:54 by etran            ###   ########.fr       */
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

    static void     init();
    static void     handle();

    /* ---------- EXTERNAL MODIFIERS ---------- */

    static void     setScancode(u8 scancode);

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    static u8       m_scancode = 0U;
    static bool     m_hasScancode = false;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    EventHandler() = default;

    /* ---------------------------------------- */

    static void     _handleCommand();
    static void     _handleInput(const ui::KeyEvent& event);

}; // class EventHandler

} // namespace ui