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

}