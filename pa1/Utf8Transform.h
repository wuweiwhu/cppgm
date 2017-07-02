#pragma once

#include <vector>

namespace cppgm
{

struct Utf8TransformResult
{
public:
    Utf8TransformResult(bool success, int codePoint);

    bool Success;
    int CodePoint;
};

class Utf8Transform
{
public:
    Utf8Transform();
    Utf8TransformResult Process(char utf8CodeUnit);

private:
    unsigned int _codeUnitCount;
    std::vector<char> _codeUnits;
};

}