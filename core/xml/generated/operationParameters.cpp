/**
 * \file operationParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "operationParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<OperationParameters>::reflection = Reflection();
template<>
int BaseReflection<OperationParameters>::dummy = OperationParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int OperationParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Operation Parameters",
        "Operation Parameters",
        ""
    );

     getReflection()->objectSize = sizeof(OperationParameters);
     

    EnumField* field0 = new EnumField
        (
          OperationParameters::OPERATION_ID,
          offsetof(OperationParameters, mOperation),
          0,
          "operation",
          "operation",
          "operation",
          new EnumReflection(6
          , new EnumOption(0,"First")
          , new EnumOption(1,"Second")
          , new EnumOption(2,"Add")
          , new EnumOption(3,"Subtract")
          , new EnumOption(4,"Min")
          , new EnumOption(5,"Max")
          )
        );
    field0->widgetHint=BaseField::COMBO_BOX;
    fields().push_back(field0);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Operation Parameters")]= &reflection;
   return 0;
}
int OperationParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


