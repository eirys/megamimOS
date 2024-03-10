/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scancode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:32:55 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 17:01:45 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "key_event.h"
# include "modifier.h"

namespace ui {

Key translateScancode(
    const u8 input,
    const bool isExtended,
    const Modifier modifiers
);

bool setModifiers(
    Modifier& modifiers,
    const Key key,
    const bool isPressed
);

} // namespace ui