/**
 * \file openCVKLTParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "openCVKLTParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<OpenCVKLTParameters>::reflection = Reflection();
template<>
int BaseReflection<OpenCVKLTParameters>::dummy = OpenCVKLTParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int OpenCVKLTParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "OpenCV KLT Parameters",
        "OpenCV KLT Parameters",
        ""
    );

     getReflection()->objectSize = sizeof(OpenCVKLTParameters);
     

    DoubleField* field0 = new DoubleField
        (
          OpenCVKLTParameters::SELECTORQUALITY_ID,
          offsetof(OpenCVKLTParameters, mSelectorQuality),
          0.01,
          "SelectorQuality",
          "SelectorQuality",
          "SelectorQuality"
        );
    field0->widgetHint=BaseField::SPIN_BOX;
    field0->precision=2;
    fields().push_back(field0);
    /*  */ 
    DoubleField* field1 = new DoubleField
        (
          OpenCVKLTParameters::SELECTORDISTANCE_ID,
          offsetof(OpenCVKLTParameters, mSelectorDistance),
          10,
          "SelectorDistance",
          "SelectorDistance",
          "SelectorDistance"
        );
    field1->widgetHint=BaseField::SPIN_BOX;
    field1->precision=2;
    fields().push_back(field1);
    /*  */ 
    IntField* field2 = new IntField
        (
          OpenCVKLTParameters::SELECTORSIZE_ID,
          offsetof(OpenCVKLTParameters, mSelectorSize),
          7,
          "SelectorSize",
          "SelectorSize",
          "SelectorSize"
        );
    fields().push_back(field2);
    /*  */ 
    IntField* field3 = new IntField
        (
          OpenCVKLTParameters::USEHARRIS_ID,
          offsetof(OpenCVKLTParameters, mUseHarris),
          1,
          "UseHarris",
          "UseHarris",
          "UseHarris"
        );
    fields().push_back(field3);
    /*  */ 
    DoubleField* field4 = new DoubleField
        (
          OpenCVKLTParameters::HARRISK_ID,
          offsetof(OpenCVKLTParameters, mHarrisK),
          0.05,
          "HarrisK",
          "HarrisK",
          "HarrisK"
        );
    field4->widgetHint=BaseField::SPIN_BOX;
    field4->precision=2;
    fields().push_back(field4);
    /*  */ 
    IntField* field5 = new IntField
        (
          OpenCVKLTParameters::KLTSIZE_ID,
          offsetof(OpenCVKLTParameters, mKltSize),
          4,
          "kltSize",
          "kltSize",
          "kltSize"
        );
    fields().push_back(field5);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("OpenCV KLT Parameters")]= &reflection;
   return 0;
}
int OpenCVKLTParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


