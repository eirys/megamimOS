/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:17:25 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 16:36:15 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

template <class Enum>
static inline
constexpr uint32_t enumSize() {
    return static_cast<uint32_t>(Enum::Last) - static_cast<uint32_t>(Enum::First) + 1;
}