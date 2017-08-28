#pragma once

namespace cppgm
{

struct TransformBehaviourData
{
public:
    TransformBehaviourData();

    bool SkipAdditionalTransforms;
};

class ITransformBehaviour
{
public:
    virtual void SetTransformBehaviour(TransformBehaviourData const &data) = 0;
};

}