/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   azerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:20:50 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 16:04:52 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "key_event.h"
# include "modifier.h"
# include "ilayout.h"
# include "vga.h"

namespace ui {

/**
 * @brief Scancode interpreter for the FR-AZERTY layout.
 */
class AzertyLayout final: public ILayout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    AzertyLayout() = default;
    ~AzertyLayout() = default;

    AzertyLayout(AzertyLayout&& other) = delete;
    AzertyLayout(const AzertyLayout& other) = delete;
    AzertyLayout& operator=(AzertyLayout&& other) = delete;
    AzertyLayout& operator=(const AzertyLayout& other) = delete;

    /* ---------------------------------------- */

    static
    AzertyLayout&       get();

    /* ---------------------------------------- */

    TranslateResult     translate(const u8 input, KeyEvent& out) override;

private:
    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    Modifier    m_modifiers = Modifier::None;
    Accent      m_accent = Accent::None;
    bool        m_isExtended = false;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void        _updateAccent(KeyEvent& out);
    bool        _setAccent(
        const Key key,
        const bool isUppercase,
        const bool isAltGr);

}; // class AzertyLayout

} // namespace ui