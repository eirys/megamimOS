/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:47:51 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 00:15:46 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

/**
 * @brief Corresponds to a key on a generic keyboard.
 * @note The values are based on the US keyboard layout.
 * @note The numpad keys are meant to be included.
 */
enum class Key: u8 {
    Unknown,
    Escape,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    Key0,
    Minus,
    Equals,
    Backspace,
};

} // namespace ui
