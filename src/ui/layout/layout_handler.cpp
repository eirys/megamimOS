/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:31 by etran             #+#    #+#             */
/*   Updated: 2024/02/19 13:25:13 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout_handler.h"

#include "qwerty.h"
#include "azerty.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

ILayout*    LayoutHandler::m_layout[LAYOUT_COUNT] = { nullptr };
Layout      LayoutHandler::m_currentLayout;

void LayoutHandler::init() {
    m_currentLayout = Layout::First;

    m_layout[0] = &QwertyLayout::get();
    m_layout[1] = &AzertyLayout::get();
}

void LayoutHandler::switchToNextLayout() {
    m_currentLayout = (Layout)(((u8)m_currentLayout + 1) % LAYOUT_COUNT);
}

void LayoutHandler::switchToPrevLayout() {
    m_currentLayout = (Layout)(((u8)m_currentLayout + LAYOUT_COUNT - 1) % LAYOUT_COUNT);
}

ILayout& LayoutHandler::getLayout() {
    return *m_layout[(u8)m_currentLayout];
}

} // namespace ui