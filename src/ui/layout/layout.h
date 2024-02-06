/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:42:17 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 15:17:35 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

enum class TranslateResult: u8 {
    Print,
    Ignore,
    Escape,

    SpecialAction,

    Invalid
};

struct KeyEvent;

class Layout {
public:
    virtual ~Layout() = default;

protected:

    virtual
    TranslateResult translate(const u8 scancode, KeyEvent& out) = 0;

};

} // namespace ui