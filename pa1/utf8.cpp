#include <array>
#include <stdexcept>

#include "utf8.h"

namespace cppgm
{
    namespace
    {
        //const char singleOctetMask = 0x80;
        //const char singleOctetValue = 0;
        //const char otherOctetMask = 0xC0;
        //const char otherOctetValue = 0x80;

        bool check_octet(char octet, char mask, char expectedValue)
        {
            return (octet & mask) == expectedValue;
        }

        bool check_utf32(int utf32, int leftBorder, int rightBorder)
        {
            return (leftBorder <= utf32) && (utf32 <= rightBorder);
        }
    }

    int octet_count(char first)
    {
        // Char number range: 0000 0000-0000 007F - UTF-8 octet sequence: 0xxxxxxx
        if (check_octet(first, 0x80, 0))
            return 1;
        // Char number range: 0000 0080-0000 07FF - UTF-8 octet sequence: 110xxxxx 10xxxxxx
        if (check_octet(first, 0xE0, 0xC0))
            return 2;
        // Char number range: 0000 0800-0000 FFFF - UTF-8 octet sequence: 1110xxxx 10xxxxxx 10xxxxxx
        if (check_octet(first, 0xF0, 0xE0))
            return 3;
        // Char number range: 0001 0000-0010 FFFF - UTF-8 octet sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        if (check_octet(first, 0xF8, 0xF0))
            return 4;
        throw std::logic_error("Bad first character");
    }

    int encode_utf32(char ch)
    {
        if (!check_octet(ch, 0x80, 0))
            throw std::logic_error("Bad first character");
        return ch;
    }

    int encode_utf32(char ch1, char ch2)
    {
        if (!check_octet(ch1, 0xE0, 0xC0))
            throw std::logic_error("Bad first character");
        if (!check_octet(ch2, 0xC0, 0x80))
            throw std::logic_error("Bad second character");
        return ((ch1 & 0x1F) << 6) + (ch2 & 0x3F);
    }

    int encode_utf32(char ch1, char ch2, char ch3)
    {
        if (!check_octet(ch1, 0xF0, 0xE0))
            throw std::logic_error("Bad first character");
        if (!check_octet(ch2, 0xC0, 0x80))
            throw std::logic_error("Bad second character");
        if (!check_octet(ch3, 0xC0, 0x80))
            throw std::logic_error("Bad third character");
        return ((ch1 & 0x0F) << 12) + ((ch2 & 0x3F) << 6) + (ch3 & 0x3F);
    }

    int encode_utf32(char ch1, char ch2, char ch3, char ch4)
    {
        if (!check_octet(ch1, 0xF8, 0xF0))
            throw std::logic_error("Bad first character");
        if (!check_octet(ch2, 0xC0, 0x80))
            throw std::logic_error("Bad second character");
        if (!check_octet(ch3, 0xC0, 0x80))
            throw std::logic_error("Bad third character");
        if (!check_octet(ch3, 0xC0, 0x80))
            throw std::logic_error("Bad fourth character");
        return ((ch1 & 0x07) << 18) + ((ch2 & 0x3F) << 12) + ((ch3 & 0x3F) << 6) + (ch4 & 0x3F);
    }

    std::array<char, 4> decode_utf32(int ch)
    {
        char ch1 = 0;
        char ch2 = 0;
        char ch3 = 0;
        char ch4 = 0;
        // Char number range: 0000 0000-0000 007F - UTF-8 octet sequence: 0xxxxxxx
        if (check_utf32(ch, 0x00000000, 0x0000007F))
        {
            ch1 = ch & 0x7F;
        }
        // Char number range: 0000 0080-0000 07FF - UTF-8 octet sequence: 110xxxxx 10xxxxxx
        else if (check_utf32(ch, 0x00000080, 0x000007FF))
        {
            ch1 = 0xC0 + ((ch >> 6) & 0x1F);
            ch2 = 0x80 + (ch & 0x3F);
        }
        // Char number range: 0000 0800-0000 FFFF - UTF-8 octet sequence: 1110xxxx 10xxxxxx 10xxxxxx
        else if (check_utf32(ch, 0x00000800, 0x0000FFFF))
        {
            ch1 = 0xE0 + ((ch >> 12) & 0x0F);
            ch2 = 0x80 + ((ch >> 6) & 0x3F);
            ch2 = 0x80 + (ch & 0x3F);
        }
        // Char number range: 0001 0000-0010 FFFF - UTF-8 octet sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if (check_utf32(ch, 0x00010000, 0x0010FFFF))
        {
            ch1 = 0xF0 + ((ch >> 18) & 0x07);
            ch2 = 0x80 + ((ch >> 12) & 0x3F);
            ch3 = 0x80 + ((ch >> 6) & 0x3F);
            ch4 = 0x80 + (ch & 0x3F);
        }
        else
        {
            throw std::logic_error("Bad utf32 character");
        }
        return {ch1, ch2, ch3, ch4};
    }
}