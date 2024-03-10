/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:38:06 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:38:11 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pit.h"
#include "core.h"

namespace kfs {

u32 microsecondsSinceBoot;

void sleep(u32 microseconds) {
    u32 end = microsecondsSinceBoot + microseconds;
    while (microsecondsSinceBoot < end) {
        core::hlt();
    }
}

} // namespace kfs