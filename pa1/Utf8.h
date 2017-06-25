#pragma once

#include <array>

namespace cppgm
{
    int octet_count(char first);
    int encode_utf32(char ch);
    int encode_utf32(char ch1, char ch2);
    int encode_utf32(char ch1, char ch2, char ch3);
    int encode_utf32(char ch1, char ch2, char ch3, char ch4);
    std::array<char, 4> decode_utf32(int ch);
}