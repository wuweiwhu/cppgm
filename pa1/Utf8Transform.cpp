#include <vector>

#include "Utf8.h"
#include "Utf8Transform.h"

namespace cppgm
{

TransformResult::TransformResult(bool success, int codePoint) : Success(success), CodePoint(codePoint)
{
}

Utf8Transform::Utf8Transform() : _codeUnitCount(0)
{
}

TransformResult Utf8Transform::Process(char utf8CodeUnit)
{
    if (_codeUnitCount == 0)
        _codeUnitCount = octet_count(utf8CodeUnit);
    _codeUnits.push_back(utf8CodeUnit);
    if (_codeUnits.size() == _codeUnitCount)
    {
        int codePoint = 0; // wtf ??
        _codeUnitCount = 0;
        _codeUnits.clear();
        return TransformResult(true, codePoint);
    }
    else
        return TransformResult(false, 0);
}

}