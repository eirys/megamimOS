/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:06:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 22:17:56 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is necessary for inheritance, for some reason...
*/

extern "C"
void __cxa_pure_virtual() {
    asm volatile("hlt");
}

// void operator delete(void *) {}

void operator delete(void *, unsigned int) {}