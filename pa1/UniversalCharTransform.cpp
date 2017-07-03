#include <cctype>
#include <unordered_map>
#include <vector>

#include "TransformResult.h"
#include "UniversalCharTransform.h"

namespace cppgm
{

namespace
{

constexpr int SlashChar = '\\';
constexpr int ShortHexSeqChar = 'u';
constexpr int LongHexSeqChar = 'U';

constexpr int ShortHexSeqLength = 2 + 4;
constexpr int LongHexSeqLength = 2 + 8;

const std::unordered_map<int, int> HexDigitMap =
{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'a', 10},
    {'B', 11},
    {'b', 11},
    {'C', 12},
    {'c', 12},
    {'D', 13},
    {'d', 13},
    {'E', 14},
    {'e', 14},
    {'F', 15},
    {'f', 15}
};

int HexToInt(int hexChar)
{
    return HexDigitMap.find(hexChar)->second;
}

}

UniversalCharTransform::UniversalCharTransform() : _state(TransformState::InitState)
{
}

TransformResult UniversalCharTransform::Process(int codePoint)
{
    // TODO (std_string) : think about using more functional style
    if ((SlashChar == codePoint) && _codePoints.empty())
    {
        _codePoints.push_back(codePoint);
        _state = TransformState::SlashState;
        return TransformResult(false, {});
    }
    if ((SlashChar == codePoint) && !_codePoints.empty())
    {
        TransformResult result(true, _codePoints);
        _codePoints.clear();
        _codePoints.push_back(codePoint);
        _state = TransformState::SlashState;
        return result;
    }
    if ((TransformState::SlashState == _state) && (ShortHexSeqChar == codePoint))
    {
        _codePoints.push_back(codePoint);
        _state = TransformState::ShortHexSeqState;
        return TransformResult(false, {});
    }
    if ((TransformState::SlashState == _state) && (LongHexSeqChar == codePoint))
    {
        _codePoints.push_back(codePoint);
        _state = TransformState::LongHexSeqState;
        return TransformResult(false, {});
    }
    if ((TransformState::ShortHexSeqState == _state) && isxdigit(codePoint))
    {
        _codePoints.push_back(codePoint);
        if (_codePoints.size() == ShortHexSeqLength)
        {
            int resultCodePoint = (HexToInt(_codePoints[2]) << 12) +
                                  (HexToInt(_codePoints[3]) << 8) +
                                  (HexToInt(_codePoints[4]) << 4) +
                                  HexToInt(_codePoints[5]);
            return TransformResult(true, {resultCodePoint});
        }
        else
        {
            return TransformResult(false, {});
        }
    }
    if ((TransformState::LongHexSeqState == _state) && isxdigit(codePoint))
    {
        _codePoints.push_back(codePoint);
        if (_codePoints.size() == LongHexSeqLength)
        {
            int resultCodePoint = (HexToInt(_codePoints[2]) << 28) +
                                  (HexToInt(_codePoints[3]) << 24) +
                                  (HexToInt(_codePoints[4]) << 20) +
                                  (HexToInt(_codePoints[5]) << 16) +
                                  (HexToInt(_codePoints[6]) << 12) +
                                  (HexToInt(_codePoints[7]) << 8) +
                                  (HexToInt(_codePoints[8]) << 4) +
                                  HexToInt(_codePoints[9]);
            return TransformResult(true, {resultCodePoint});
        }
        else
        {
            return TransformResult(false, {});
        }
    }
    _codePoints.push_back(codePoint);
    TransformResult result(true, _codePoints);
    _state = TransformState::InitState;
    _codePoints.clear();
    return result;
}

}