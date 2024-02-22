/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kalloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:31:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 16:41:13 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace mem {

u32     kalloc();
void    kfree(u32 physicalFrame);
void    kinit(u32 maxFreePages);

void*   valloc();

} // namespace mem