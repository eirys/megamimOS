/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:06:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 00:59:37 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is necessary for inheritance, and other obscure reasons...
*/
#include "lib.h"

// Inheritance
extern "C"
void __cxa_pure_virtual() {
    asm volatile("hlt");
}

// Static initialization
extern "C"
void __cxa_guard_acquire() {}

extern "C"
void __cxa_guard_release() {}


void operator delete(void *) {}
void operator delete(void *, unsigned int) {}
void operator delete(void *, unsigned long int) {}
