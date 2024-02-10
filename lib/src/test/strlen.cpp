/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:20:26 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/11 00:46:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <utility>

static constexpr std::pair<char const *, usize> const TESTS[] = {
	{"", 0},
	{"etran & jodufour", 16},
	{"A", 1},
	{"42", 2},
	{"foo \x7F bar \x80 \xFF", 13},
	{"We are all being used\n"
	 "Our lives have been abused\n"
	 "Still no one resists\n"
	 "I guess there 's nothing to lose\n"
	 "I am no longer confused\n"
	 "You' re killing my dreams\n",
	 153},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

/**
 * @brief Test the lib::strlen function.
 *
 * @return true if the test was passed successfully, false otherwise.
 */
bool testStrLen(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
	{
		usize const len = lib::strLen(TESTS[i].first);

		if (len != TESTS[i].second)
			return false;
	}
	return true;
}
