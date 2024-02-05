/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:42:17 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 23:44:40 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

struct KeyEvent;

class Layout {
public:
    virtual ~Layout() = default;

protected:

    virtual
    bool translate(const u8 scancode, KeyEvent& out) = 0;

};

} // namespace ui