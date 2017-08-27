#pragma once

#include "TransformResult.h"
#include "TrigraphTransform.h"
#include "Utf8Transform.h"
#include "UniversalCharTransform.h"

namespace cppgm
{

class TotalTransform
{
public:
    TransformResult Process(unsigned char utf8CodeUnit);

private:
    Utf8Transform _utf8Transform;
    TrigraphTransform _trigraphTransform;
    UniversalCharTransform _universalCharTransform;
};

}