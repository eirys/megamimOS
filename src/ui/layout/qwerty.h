/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:44:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 17:50:40 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "key_event.h"
# include "ilayout.h"
# include "vga.h"

namespace ui {

/**
 * @brief Scancode interpreter for the US-QWERTY layout.
 */
class QwertyLayout final: public ILayout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    QwertyLayout() = default;
    ~QwertyLayout() = default;

    QwertyLayout(QwertyLayout&& other) = delete;
    QwertyLayout(const QwertyLayout& other) = delete;
    QwertyLayout& operator=(QwertyLayout&& other) = delete;
    QwertyLayout& operator=(const QwertyLayout& other) = delete;

    /* ---------------------------------------- */

    TranslateResult translate(const u8 input, KeyEvent& out) override;

private:
    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    Modifier    m_modifiers = Modifier::None;
    bool        m_isExtended = false;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    bool    _translateKey(u8 makecode, const bool isExtended, Key& out);

    /* ---------------------------------------- */

    void    _setMod(const Modifier mod, const bool pressed);
    void    _setLock(const Modifier mod, const bool pressed);
    bool    _setModifiers(
        const KeyEvent& out,
        const bool isExtended);

}; // class QwertyLayout

} // namespace ui