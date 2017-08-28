#pragma once

#include "ITransformBehaviour.h"
#include "TransformResult.h"
#include "TrigraphTransform.h"
#include "Utf8Transform.h"
#include "UniversalCharTransform.h"

namespace cppgm
{

class TotalTransform : public ITransformBehaviour
{
public:
    virtual void SetTransformBehaviour(TransformBehaviourData const &data) override;
    TransformResult Process(unsigned char utf8CodeUnit);

private:
    TransformBehaviourData _transformBehaviourData;
    Utf8Transform _utf8Transform;
    TrigraphTransform _trigraphTransform;
    UniversalCharTransform _universalCharTransform;
};

}