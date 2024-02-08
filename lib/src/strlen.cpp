/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:38:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 15:23:19 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

namespace lib {

u32 strlen(const i8* str) noexcept {
    u32 len = 0;
    while (str[len]) ++len;
    return len;
}

} // namespace lib