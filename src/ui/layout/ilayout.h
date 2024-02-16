/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilayout.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:13:15 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:07:37 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace ui {

enum class TranslateResult: u8 {
    Continue,
    Success,
    Invalid
};

struct KeyEvent;

class ILayout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    virtual ~ILayout() = default;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    virtual
    TranslateResult translate(const u8 scancode, KeyEvent& out) = 0;

protected:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    ILayout() = default;

}; // class ILayout

} // namespace ui