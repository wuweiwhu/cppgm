#include <vector>

#include "TransformResult.h"

namespace cppgm
{

TransformResult::TransformResult(bool processed, std::vector<int> codePoints) :
    Processed(processed),
    CodePoints(codePoints)
{
}

bool operator==(TransformResult const &left, TransformResult const &right)
{
    return (left.Processed == right.Processed) && (left.CodePoints == right.CodePoints);
}

bool operator!=(TransformResult const &left, TransformResult const &right)
{
    return !(left == right);
}

}