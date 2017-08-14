#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "Utf8Transform.h"

namespace cppgm
{

namespace
{

struct BadUtf8TransformData
{
public:
    std::vector<unsigned char> CodePoints;
    std::string Name;
};

}

class Utf8TransformBadOctetTests : public testing::TestWithParam<BadUtf8TransformData>
{
};


TEST_P(Utf8TransformBadOctetTests, ProcessUtf8)
{
    BadUtf8TransformData transformData = GetParam();
    Utf8Transform transform;
    for (unsigned int index = 0; index < transformData.CodePoints.size() - 1; ++index)
        EXPECT_EQ(Utf8TransformResult(false, 0), transform.Process(transformData.CodePoints[index]));
    EXPECT_THROW(transform.Process(transformData.CodePoints[transformData.CodePoints.size() - 1]), std::logic_error);
}

INSTANTIATE_TEST_CASE_P(BadFirstOctet, Utf8TransformBadOctetTests, testing::Values(BadUtf8TransformData {{0x80}, "Processing_0x80"},
                                                                                   BadUtf8TransformData {{0x81}, "Processing_0x81"},
                                                                                   BadUtf8TransformData {{0xBF}, "Processing_0xBF"},
                                                                                   BadUtf8TransformData {{0xF8}, "Processing_0xF8"},
                                                                                   BadUtf8TransformData {{0xF9}, "Processing_0xF9"},
                                                                                   BadUtf8TransformData {{0xFF}, "Processing_0xFF"}),
                                                                   [](testing::TestParamInfo<BadUtf8TransformData> const &data){ return data.param.Name; });

INSTANTIATE_TEST_CASE_P(BadSecondOctet, Utf8TransformBadOctetTests, testing::Values(BadUtf8TransformData {{0xC0, 0x7F}, "Processing_0xC0_0x7F"},
                                                                                    BadUtf8TransformData {{0xC0, 0xC0}, "Processing_0xC0_0xC0"},
                                                                                    BadUtf8TransformData {{0xC0, 0xC1}, "Processing_0xC0_0xC1"},
                                                                                    BadUtf8TransformData {{0xC0, 0xFF}, "Processing_0xC0_0xFF"},
                                                                                    BadUtf8TransformData {{0xC1, 0x7F}, "Processing_0xC1_0x7F"},
                                                                                    BadUtf8TransformData {{0xC1, 0xC0}, "Processing_0xC1_0xC0"},
                                                                                    BadUtf8TransformData {{0xC1, 0xC1}, "Processing_0xC1_0xC1"},
                                                                                    BadUtf8TransformData {{0xC1, 0xFF}, "Processing_0xC1_0xFF"},
                                                                                    BadUtf8TransformData {{0xDF, 0x7F}, "Processing_0xDF_0x7F"},
                                                                                    BadUtf8TransformData {{0xDF, 0xC0}, "Processing_0xDF_0xC0"},
                                                                                    BadUtf8TransformData {{0xDF, 0xC1}, "Processing_0xDF_0xC1"},
                                                                                    BadUtf8TransformData {{0xDF, 0xFF}, "Processing_0xDF_0xFF"},
                                                                                    BadUtf8TransformData {{0xE0, 0x7F, 0x80}, "Processing_0xE0_0x7F_0x80"},
                                                                                    BadUtf8TransformData {{0xE0, 0xC0, 0x80}, "Processing_0xE0_0xC0_0x80"},
                                                                                    BadUtf8TransformData {{0xE0, 0xC1, 0x80}, "Processing_0xE0_0xC1_0x80"},
                                                                                    BadUtf8TransformData {{0xE0, 0xFF, 0x80}, "Processing_0xE0_0xFF_0x80"},
                                                                                    BadUtf8TransformData {{0xE1, 0x7F, 0x80}, "Processing_0xE1_0x7F_0x80"},
                                                                                    BadUtf8TransformData {{0xE1, 0xC0, 0x80}, "Processing_0xE1_0xC0_0x80"},
                                                                                    BadUtf8TransformData {{0xE1, 0xC1, 0x80}, "Processing_0xE1_0xC1_0x80"},
                                                                                    BadUtf8TransformData {{0xE1, 0xFF, 0x80}, "Processing_0xE1_0xFF_0x80"},
                                                                                    BadUtf8TransformData {{0xEF, 0x7F, 0x80}, "Processing_0xEF_0x7F_0x80"},
                                                                                    BadUtf8TransformData {{0xEF, 0xC0, 0x80}, "Processing_0xEF_0xC0_0x80"},
                                                                                    BadUtf8TransformData {{0xEF, 0xC1, 0x80}, "Processing_0xEF_0xC1_0x80"},
                                                                                    BadUtf8TransformData {{0xEF, 0xFF, 0x80}, "Processing_0xEF_0xFF_0x80"},
                                                                                    BadUtf8TransformData {{0xF0, 0x7F, 0x80, 0x80}, "Processing_0xF0_0x7F_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF0, 0xC0, 0x80, 0x80}, "Processing_0xF0_0xC0_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF0, 0xC1, 0x80, 0x80}, "Processing_0xF0_0xC1_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF0, 0xFF, 0x80, 0x80}, "Processing_0xF0_0xFF_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF1, 0x7F, 0x80, 0x80}, "Processing_0xF1_0x7F_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF1, 0xC0, 0x80, 0x80}, "Processing_0xF1_0xC0_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF1, 0xC1, 0x80, 0x80}, "Processing_0xF1_0xC1_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF1, 0xFF, 0x80, 0x80}, "Processing_0xF1_0xFF_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF7, 0x7F, 0x80, 0x80}, "Processing_0xF7_0x7F_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF7, 0xC0, 0x80, 0x80}, "Processing_0xF7_0xC0_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF7, 0xC1, 0x80, 0x80}, "Processing_0xF7_0xC1_0x80_0x80"},
                                                                                    BadUtf8TransformData {{0xF7, 0xFF, 0x80, 0x80}, "Processing_0xF7_0xFF_0x80_0x80"}),
                                                                    [](testing::TestParamInfo<BadUtf8TransformData> const &data){ return data.param.Name; });

INSTANTIATE_TEST_CASE_P(BadThirdOctet, Utf8TransformBadOctetTests, testing::Values(BadUtf8TransformData {{0xE0, 0x80, 0x7F}, "Processing_0xE0_0x80_0x7F"},
                                                                                   BadUtf8TransformData {{0xE0, 0x80, 0xC0}, "Processing_0xE0_0x80_0xC0"},
                                                                                   BadUtf8TransformData {{0xE0, 0x80, 0xC1}, "Processing_0xE0_0x80_0xC1"},
                                                                                   BadUtf8TransformData {{0xE0, 0x80, 0xFF}, "Processing_0xE0_0x80_0xFF"},
                                                                                   BadUtf8TransformData {{0xE1, 0x80, 0x7F}, "Processing_0xE1_0x80_0x7F"},
                                                                                   BadUtf8TransformData {{0xE1, 0x80, 0xC0}, "Processing_0xE1_0x80_0xC0"},
                                                                                   BadUtf8TransformData {{0xE1, 0x80, 0xC1}, "Processing_0xE1_0x80_0xC1"},
                                                                                   BadUtf8TransformData {{0xE1, 0x80, 0xFF}, "Processing_0xE1_0x80_0xFF"},
                                                                                   BadUtf8TransformData {{0xEF, 0x80, 0x7F}, "Processing_0xEF_0x80_0x7F"},
                                                                                   BadUtf8TransformData {{0xEF, 0x80, 0xC0}, "Processing_0xEF_0x80_0xC0"},
                                                                                   BadUtf8TransformData {{0xEF, 0x80, 0xC1}, "Processing_0xEF_0x80_0xC1"},
                                                                                   BadUtf8TransformData {{0xEF, 0x80, 0xFF}, "Processing_0xEF_0x80_0xFF"},
                                                                                   BadUtf8TransformData {{0xF0, 0x80, 0x7F, 0x80}, "Processing_0xF0_0x80_0x7F_0x80"},
                                                                                   BadUtf8TransformData {{0xF0, 0x80, 0xC0, 0x80}, "Processing_0xF0_0x80_0xC0_0x80"},
                                                                                   BadUtf8TransformData {{0xF0, 0x80, 0xC1, 0x80}, "Processing_0xF0_0x80_0xC1_0x80"},
                                                                                   BadUtf8TransformData {{0xF0, 0x80, 0xFF, 0x80}, "Processing_0xF0_0x80_0xFF_0x80"},
                                                                                   BadUtf8TransformData {{0xF1, 0x80, 0x7F, 0x80}, "Processing_0xF1_0x80_0x7F_0x80"},
                                                                                   BadUtf8TransformData {{0xF1, 0x80, 0xC0, 0x80}, "Processing_0xF1_0x80_0xC0_0x80"},
                                                                                   BadUtf8TransformData {{0xF1, 0x80, 0xC1, 0x80}, "Processing_0xF1_0x80_0xC1_0x80"},
                                                                                   BadUtf8TransformData {{0xF1, 0x80, 0xFF, 0x80}, "Processing_0xF1_0x80_0xFF_0x80"},
                                                                                   BadUtf8TransformData {{0xF7, 0x80, 0x7F, 0x80}, "Processing_0xF7_0x80_0x7F_0x80"},
                                                                                   BadUtf8TransformData {{0xF7, 0x80, 0xC0, 0x80}, "Processing_0xF7_0x80_0xC0_0x80"},
                                                                                   BadUtf8TransformData {{0xF7, 0x80, 0xC1, 0x80}, "Processing_0xF7_0x80_0xC1_0x80"},
                                                                                   BadUtf8TransformData {{0xF7, 0x80, 0xFF, 0x80}, "Processing_0xF7_0x80_0xFF_0x80"}),
                                                                   [](testing::TestParamInfo<BadUtf8TransformData> const &data){ return data.param.Name; });

INSTANTIATE_TEST_CASE_P(BadFourthOctet, Utf8TransformBadOctetTests, testing::Values(BadUtf8TransformData {{0xF0, 0x80, 0x80, 0x7F}, "Processing_0xF0_0x80_0x80_0x7F"},
                                                                                    BadUtf8TransformData {{0xF0, 0x80, 0x80, 0xC0}, "Processing_0xF0_0x80_0x80_0xC0"},
                                                                                    BadUtf8TransformData {{0xF0, 0x80, 0x80, 0xC1}, "Processing_0xF0_0x80_0x80_0xC1"},
                                                                                    BadUtf8TransformData {{0xF0, 0x80, 0x80, 0xFF}, "Processing_0xF0_0x80_0x80_0xFF"},
                                                                                    BadUtf8TransformData {{0xF1, 0x80, 0x80, 0x7F}, "Processing_0xF1_0x80_0x80_0x7F"},
                                                                                    BadUtf8TransformData {{0xF1, 0x80, 0x80, 0xC0}, "Processing_0xF1_0x80_0x80_0xC0"},
                                                                                    BadUtf8TransformData {{0xF1, 0x80, 0x80, 0xC1}, "Processing_0xF1_0x80_0x80_0xC1"},
                                                                                    BadUtf8TransformData {{0xF1, 0x80, 0x80, 0xFF}, "Processing_0xF1_0x80_0x80_0xFF"},
                                                                                    BadUtf8TransformData {{0xF7, 0x80, 0x80, 0x7F}, "Processing_0xF7_0x80_0x80_0x7F"},
                                                                                    BadUtf8TransformData {{0xF7, 0x80, 0x80, 0xC0}, "Processing_0xF7_0x80_0x80_0xC0"},
                                                                                    BadUtf8TransformData {{0xF7, 0x80, 0x80, 0xC1}, "Processing_0xF7_0x80_0x80_0xC1"},
                                                                                    BadUtf8TransformData {{0xF7, 0x80, 0x80, 0xFF}, "Processing_0xF7_0x80_0x80_0xFF"}),
                                                                    [](testing::TestParamInfo<BadUtf8TransformData> const &data){ return data.param.Name; });

}