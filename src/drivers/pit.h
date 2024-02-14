/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:47:09 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 15:01:39 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace pit {

/* -------------------------------------------- */
/*                   PIT PORTS                  */
/* -------------------------------------------- */

static constexpr const u16 CHANNEL_0 = 0x40;
static constexpr const u16 CHANNEL_1 = 0x41;
static constexpr const u16 CHANNEL_2 = 0x42;
static constexpr const u16 COMMAND = 0x43;

}  // namespace pit