/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:31:14 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:40:12 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace kfs {

/// The total number of microseconds since the system booted.
extern u32 microsecondsSinceBoot;

/// Sleeps for the given number of microseconds.
///
/// Note that this function *will* sleep slightly
/// more time than requested. But it is guaranteed to
/// sleep at least the requested time.
void sleep(u32 microseconds);

} // namespace kfs