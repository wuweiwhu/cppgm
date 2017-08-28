#include <algorithm>
#include <iterator>
#include <vector>

#include "ITransformBehaviour.h"
#include "TransformResult.h"
#include "TotalTransform.h"
#include "Utf8Transform.h"

namespace cppgm
{

void TotalTransform::SetTransformBehaviour(TransformBehaviourData const &data)
{
    _transformBehaviourData = data;
}

TransformResult TotalTransform::Process(unsigned char utf8CodeUnit)
{
    // process Utf8
    Utf8TransformResult utf8TransformResult = _utf8Transform.Process(utf8CodeUnit);
    if (!utf8TransformResult.Processed)
        return TransformResult(false, {});
    if (_transformBehaviourData.SkipAdditionalTransforms)
        return TransformResult(true, {utf8TransformResult.CodePoint});
    // process trigraph
    TransformResult trigraphTransformResult = _trigraphTransform.Process(utf8TransformResult.CodePoint);
    if (!trigraphTransformResult.Processed)
        return TransformResult(false, {});
    // process universal char
    std::vector<int> resultCodePoints;
    for (int codePoint : trigraphTransformResult.CodePoints)
    {
        TransformResult universalCharTransformResult = _universalCharTransform.Process(codePoint);
        if (universalCharTransformResult.Processed)
            std::copy(universalCharTransformResult.CodePoints.cbegin(), universalCharTransformResult.CodePoints.cend(), std::back_inserter(resultCodePoints));
    }
    return resultCodePoints.empty() ? TransformResult(false, {}) : TransformResult(true, resultCodePoints);
}

}