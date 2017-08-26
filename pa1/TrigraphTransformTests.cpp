#include <gtest/gtest.h>
#include <string>
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
    std::string Name;
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

INSTANTIATE_TEST_CASE_P(Trigraphs, TrigraphTransformTests, testing::Values(TrigraphTransformData {'=', '#', "Processing_number_sign_char"},
                                                                           TrigraphTransformData {'/', '\\', "Processing_backslash_char"},
                                                                           TrigraphTransformData {'\'', '^', "Processing_caret_circumflex_char"},
                                                                           TrigraphTransformData {'(', '[', "Processing_opening_bracket_char"},
                                                                           TrigraphTransformData {')', ']', "Processing_closing_bracket_char"},
                                                                           TrigraphTransformData {'!', '|', "Processing_vertical_bar_char"},
                                                                           TrigraphTransformData {'<', '{', "Processing_opening_brace_char"},
                                                                           TrigraphTransformData {'>', '}', "Processing_closing_brace_char"},
                                                                           TrigraphTransformData {'-', '~', "Processing_tilde_char"}),
                                                           [](testing::TestParamInfo<TrigraphTransformData> const &data){ return data.param.Name; });

}