#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "Utf8Transform.h"

namespace cppgm
{

class Utf8TransformBadOctetTests : public testing::TestWithParam<std::vector<unsigned char>>
{
};


TEST_P(Utf8TransformBadOctetTests, ProcessUtf8)
{
    std::vector<unsigned char> transformData = GetParam();
    Utf8Transform transform;
    for (unsigned int index = 0; index < transformData.size() - 1; ++index)
        EXPECT_EQ(Utf8TransformResult(false, 0), transform.Process(transformData[index]));
    EXPECT_THROW(transform.Process(transformData[transformData.size() - 1]), std::logic_error);
}

INSTANTIATE_TEST_CASE_P(BadFirstOctet, Utf8TransformBadOctetTests, testing::Values(std::vector<unsigned char> {0x80},
                                                                                   std::vector<unsigned char> {0x81},
                                                                                   std::vector<unsigned char> {0xBF},
                                                                                   std::vector<unsigned char> {0xF8},
                                                                                   std::vector<unsigned char> {0xF9},
                                                                                   std::vector<unsigned char> {0xFF}));

INSTANTIATE_TEST_CASE_P(BadSecondOctet, Utf8TransformBadOctetTests, testing::Values(std::vector<unsigned char> {0xC0, 0x7F},
                                                                                    std::vector<unsigned char> {0xC0, 0xC0},
                                                                                    std::vector<unsigned char> {0xC0, 0xC1},
                                                                                    std::vector<unsigned char> {0xC0, 0xFF},
                                                                                    std::vector<unsigned char> {0xC1, 0x7F},
                                                                                    std::vector<unsigned char> {0xC1, 0xC0},
                                                                                    std::vector<unsigned char> {0xC1, 0xC1},
                                                                                    std::vector<unsigned char> {0xC1, 0xFF},
                                                                                    std::vector<unsigned char> {0xDF, 0x7F},
                                                                                    std::vector<unsigned char> {0xDF, 0xC0},
                                                                                    std::vector<unsigned char> {0xDF, 0xC1},
                                                                                    std::vector<unsigned char> {0xDF, 0xFF},
                                                                                    std::vector<unsigned char> {0xE0, 0x7F, 0x80},
                                                                                    std::vector<unsigned char> {0xE0, 0xC0, 0x80},
                                                                                    std::vector<unsigned char> {0xE0, 0xC1, 0x80},
                                                                                    std::vector<unsigned char> {0xE0, 0xFF, 0x80},
                                                                                    std::vector<unsigned char> {0xE1, 0x7F, 0x80},
                                                                                    std::vector<unsigned char> {0xE1, 0xC0, 0x80},
                                                                                    std::vector<unsigned char> {0xE1, 0xC1, 0x80},
                                                                                    std::vector<unsigned char> {0xE1, 0xFF, 0x80},
                                                                                    std::vector<unsigned char> {0xEF, 0x7F, 0x80},
                                                                                    std::vector<unsigned char> {0xEF, 0xC0, 0x80},
                                                                                    std::vector<unsigned char> {0xEF, 0xC1, 0x80},
                                                                                    std::vector<unsigned char> {0xEF, 0xFF, 0x80},
                                                                                    std::vector<unsigned char> {0xF0, 0x7F, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF0, 0xC0, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF0, 0xC1, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF0, 0xFF, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF1, 0x7F, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF1, 0xC0, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF1, 0xC1, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF1, 0xFF, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF7, 0x7F, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF7, 0xC0, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF7, 0xC1, 0x80, 0x80},
                                                                                    std::vector<unsigned char> {0xF7, 0xFF, 0x80, 0x80}));

INSTANTIATE_TEST_CASE_P(BadThirdOctet, Utf8TransformBadOctetTests, testing::Values(std::vector<unsigned char> {0xE0, 0x80, 0x7F},
                                                                                   std::vector<unsigned char> {0xE0, 0x80, 0xC0},
                                                                                   std::vector<unsigned char> {0xE0, 0x80, 0xC1},
                                                                                   std::vector<unsigned char> {0xE0, 0x80, 0xFF},
                                                                                   std::vector<unsigned char> {0xE1, 0x80, 0x7F},
                                                                                   std::vector<unsigned char> {0xE1, 0x80, 0xC0},
                                                                                   std::vector<unsigned char> {0xE1, 0x80, 0xC1},
                                                                                   std::vector<unsigned char> {0xE1, 0x80, 0xFF},
                                                                                   std::vector<unsigned char> {0xEF, 0x80, 0x7F},
                                                                                   std::vector<unsigned char> {0xEF, 0x80, 0xC0},
                                                                                   std::vector<unsigned char> {0xEF, 0x80, 0xC1},
                                                                                   std::vector<unsigned char> {0xEF, 0x80, 0xFF},
                                                                                   std::vector<unsigned char> {0xF0, 0x80, 0x7F, 0x80},
                                                                                   std::vector<unsigned char> {0xF0, 0x80, 0xC0, 0x80},
                                                                                   std::vector<unsigned char> {0xF0, 0x80, 0xC1, 0x80},
                                                                                   std::vector<unsigned char> {0xF0, 0x80, 0xFF, 0x80},
                                                                                   std::vector<unsigned char> {0xF1, 0x80, 0x7F, 0x80},
                                                                                   std::vector<unsigned char> {0xF1, 0x80, 0xC0, 0x80},
                                                                                   std::vector<unsigned char> {0xF1, 0x80, 0xC1, 0x80},
                                                                                   std::vector<unsigned char> {0xF1, 0x80, 0xFF, 0x80},
                                                                                   std::vector<unsigned char> {0xF7, 0x80, 0x7F, 0x80},
                                                                                   std::vector<unsigned char> {0xF7, 0x80, 0xC0, 0x80},
                                                                                   std::vector<unsigned char> {0xF7, 0x80, 0xC1, 0x80},
                                                                                   std::vector<unsigned char> {0xF7, 0x80, 0xFF, 0x80}));

INSTANTIATE_TEST_CASE_P(BadFourthOctet, Utf8TransformBadOctetTests, testing::Values(std::vector<unsigned char> {0xF0, 0x80, 0x80, 0x7F},
                                                                                    std::vector<unsigned char> {0xF0, 0x80, 0x80, 0xC0},
                                                                                    std::vector<unsigned char> {0xF0, 0x80, 0x80, 0xC1},
                                                                                    std::vector<unsigned char> {0xF0, 0x80, 0x80, 0xFF},
                                                                                    std::vector<unsigned char> {0xF1, 0x80, 0x80, 0x7F},
                                                                                    std::vector<unsigned char> {0xF1, 0x80, 0x80, 0xC0},
                                                                                    std::vector<unsigned char> {0xF1, 0x80, 0x80, 0xC1},
                                                                                    std::vector<unsigned char> {0xF1, 0x80, 0x80, 0xFF},
                                                                                    std::vector<unsigned char> {0xF7, 0x80, 0x80, 0x7F},
                                                                                    std::vector<unsigned char> {0xF7, 0x80, 0x80, 0xC0},
                                                                                    std::vector<unsigned char> {0xF7, 0x80, 0x80, 0xC1},
                                                                                    std::vector<unsigned char> {0xF7, 0x80, 0x80, 0xFF}));

}