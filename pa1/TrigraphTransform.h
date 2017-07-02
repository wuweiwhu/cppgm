#pragma once

#include <vector>

namespace cppgm
{

struct TransformResult
{
public:
    TransformResult(bool processed, std::vector<int> codePoints);

    bool Processed;
    std::vector<int> CodePoints;
};

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