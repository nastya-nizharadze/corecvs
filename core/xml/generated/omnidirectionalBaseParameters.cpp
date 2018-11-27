/**
 * \file omnidirectionalBaseParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "omnidirectionalBaseParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<OmnidirectionalBaseParameters>::reflection = Reflection();
template<>
int BaseReflection<OmnidirectionalBaseParameters>::dummy = OmnidirectionalBaseParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int OmnidirectionalBaseParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Omnidirectional Base Parameters",
        "Omnidirectional Base Parameters",
        ""
    );

     getReflection()->objectSize = sizeof(OmnidirectionalBaseParameters);
     

    DoubleField* field0 = new DoubleField
        (
          OmnidirectionalBaseParameters::PRINCIPALX_ID,
          offsetof(OmnidirectionalBaseParameters, mPrincipalX),
          240,
          "principalX",
          "principalX",
          "The center of projection \f$x_c\f$",
          true,
         0,
         99999,
         1
        );
    field0->widgetHint=BaseField::SPIN_BOX;
    field0->suffixHint="px";
    field0->precision=2;
    fields().push_back(field0);
    /*  */ 
    DoubleField* field1 = new DoubleField
        (
          OmnidirectionalBaseParameters::PRINCIPALY_ID,
          offsetof(OmnidirectionalBaseParameters, mPrincipalY),
          320,
          "principalY",
          "principalY",
          "The center of projection \f$y_c\f$",
          true,
         0,
         99999,
         1
        );
    field1->widgetHint=BaseField::SPIN_BOX;
    field1->suffixHint="px";
    field1->precision=2;
    fields().push_back(field1);
    /*  */ 
    DoubleField* field2 = new DoubleField
        (
          OmnidirectionalBaseParameters::FOCAL_ID,
          offsetof(OmnidirectionalBaseParameters, mFocal),
          820.427,
          "focal",
          "focal",
          "focal",
          true,
         -99999,
         99999,
         1
        );
    field2->widgetHint=BaseField::SPIN_BOX;
    field2->precision=6;
    fields().push_back(field2);
    /*  */ 
    double mN_dv[] = {0,0,0,0,0,0};
    DoubleVectorField* field3 = new DoubleVectorField
        (
          OmnidirectionalBaseParameters::N_ID,
          offsetof(OmnidirectionalBaseParameters, mN),
          vector<double>(mN_dv, mN_dv + 6),
          6,
          "n",
          "n",
          "n",
          true,
         -99999,
         99999,
         0.01
        );
    field3->precision=6;
    fields().push_back(field3);
    /*  */ 
    DoubleField* field4 = new DoubleField
        (
          OmnidirectionalBaseParameters::SIZEX_ID,
          offsetof(OmnidirectionalBaseParameters, mSizeX),
          240,
          "sizeX",
          "sizeX",
          "Model image resolution X",
          true,
         0,
         99999,
         1
        );
    field4->widgetHint=BaseField::SPIN_BOX;
    field4->suffixHint="px";
    field4->precision=2;
    fields().push_back(field4);
    /*  */ 
    DoubleField* field5 = new DoubleField
        (
          OmnidirectionalBaseParameters::SIZEY_ID,
          offsetof(OmnidirectionalBaseParameters, mSizeY),
          320,
          "sizeY",
          "sizeY",
          "Model image resolution Y",
          true,
         0,
         99999,
         1
        );
    field5->widgetHint=BaseField::SPIN_BOX;
    field5->suffixHint="px";
    field5->precision=2;
    fields().push_back(field5);
    /*  */ 
    DoubleField* field6 = new DoubleField
        (
          OmnidirectionalBaseParameters::DISTORTEDSIZEX_ID,
          offsetof(OmnidirectionalBaseParameters, mDistortedSizeX),
          240,
          "distortedSizeX",
          "distortedSizeX",
          "Source image resolution X",
          true,
         0,
         99999,
         1
        );
    field6->widgetHint=BaseField::SPIN_BOX;
    field6->suffixHint="px";
    field6->precision=2;
    fields().push_back(field6);
    /*  */ 
    DoubleField* field7 = new DoubleField
        (
          OmnidirectionalBaseParameters::DISTORTEDSIZEY_ID,
          offsetof(OmnidirectionalBaseParameters, mDistortedSizeY),
          320,
          "distortedSizeY",
          "distortedSizeY",
          "Source image resolution Y",
          true,
         0,
         99999,
         1
        );
    field7->widgetHint=BaseField::SPIN_BOX;
    field7->suffixHint="px";
    field7->precision=2;
    fields().push_back(field7);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Omnidirectional Base Parameters")]= &reflection;
   return 0;
}
int OmnidirectionalBaseParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


