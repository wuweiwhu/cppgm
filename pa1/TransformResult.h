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

// TODO (std_string) : think about location
bool operator==(TransformResult const &left, TransformResult const &right);
bool operator!=(TransformResult const &left, TransformResult const &right);

}