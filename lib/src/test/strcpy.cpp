/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:52:31 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/12 02:40:36 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <cstring>

struct Parameters
{
	char *const dst;
	char const *const src;
};

typedef char *return_type;

struct Test
{
	Parameters const parameters;
	usize const dst_size;
	usize const src_size;
};

static constexpr Test TESTS[] = {
	{{(char[]){0x00}, (char const[]){0x00}}, 1, 1},
	{{(char[]){0x42, 0x00}, (char const[]){0x00}}, 2, 1},
	{{(char[]){0x2A, 0x00}, (char const[]){0x54, 0x00}}, 2, 2},
	{{(char[]){0x21, 0x01, 0x00, 0x12, 0x4C}, (char const[]){0x71, 0x3D, 0x69, 0x00}}, 5, 4},
	{{(char[]){0x01, 0x02, 0x03, 0x04, 0x05, 0x06}, (char const[]){0x00}}, 6, 1},
	{{(char[]){0x7F, 0xD3, 0xF0, 0xC4, 0x20, 0x99, 0x34, 0x6B, 0x00, 0xA3, 0x37, 0x0A},
	  (char const[]){0xDE, 0xAD, 0xBE, 0xEF, 0x00}},
	 12,
	 5},
	{{(char[]){0x0d, 0x1d, 0xb8, 0xec, 0xa2, 0xa2, 0x0f, 0x3e, 0x28, 0xd1, 0x41, 0xda, 0x69, 0x1a, 0x06, 0xe4, 0x22,
			   0x49, 0x16, 0x54, 0xe2, 0xcc, 0x3e, 0x27, 0xfe, 0x40, 0x63, 0x5b, 0x0b, 0x58, 0xa6, 0x7f, 0x8a, 0x34,
			   0x91, 0xe9, 0xaf, 0x5f, 0x2c, 0xfb, 0x6e, 0x9f},
	  (char const[]){0xc1, 0x43, 0xf9, 0xbe, 0x8d, 0x73, 0x97, 0x04, 0xe4, 0x04, 0xe8, 0xc7, 0x6b, 0xb0, 0xd2, 0xb5,
					 0x33, 0xa6, 0x31, 0x0f, 0x57, 0xbc, 0x83, 0x81, 0x0f, 0xad, 0x78, 0x1d, 0x1e, 0x1d, 0x00}},
	 42,
	 31},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

/**
 * @brief Test the lib::strCpy function.
 *
 * @return true if the test was passed successfully, false otherwise.
 */
bool testStrCpy(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
	{
		Parameters const p = TESTS[i].parameters;
		usize const src_size = TESTS[i].src_size;
		usize const end_size = TESTS[i].dst_size - src_size;
		char const *const end = p.dst + src_size;
		char const *const end_dup = reinterpret_cast<char const *>(memcpy(new char[end_size], end, end_size));
		return_type const ret = lib::strCpy(p.dst, p.src);
		bool const failed = ret != p.dst || memcmp(ret, p.src, src_size) || memcmp(end, end_dup, end_size);

		delete[] end_dup;
		if (failed)
			return false;
	}
	return true;
}
