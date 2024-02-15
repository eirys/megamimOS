/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:52:31 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/14 09:29:43 by jodufour         ###   ########.fr       */
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
	usize const dst_len;
	usize const src_len;
};

static constexpr Test TESTS[] = {
	{{(char[]){
		  '\x00'},
	  (char const[]){
		  '\x00'}},
	 1,
	 1},
	{{(char[]){
		  '\x42', '\x00'},
	  (char const[]){
		  '\x00'}},
	 2,
	 1},
	{{(char[]){
		  '\x2A', '\x00'},
	  (char const[]){
		  '\x54', '\x00'}},
	 2,
	 2},
	{{(char[]){
		  '\x21', '\x01', '\x00', '\x0C', '\x4C'},
	  (char const[]){
		  '\x71', '\x3D', '\x69', '\x00'}},
	 5,
	 4},
	{{(char[]){
		  '\xFD', '\x4E', '\xD4', '\x24', '\x0C', '\x6C'},
	  (char const[]){
		  '\x00'}},
	 6,
	 1},
	{{(char[]){
		  '\x7F', '\xD3', '\xF0', '\xC4', '\x20', '\x99', '\x34', '\x6B', '\x00', '\xA3', '\x37', '\x0A'},
	  (char const[]){
		  '\xDE', '\xAD', '\xBE', '\xEF', '\x00'}},
	 12,
	 5},
	{{(char[]){
		  '\x0D', '\x1D', '\xB8', '\xEC', '\xA2', '\xA2', '\x0F', '\x3C', '\x28', '\xD1', '\x41', '\xDA', '\x69',
		  '\x1A', '\x06', '\xE4', '\x22', '\x49', '\x16', '\x54', '\xE2', '\xCC', '\x3E', '\x27', '\xFE', '\x40',
		  '\x63', '\x5B', '\x0B', '\x58', '\xA6', '\x7F', '\x8A', '\x34', '\x91', '\xE9', '\xAf', '\x5F', '\x2C',
		  '\xFB', '\x6E', '\x9F'},
	  (char const[]){
		  '\xC1', '\x43', '\xF9', '\xBE', '\x8D', '\x73', '\x97', '\x04', '\xE4', '\x04', '\xE8', '\xC7', '\x6B',
		  '\xB0', '\xD2', '\xB5', '\x33', '\xA6', '\x31', '\x0F', '\x57', '\xBC', '\x83', '\x81', '\x0F', '\xAD',
		  '\x78', '\x1D', '\x1E', '\x1D', '\x00'}},
	 42,
	 31},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

/**
 * @brief Test the lib::strCpy function.
 *
 * @return `true` if the test was passed successfully, `false` otherwise.
 */
bool testStrCpy(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
	{
		Parameters const p = TESTS[i].parameters;
		usize const src_len = TESTS[i].src_len;
		usize const end_len = TESTS[i].dst_len - src_len;
		char const *const end = p.dst + src_len;
		char const *const end_dup = reinterpret_cast<char const *>(memcpy(new char[end_len], end, end_len));
		return_type const ret = lib::strCpy(p.dst, p.src);
		bool const failed = ret != p.dst || memcmp(ret, p.src, src_len) || memcmp(end, end_dup, end_len);

		delete[] end_dup;
		if (failed)
			return false;
	}
	return true;
}
