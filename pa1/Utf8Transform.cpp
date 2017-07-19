#include <vector>

#include "Utf8.h"
#include "Utf8Transform.h"

namespace cppgm
{

Utf8TransformResult::Utf8TransformResult(bool processed, int codePoint) : Processed(processed), CodePoint(codePoint)
{
}

bool operator==(Utf8TransformResult const &left, Utf8TransformResult const &right)
{
    return (left.Processed == right.Processed) && (left.CodePoint == right.CodePoint);
}

bool operator!=(Utf8TransformResult const &left, Utf8TransformResult const &right)
{
    return !(left == right);
}

Utf8Transform::Utf8Transform() : _codeUnitCount(0)
{
}

Utf8TransformResult Utf8Transform::Process(unsigned char utf8CodeUnit)
{
    if (_codeUnitCount == 0)
        _codeUnitCount = octet_count(utf8CodeUnit);
    _codeUnits.push_back(utf8CodeUnit);
    if (_codeUnits.size() == _codeUnitCount)
    {
        int codePoint = encode_utf32(_codeUnits);
        _codeUnitCount = 0;
        _codeUnits.clear();
        return Utf8TransformResult(true, codePoint);
    }
    else
        return Utf8TransformResult(false, 0);
}

}