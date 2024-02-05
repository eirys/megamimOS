/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:06:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 21:12:08 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C"
void __cxa_pure_virtual() {
    asm volatile("hlt");
}

void operator delete(void *) {}