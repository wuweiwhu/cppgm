#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "Utf8.h"

namespace cppgm
{

namespace
{

struct OctetCountData
{
public:
    unsigned char FirstOctet;
    int Count;
};

struct EncodeUtf32Data
{
public:
    std::vector<unsigned char> Source;
    int Dest;
};

struct DecodeUtf32Data
{
public:
    int Source;
    std::vector<unsigned char> Dest;
};

}

class Utf8OctetCountTests : public testing::TestWithParam<OctetCountData>
{
};

class Utf8BadOctetCountTests : public testing::TestWithParam<unsigned char>
{
};

class Utf8EncodeUtf32Tests : public testing::TestWithParam<EncodeUtf32Data>
{
};

class Utf8BadEncodeUtf32Tests : public testing::TestWithParam<std::vector<unsigned char>>
{
};

class Utf8DecodeUtf32Tests : public testing::TestWithParam<DecodeUtf32Data>
{
};

TEST_P(Utf8OctetCountTests, OctetCount)
{
    OctetCountData data = GetParam();
    EXPECT_EQ(data.Count, octet_count(data.FirstOctet));
}

TEST_P(Utf8BadOctetCountTests, BadOctetCount)
{
    unsigned char firstOctet = GetParam();
    EXPECT_THROW(octet_count(firstOctet), std::logic_error);
}

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

TEST_P(Utf8DecodeUtf32Tests, DecodeUtf32)
{
    DecodeUtf32Data data = GetParam();
    EXPECT_EQ(data.Dest, decode_utf32(data.Source));
}

TEST(Utf8BadDecodeUtf32Tests, BadDecodeUtf32)
{
    EXPECT_THROW(decode_utf32(0X110000), std::logic_error);
}

INSTANTIATE_TEST_CASE_P(Utf8OctetCount, Utf8OctetCountTests, testing::Values(OctetCountData {0x01, 1},
                                                                             OctetCountData {0x02, 1},
                                                                             OctetCountData {0x7F, 1},
                                                                             OctetCountData {0xC0, 2},
                                                                             OctetCountData {0xC1, 2},
                                                                             OctetCountData {0xDF, 2},
                                                                             OctetCountData {0xE0, 3},
                                                                             OctetCountData {0xE1, 3},
                                                                             OctetCountData {0xEF, 3},
                                                                             OctetCountData {0xF0, 4},
                                                                             OctetCountData {0xF1, 4},
                                                                             OctetCountData {0xF7, 4}));

INSTANTIATE_TEST_CASE_P(Utf8BadOctetCount, Utf8BadOctetCountTests, testing::Values(0x80, 0x81, 0xBF, 0xF8, 0xF9, 0xFF));

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

INSTANTIATE_TEST_CASE_P(Utf8DecodeUtf32, Utf8DecodeUtf32Tests, testing::Values(DecodeUtf32Data {'?', {'?'}},
                                                                               DecodeUtf32Data {'~', {'~'}},
                                                                               DecodeUtf32Data {0x7F, {0x7F}},
                                                                               DecodeUtf32Data {0x80, {0xC2, 0x80}},
                                                                               DecodeUtf32Data {0xA1, {0xC2, 0xA1}},
                                                                               DecodeUtf32Data {0xC0, {0xC3, 0x80}},
                                                                               DecodeUtf32Data {0x1BF, {0xC6, 0xBF}},
                                                                               DecodeUtf32Data {0x3FF, {0xCF, 0xBF}},
                                                                               DecodeUtf32Data {0x7FE, {0xDF, 0xBE}},
                                                                               DecodeUtf32Data {0x7FF, {0xDF, 0xBF}},
                                                                               DecodeUtf32Data {0x800, {0xE0, 0xA0, 0x80}},
                                                                               DecodeUtf32Data {0x801, {0xE0, 0xA0, 0x81}},
                                                                               DecodeUtf32Data {0x8A1, {0xE0, 0xA2, 0xA1}},
                                                                               DecodeUtf32Data {0xEDC, {0xE0, 0xBB, 0x9C}},
                                                                               DecodeUtf32Data {0x1000, {0xE1, 0x80, 0x80}},
                                                                               DecodeUtf32Data {0x10F3, {0xE1, 0x83, 0xB3}},
                                                                               DecodeUtf32Data {0xFFFE, {0xEF, 0xBF, 0xBE}},
                                                                               DecodeUtf32Data {0xFFFF, {0xEF, 0xBF, 0xBF}},
                                                                               DecodeUtf32Data {0x10000, {0xF0, 0x90, 0x80, 0x80}},
                                                                               DecodeUtf32Data {0x10001, {0xF0, 0x90, 0x80, 0x81}},
                                                                               DecodeUtf32Data {0x118F2, {0xF0, 0x91, 0xA3, 0xB2}},
                                                                               DecodeUtf32Data {0xE0023, {0xF3, 0xA0, 0x80, 0xA3}},
                                                                               DecodeUtf32Data {0x100000, {0xF4, 0x80, 0x80, 0x80}},
                                                                               DecodeUtf32Data {0x100364, {0xF4, 0x80, 0x8D, 0xA4}}));
}