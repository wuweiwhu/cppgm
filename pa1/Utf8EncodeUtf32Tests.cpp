#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "Utf8.h"

namespace cppgm
{

namespace
{

struct EncodeUtf32Data
{
public:
    std::vector<unsigned char> Source;
    int Dest;
};

}

class Utf8EncodeUtf32Tests : public testing::TestWithParam<EncodeUtf32Data>
{
};

class Utf8BadEncodeUtf32Tests : public testing::TestWithParam<std::vector<unsigned char>>
{
};

TEST_P(Utf8EncodeUtf32Tests, EncodeUtf32)
{
    EncodeUtf32Data data = GetParam();
    EXPECT_EQ(data.Dest, encode_utf32(data.Source));
}

TEST_P(Utf8BadEncodeUtf32Tests, BadEncodeUtf32)
{
    std::vector<unsigned char> data = GetParam();
    EXPECT_THROW(encode_utf32(data), std::logic_error);
}

INSTANTIATE_TEST_CASE_P(Utf8EncodeUtf32, Utf8EncodeUtf32Tests, testing::Values(EncodeUtf32Data {{'?'}, '?'},
                                                                               EncodeUtf32Data {{'~'}, '~'},
                                                                               EncodeUtf32Data {{0x7F}, 0x7F},
                                                                               EncodeUtf32Data {{0xC2, 0x80}, 0x80},
                                                                               EncodeUtf32Data {{0xC2, 0xA1}, 0xA1},
                                                                               EncodeUtf32Data {{0xC3, 0x80}, 0xC0},
                                                                               EncodeUtf32Data {{0xC6, 0xBF}, 0x1BF},
                                                                               EncodeUtf32Data {{0xCF, 0xBF}, 0x3FF},
                                                                               EncodeUtf32Data {{0xDF, 0xBE}, 0x7FE},
                                                                               EncodeUtf32Data {{0xDF, 0xBF}, 0x7FF},
                                                                               EncodeUtf32Data {{0xE0, 0xA0, 0x80}, 0x800},
                                                                               EncodeUtf32Data {{0xE0, 0xA0, 0x81}, 0x801},
                                                                               EncodeUtf32Data {{0xE0, 0xA2, 0xA1}, 0x8A1},
                                                                               EncodeUtf32Data {{0xE0, 0xBB, 0x9C}, 0xEDC},
                                                                               EncodeUtf32Data {{0xE1, 0x80, 0x80}, 0x1000},
                                                                               EncodeUtf32Data {{0xE1, 0x83, 0xB3}, 0x10F3},
                                                                               EncodeUtf32Data {{0xEF, 0xBF, 0xBE}, 0xFFFE},
                                                                               EncodeUtf32Data {{0xEF, 0xBF, 0xBF}, 0xFFFF},
                                                                               EncodeUtf32Data {{0xF0, 0x90, 0x80, 0x80}, 0x10000},
                                                                               EncodeUtf32Data {{0xF0, 0x90, 0x80, 0x81}, 0x10001},
                                                                               EncodeUtf32Data {{0xF0, 0x91, 0xA3, 0xB2}, 0x118F2},
                                                                               EncodeUtf32Data {{0xF3, 0xA0, 0x80, 0xA3}, 0xE0023},
                                                                               EncodeUtf32Data {{0xF4, 0x80, 0x80, 0x80}, 0x100000},
                                                                               EncodeUtf32Data {{0xF4, 0x80, 0x8D, 0xA4}, 0x100364}));

INSTANTIATE_TEST_CASE_P(Utf8BadEncodeUtf32, Utf8BadEncodeUtf32Tests, testing::Values(std::vector<unsigned char> {0x80},
                                                                                     std::vector<unsigned char> {0xBF, 0x80},
                                                                                     std::vector<unsigned char> {0xE0, 0x80},
                                                                                     std::vector<unsigned char> {0xC0, 0x7F},
                                                                                     std::vector<unsigned char> {0xC0, 0xC0},
                                                                                     std::vector<unsigned char> {0xDF, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xE0, 0x7F, 0x80},
                                                                                     std::vector<unsigned char> {0xE0, 0xC0, 0x80},
                                                                                     std::vector<unsigned char> {0xE0, 0x80, 0x7F},
                                                                                     std::vector<unsigned char> {0xE0, 0x80, 0xC0},
                                                                                     std::vector<unsigned char> {0xEF, 0x80, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xF8, 0x80, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0x7F, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0xC0, 0x80, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0x80, 0x7F, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0x80, 0xC0, 0x80},
                                                                                     std::vector<unsigned char> {0xF0, 0x80, 0x80, 0x7F},
                                                                                     std::vector<unsigned char> {0xF0, 0x80, 0x80, 0xC0}));
}