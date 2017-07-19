#pragma once

#include <vector>

namespace cppgm
{

struct Utf8TransformResult
{
public:
    Utf8TransformResult(bool processed, int codePoint);

    bool Processed;
    int CodePoint;
};

// TODO (std_string) : think about location
bool operator==(Utf8TransformResult const &left, Utf8TransformResult const &right);
bool operator!=(Utf8TransformResult const &left, Utf8TransformResult const &right);

class Utf8Transform
{
public:
    Utf8Transform();
    Utf8TransformResult Process(unsigned char utf8CodeUnit);

private:
    unsigned int _codeUnitCount;
    std::vector<unsigned char> _codeUnits;
};

}