#include <gtest/gtest.h>
#include <vector>

#include "TransformResult.h"
#include "UniversalCharTransform.h"

namespace cppgm
{

struct UniversalCharTransformData
{
public:
    int DescriptorCodePoint;
    std::vector<int> DigitCodePoints;
    int ResultCodePoint;
};

class UniversalCharTransformTests : public testing::TestWithParam<UniversalCharTransformData>
{
};

TEST_P(UniversalCharTransformTests, ProcessUniversalChars)
{
    UniversalCharTransformData transformData = GetParam();
    UniversalCharTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.DescriptorCodePoint));
    for(unsigned int index = 0; index < transformData.DigitCodePoints.size()-1; ++index)
        EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.DigitCodePoints[index]));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.DigitCodePoints[transformData.DigitCodePoints.size()-1]));
}

TEST_P(UniversalCharTransformTests, ProcessSlashAndUniversalChars)
{
    UniversalCharTransformData transformData = GetParam();
    UniversalCharTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(true, {'\\'}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.DescriptorCodePoint));
    for(unsigned int index = 0; index < transformData.DigitCodePoints.size()-1; ++index)
        EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.DigitCodePoints[index]));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.DigitCodePoints[transformData.DigitCodePoints.size()-1]));
}

TEST(UniversalCharTransformTests, ProcessOtherCases)
{
    UniversalCharTransform transform;
    EXPECT_EQ(TransformResult(true, {'#'}), transform.Process('#'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(true, {'\\', '#'}), transform.Process('#'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('u'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('0'));
    EXPECT_EQ(TransformResult(true, {'\\', 'u', '0', 'x'}), transform.Process('x'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('U'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('0'));
    EXPECT_EQ(TransformResult(true, {'\\', 'U', '0', 'x'}), transform.Process('x'));
}

INSTANTIATE_TEST_CASE_P(UniversalChars, UniversalCharTransformTests, testing::Values(UniversalCharTransformData {'u', {'0', '0', '3', 'F'}, '?'},
                                                                                     UniversalCharTransformData {'u', {'0', '0', '3', 'f'}, '?'},
                                                                                     UniversalCharTransformData {'u', {'0', '3', '0', '4'}, 0x304},
                                                                                     UniversalCharTransformData {'u', {'1', '2', '3', 'd'}, 0x123D},
                                                                                     UniversalCharTransformData {'u', {'1', '2', '3', 'D'}, 0x123D},
                                                                                     UniversalCharTransformData {'U', {'0', '0', '0', '0', '0', '0', '3', 'F'}, '?'},
                                                                                     UniversalCharTransformData {'U', {'0', '0', '0', '0', '0', '0', '3', 'f'}, '?'},
                                                                                     UniversalCharTransformData {'U', {'0', '0', '0', '0', '0', '3', '0', '4'}, 0x304},
                                                                                     UniversalCharTransformData {'U', {'0', '0', '0', '0', '1', '2', '3', 'd'}, 0x123D},
                                                                                     UniversalCharTransformData {'U', {'0', '0', '0', '0', '1', '2', '3', 'D'}, 0x123D}));

}