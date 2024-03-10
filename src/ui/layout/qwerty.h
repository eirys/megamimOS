/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:44:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 14:14:41 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "key_event.h"
# include "modifier.h"
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

    static
    QwertyLayout&       get();

    /* ---------------------------------------- */

    TranslateResult     translate(const u8 input, KeyEvent& out) override;

private:
    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    Modifier    m_modifiers = Modifier::None;
    bool        m_isExtended = false;

}; // class QwertyLayout

} // namespace ui