#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "TransformResult.h"
#include "UniversalCharTransform.h"

namespace cppgm
{

namespace
{

struct UniversalCharTransformData
{
public:
    std::vector<int> CodePoints;
    int ResultCodePoint;
    std::string Name;
};

}

class UniversalCharTransformTests : public testing::TestWithParam<UniversalCharTransformData>
{
};

TEST_P(UniversalCharTransformTests, ProcessUniversalChars)
{
    UniversalCharTransformData transformData = GetParam();
    UniversalCharTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    for(unsigned int index = 0; index < transformData.CodePoints.size() - 1; ++index)
        EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.CodePoints[index]));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.CodePoints[transformData.CodePoints.size() - 1]));
}

TEST_P(UniversalCharTransformTests, ProcessSlashAndUniversalChars)
{
    UniversalCharTransformData transformData = GetParam();
    UniversalCharTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('\\'));
    EXPECT_EQ(TransformResult(true, {'\\'}), transform.Process('\\'));
    for(unsigned int index = 0; index < transformData.CodePoints.size() - 1; ++index)
        EXPECT_EQ(TransformResult(false, {}), transform.Process(transformData.CodePoints[index]));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.CodePoints[transformData.CodePoints.size() - 1]));
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

INSTANTIATE_TEST_CASE_P(UniversalChars,
                        UniversalCharTransformTests,
                        testing::Values(UniversalCharTransformData {{'u', '0', '0', '3', 'F'}, '?', "Processing_u003F"},
                                        UniversalCharTransformData {{'u', '0', '0', '3', 'f'}, '?', "Processing_u003f"},
                                        UniversalCharTransformData {{'u', '0', '3', '0', '4'}, 0x304, "Processing_u0304"},
                                        UniversalCharTransformData {{'u', '1', '2', '3', 'd'}, 0x123D, "Processing_u123d"},
                                        UniversalCharTransformData {{'u', '1', '2', '3', 'D'}, 0x123D, "Processing_u123D"},
                                        UniversalCharTransformData {{'U', '0', '0', '0', '0', '0', '0', '3', 'F'}, '?', "Processing_U0000003F"},
                                        UniversalCharTransformData {{'U', '0', '0', '0', '0', '0', '0', '3', 'f'}, '?', "Processing_U0000003f"},
                                        UniversalCharTransformData {{'U', '0', '0', '0', '0', '0', '3', '0', '4'}, 0x304, "Processing_U00000304"},
                                        UniversalCharTransformData {{'U', '0', '0', '0', '0', '1', '2', '3', 'd'}, 0x123D, "Processing_U0000123d"},
                                        UniversalCharTransformData {{'U', '0', '0', '0', '0', '1', '2', '3', 'D'}, 0x123D, "Processing_U0000123D"}),
                        [](testing::TestParamInfo<UniversalCharTransformData> const &data){ return data.param.Name; });

}