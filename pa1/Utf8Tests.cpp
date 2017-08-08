#include <gtest/gtest.h>

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

}

class Utf8OctetCountTests : public testing::TestWithParam<OctetCountData>
{
};

class Utf8BadOctetCountTests : public testing::TestWithParam<unsigned char>
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

}