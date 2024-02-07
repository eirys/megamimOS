/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:42:17 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 19:46:39 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

enum class TranslateResult: u8 {
    Print,
    Ignore,
    Exit,

    SpecialAction,

    Invalid
};

struct KeyEvent;

class Layout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    virtual ~Layout() = default;

protected:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    virtual
    TranslateResult translate(const u8 scancode, KeyEvent& out) = 0;
};

} // namespace ui