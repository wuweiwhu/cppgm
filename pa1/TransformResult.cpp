#include <vector>

#include "TransformResult.h"

namespace cppgm
{

TransformResult::TransformResult(bool processed, std::vector<int> codePoints) :
    Processed(processed),
    CodePoints(codePoints)
{
}

}