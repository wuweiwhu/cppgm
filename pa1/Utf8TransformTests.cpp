#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "Utf8Transform.h"

namespace cppgm
{

namespace
{

struct Utf8TransformData
{
public:
    std::vector<unsigned char> Utf8CodeUnits;
    int ResultCodePoint;
    std::string Name;
};

}

class Utf8TransformTests : public testing::TestWithParam<Utf8TransformData>
{
};

TEST_P(Utf8TransformTests, ProcessUtf8)
{
    Utf8TransformData transformData = GetParam();
    Utf8Transform transform;
    for(unsigned int index = 0; index < transformData.Utf8CodeUnits.size()-1; ++index)
        EXPECT_EQ(Utf8TransformResult(false, 0), transform.Process(transformData.Utf8CodeUnits[index]));
    EXPECT_EQ(Utf8TransformResult(true, transformData.ResultCodePoint), transform.Process(transformData.Utf8CodeUnits[transformData.Utf8CodeUnits.size()-1]));
}

INSTANTIATE_TEST_CASE_P(Utf8, Utf8TransformTests, testing::Values(Utf8TransformData {{'?'}, '?', "Processing_0x3F"},
                                                                  Utf8TransformData {{'~'}, '~', "Processing_0x7E"},
                                                                  Utf8TransformData {{0x7F}, 0x7F, "Processing_0x7F"},
                                                                  Utf8TransformData {{0xC2, 0x80}, 0x80, "Processing_0xC2_0x80"},
                                                                  Utf8TransformData {{0xC3, 0x80}, 0xC0, "Processing_0xC3_0x80"},
                                                                  Utf8TransformData {{0xC5, 0x8B}, 0x14B, "Processing_0xC5_0x8B"},
                                                                  Utf8TransformData {{0xCE, 0xB0}, 0x3B0, "Processing_0xCE_0xB0"},
                                                                  Utf8TransformData {{0xE0, 0xA0, 0x80}, 0x800, "Processing_0xE0_0xA0_0x80"},
                                                                  Utf8TransformData {{0xE0, 0xA0, 0x81}, 0x801, "Processing_0xE0_0xA0_0x81"},
                                                                  Utf8TransformData {{0xE0, 0xA1, 0x9E}, 0x85E, "Processing_0xE0_0xA1_0x9E"},
                                                                  Utf8TransformData {{0xF0, 0x9F, 0x82, 0xA0}, 0x1F0A0, "Processing_0xF0_0x9F_0x82_0xA0"},
                                                                  Utf8TransformData {{0xF3, 0xA0, 0x80, 0x81}, 0xE0001, "Processing_0xF3_0xA0_0x80_0x81"}),
                                                  [](testing::TestParamInfo<Utf8TransformData> const &data){ return data.param.Name; });

}