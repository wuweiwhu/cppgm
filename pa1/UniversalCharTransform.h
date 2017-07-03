#pragma once

#include <vector>

#include "TransformResult.h"

namespace cppgm
{

class UniversalCharTransform
{
public:
    UniversalCharTransform();
    TransformResult Process(int codePoint);

private:
    enum TransformState {InitState, SlashState, ShortHexSeqState, LongHexSeqState};
    TransformState _state;
    std::vector<int> _codePoints;
};

}