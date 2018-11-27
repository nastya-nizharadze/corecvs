/**
 * \file focusEstimationParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "focusEstimationParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<FocusEstimationParameters>::reflection = Reflection();
template<>
int BaseReflection<FocusEstimationParameters>::dummy = FocusEstimationParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int FocusEstimationParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Focus Estimation Parameters",
        "Focus Estimation Parameters",
        ""
    );

     getReflection()->objectSize = sizeof(FocusEstimationParameters);
     

    DoubleField* field0 = new DoubleField
        (
          FocusEstimationParameters::JUNCTIONCOEF_ID,
          offsetof(FocusEstimationParameters, mJunctionCoef),
          0.1,
          "JunctionCoef",
          "JunctionCoef",
          "JunctionCoef",
          true,
         0,
         1,
         1
        );
    field0->widgetHint=BaseField::SPIN_BOX;
    field0->precision=2;
    fields().push_back(field0);
    /*  */ 
    DoubleField* field1 = new DoubleField
        (
          FocusEstimationParameters::CENTER_COEF_ID,
          offsetof(FocusEstimationParameters, mCenterCoef),
          0.6,
          "Center Coef",
          "Center Coef",
          "Center Coef",
          true,
         0,
         1,
         1
        );
    field1->widgetHint=BaseField::SPIN_BOX;
    field1->precision=2;
    fields().push_back(field1);
    /*  */ 
    BoolField* field2 = new BoolField
        (
          FocusEstimationParameters::PRODUCE_DEBUG_ID,
          offsetof(FocusEstimationParameters, mProduceDebug),
          false,
          "Produce Debug",
          "Produce Debug",
          "Produce Debug"
        );
    field2->widgetHint=BaseField::CHECK_BOX;
    fields().push_back(field2);
    /*  */ 
    BoolField* field3 = new BoolField
        (
          FocusEstimationParameters::COMPUTE_NOISE_ID,
          offsetof(FocusEstimationParameters, mComputeNoise),
          false,
          "Compute Noise",
          "Compute Noise",
          "Compute Noise"
        );
    field3->widgetHint=BaseField::CHECK_BOX;
    fields().push_back(field3);
    /*  */ 
    BoolField* field4 = new BoolField
        (
          FocusEstimationParameters::COMPUTE_OLD_STATS_ID,
          offsetof(FocusEstimationParameters, mComputeOldStats),
          false,
          "Compute Old Stats",
          "Compute Old Stats",
          "Compute Old Stats"
        );
    field4->widgetHint=BaseField::CHECK_BOX;
    fields().push_back(field4);
    /*  */ 
    IntField* field5 = new IntField
        (
          FocusEstimationParameters::EDGE_THRESHOLD_ID,
          offsetof(FocusEstimationParameters, mEdgeThreshold),
          0,
          "edge Threshold",
          "edge Threshold",
          "edge Threshold"
        );
    fields().push_back(field5);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Focus Estimation Parameters")]= &reflection;
   return 0;
}
int FocusEstimationParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


