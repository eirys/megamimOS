/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paging.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:43:18 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 15:04:19 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace mem {

void init(const u32 upperBound);

u32 kalloc(void);
void kfree(u32 physicalFrame);
void kinit(u32 maxFreePages);

} // namespace mem