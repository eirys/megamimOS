/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:40 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 16:48:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "utils.h"

namespace ui {

enum class Layout: u8 {
    Azerty = 0,
    Qwerty,

    First   = Azerty,
    Last    = Qwerty
};

class ILayout;

class LayoutHandler final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    LayoutHandler() = default;
    ~LayoutHandler() = default;

    LayoutHandler(LayoutHandler&& other) = delete;
    LayoutHandler(const LayoutHandler& other) = delete;
    LayoutHandler& operator=(LayoutHandler&& other) = delete;
    LayoutHandler& operator=(const LayoutHandler& other) = delete;

    /* ---------------------------------------- */

    static void     init();

    /* ---------------------------------------- */

    static void     switchToNextLayout();
    static void     switchToPrevLayout();

    static ILayout& getLayout();

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u8 LAYOUT_COUNT = enumSize<Layout>();

    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    static ILayout*     m_layout[LAYOUT_COUNT];
    static Layout       m_currentLayout;

}; // class LayoutHandler

} // namespace ui
