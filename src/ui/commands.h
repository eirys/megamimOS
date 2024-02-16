/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:58:19 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:32:47 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

/* -------------------------------------------- */
/*                     ENUMS                    */
/* -------------------------------------------- */

enum class Command: u8 {
    Clear   = 0,
    Help,
    Panic,
    Reboot,
    Halt,
    Version,
    SendSignal,

    Empty,
    Unknown,

    First = Clear,
    Last = SendSignal
};

} // namespace ui