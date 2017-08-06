#include <gtest/gtest.h>
#include <vector>

#include "TransformResult.h"
#include "TrigraphTransform.h"

namespace cppgm
{

namespace
{

struct TrigraphTransformData
{
public:
    int ThirdSourceCodePoint;
    int ResultCodePoint;
};

}

class TrigraphTransformTests : public testing::TestWithParam<TrigraphTransformData>
{
};

TEST_P(TrigraphTransformTests, ProcessTrigraphs)
{
    TrigraphTransformData transformData = GetParam();
    TrigraphTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.ThirdSourceCodePoint));
}

TEST_P(TrigraphTransformTests, ProcessQuestionsAndTrigraphs)
{
    TrigraphTransformData transformData = GetParam();
    TrigraphTransform transform;
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {'?'}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {'?'}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {transformData.ResultCodePoint}), transform.Process(transformData.ThirdSourceCodePoint));
}

TEST(TrigraphTransformTests, ProcessOtherCases)
{
    TrigraphTransform transform;
    EXPECT_EQ(TransformResult(true, {'A'}), transform.Process('A'));
    EXPECT_EQ(TransformResult(true, {'#'}), transform.Process('#'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {'?', '#'}), transform.Process('#'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(false, {}), transform.Process('?'));
    EXPECT_EQ(TransformResult(true, {'?', '?', '#'}), transform.Process('#'));
}

INSTANTIATE_TEST_CASE_P(Trigraphs, TrigraphTransformTests, testing::Values(TrigraphTransformData {'=', '#'},
                                                                           TrigraphTransformData {'/', '\\'},
                                                                           TrigraphTransformData {'\'', '^'},
                                                                           TrigraphTransformData {'(', '['},
                                                                           TrigraphTransformData {')', ']'},
                                                                           TrigraphTransformData {'!', '|'},
                                                                           TrigraphTransformData {'<', '{'},
                                                                           TrigraphTransformData {'>', '}'},
                                                                           TrigraphTransformData {'-', '~'}));

}