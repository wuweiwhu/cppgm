#pragma once

/*#include <array>*/
#include <vector>

namespace cppgm
{
    int octet_count(char first);
    int encode_utf32(std::vector<char> const &codeUnits);
    std::vector<char> decode_utf32(int ch);
}