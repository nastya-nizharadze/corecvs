/**
 * \file floatFlowBuffer.cpp
 * \brief Add Comment Here
 *
 * \ingroup cppcorefiles
 * \date Jul 20, 2010
 * \author alexander
 */
#include "core/utils/global.h"

#include "core/buffers/flow/floatFlowBuffer.h"

namespace corecvs {

FloatFlowBuffer::FloatFlowBuffer(FlowBuffer *that)
    : FloatFlowBufferBase(that->h, that->w, true)
{
    for (int i = 0; i < that->h; i++)
    {
        for (int j = 0; j < that->w; j++)
        {
            if (!that->isElementKnown(i, j))
                continue;

            FlowElement shift = that->element(i, j);
            this->element(i, j) = FloatFlow(Vector2dd(shift.x(), shift.y()));
        }
    }
}

} //namespace corecvs

