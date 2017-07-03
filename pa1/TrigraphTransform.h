#pragma once

#include <vector>

#include "TransformResult.h"

namespace cppgm
{

class TrigraphTransform
{
public:
    TrigraphTransform();
    TransformResult Process(int codePoint);

private:
    enum TransformState {InitState, FirstQuestionState, SecondQuestionState};
    TransformState _state;
    std::vector<int> _codePoints;
};

}