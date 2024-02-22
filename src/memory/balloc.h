/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:31:43 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 15:02:38 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace mem {

void    ballocInit(u32 top, u32 base);
void*   balloc(u32 size, u32 align);
bool    ballocIsConsumed(u32 physicalFrame);

} // namespace mem