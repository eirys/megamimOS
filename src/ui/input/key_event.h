/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:13:09 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 15:36:10 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "keys.h"
# include "utils.h"
# include "vga.h"

namespace ui {

enum class Action: u8 {
    Released,
    Pressed,
    Repeat
};

/**
 * @brief Represents a key event.
 * Used to store the state of a key and the translater character it represents.
*/
struct KeyEvent {
    Key         m_key       = Key::Unknown;
    Action      m_action    = Action::Released;
    vga::Char   m_character = vga::Char::Empty;

    bool        m_uppercase = false;
    bool        m_control   = false;
    bool        m_alt       = false;
    bool        m_altGr     = false;
};

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/**
 * @brief Returns whether the input is pressed or released.
 */
static inline
Action isPressed(const u8 input) {
    return (input & 0x80) ? Action::Released : Action::Pressed;
}

} // namespace ui