/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:06:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 15:56:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is necessary for inheritance, for some reason...
*/
#include "lib.h"
extern "C"
void __cxa_pure_virtual() {
    asm volatile("hlt");
}

extern "C"
void* memset(void *dst, i32 value, u32 n)  {
    return lib::memset(dst, value, n);
}

void operator delete(void *) {}
void operator delete(void *, unsigned int) {}