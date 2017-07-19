#pragma once

#include <vector>

namespace cppgm
{
    int octet_count(unsigned char first);
    int encode_utf32(std::vector<unsigned char> const &codeUnits);
    std::vector<unsigned char> decode_utf32(int ch);
}