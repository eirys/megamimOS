/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:58:19 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 00:59:09 by etran            ###   ########.fr       */
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

    Empty,
    Unknown,

    First = Clear,
    Last = Version
};

} // namespace ui