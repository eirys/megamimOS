/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:47:09 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 14:43:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace pit {

/// The number of microseconds between each tick
/// emitted by the PIT.
extern u32 tickDurationMicros;

void init(u32 frequency);

}  // namespace pit
