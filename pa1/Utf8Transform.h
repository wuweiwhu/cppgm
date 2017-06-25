#pragma once

#include <vector>

namespace cppgm
{

struct TransformResult
{
public:
    TransformResult(bool success, int codePoint);

    bool Success;
    int CodePoint;
};

class Utf8Transform
{
public:
    Utf8Transform();
    TransformResult Process(char utf8CodeUnit);

private:
    unsigned int _codeUnitCount;
    std::vector<char> _codeUnits;
};

}