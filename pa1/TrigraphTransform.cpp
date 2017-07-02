#include <vector>
#include <unordered_map>

#include "TrigraphTransform.h"

namespace cppgm
{

namespace
{

constexpr int QuestionChar = '?';

const std::unordered_map<int, int> ThirdCodePointMap = {{'=', '#'}, {'/', '\\'}, {'\'', '^'}, {'(', '['}, {')', ']'}, {'!', '|'}, {'<', '{'}, {'>', '}'}, {'-', '~'}};

bool IsKnownThirdCodePoint(int codePoint)
{
    return ThirdCodePointMap.find(codePoint) != ThirdCodePointMap.cend();
}

}

TransformResult::TransformResult(bool processed, std::vector<int> codePoints) :
    Processed(processed),
    CodePoints(codePoints)
{
}

TrigraphTransform::TrigraphTransform() : _state(TransformState::InitState)
{
}

TransformResult TrigraphTransform::Process(int codePoint)
{
    // TODO (std_string) : think about using more functional style
    if ((TransformState::InitState == _state) && (QuestionChar == codePoint))
    {
        _codePoints.push_back(codePoint);
        _state = TransformState::FirstQuestionState;
        return TransformResult(false, {});
    }
    if ((TransformState::FirstQuestionState == _state) && (QuestionChar == codePoint))
    {
        _codePoints.push_back(codePoint);
        _state = TransformState::SecondQuestionState;
        return TransformResult(false, {});
    }
    if ((TransformState::SecondQuestionState == _state) && IsKnownThirdCodePoint(codePoint))
    {
        std::unordered_map<int, int>::const_iterator iterator = ThirdCodePointMap.find(codePoint);
        _state = TransformState::InitState;
        _codePoints.clear();
        return TransformResult(true, {iterator->second});
    }
    if ((TransformState::SecondQuestionState == _state) && (QuestionChar == codePoint))
    {
        return TransformResult(true, {QuestionChar});
    }
    _codePoints.push_back(codePoint);
    TransformResult result(true, _codePoints);
    _state = TransformState::InitState;
    _codePoints.clear();
    return result;
}

}