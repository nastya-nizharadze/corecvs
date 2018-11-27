/**
 * \file bitcodeBoardParamsBase.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "bitcodeBoardParamsBase.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<BitcodeBoardParamsBase>::reflection = Reflection();
template<>
int BaseReflection<BitcodeBoardParamsBase>::dummy = BitcodeBoardParamsBase::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int BitcodeBoardParamsBase::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Bitcode Board Params Base",
        "Bitcode Board Params Base",
        ""
    );

     getReflection()->objectSize = sizeof(BitcodeBoardParamsBase);
     

    BoolField* field0 = new BoolField
        (
          BitcodeBoardParamsBase::VERTICAL_ID,
          offsetof(BitcodeBoardParamsBase, mVertical),
          true,
          "vertical",
          "vertical",
          "Orientation"
        );
    field0->widgetHint=BaseField::CHECK_BOX;
    fields().push_back(field0);
    /*  */ 
    IntField* field1 = new IntField
        (
          BitcodeBoardParamsBase::CELLSIZE_ID,
          offsetof(BitcodeBoardParamsBase, mCellSize),
          256,
          "cellSize",
          "cellSize",
          "Chess cells size in pixels",
          true,
         0,
         999999,
         1
        );
    field1->suffixHint="px";
    fields().push_back(field1);
    /*  */ 
    IntField* field2 = new IntField
        (
          BitcodeBoardParamsBase::BLACKCOLOR_ID,
          offsetof(BitcodeBoardParamsBase, mBlackColor),
          0,
          "blackColor",
          "blackColor",
          "shades of gray for black chesses",
          true,
         0,
         255,
         1
        );
    fields().push_back(field2);
    /*  */ 
    IntField* field3 = new IntField
        (
          BitcodeBoardParamsBase::WHITECOLOR_ID,
          offsetof(BitcodeBoardParamsBase, mWhiteColor),
          255,
          "whiteColor",
          "whiteColor",
          "shades of gray for white chesses",
          true,
         0,
         255,
         1
        );
    fields().push_back(field3);
    /*  */ 
    DoubleField* field4 = new DoubleField
        (
          BitcodeBoardParamsBase::IDENTSIZE_ID,
          offsetof(BitcodeBoardParamsBase, mIdentSize),
          1,
          "identSize",
          "identSize",
          "white ident size around chessboard in chesses"
        );
    field4->widgetHint=BaseField::SPIN_BOX;
    field4->suffixHint="cells";
    field4->precision=2;
    fields().push_back(field4);
    /*  */ 
    IntField* field5 = new IntField
        (
          BitcodeBoardParamsBase::BOARDHEIGHT_ID,
          offsetof(BitcodeBoardParamsBase, mBoardHeight),
          4,
          "boardHeight",
          "boardHeight",
          "size of the chessboard in chesses"
        );
    field5->suffixHint="cells";
    fields().push_back(field5);
    /*  */ 
    IntField* field6 = new IntField
        (
          BitcodeBoardParamsBase::BOARDWIDTH_ID,
          offsetof(BitcodeBoardParamsBase, mBoardWidth),
          4,
          "boardWidth",
          "boardWidth",
          "size of the chessboard in chesses"
        );
    field6->suffixHint="cells";
    fields().push_back(field6);
    /*  */ 
    IntField* field7 = new IntField
        (
          BitcodeBoardParamsBase::CODEWIDTH_ID,
          offsetof(BitcodeBoardParamsBase, mCodeWidth),
          4,
          "codeWidth",
          "codeWidth",
          "width and height of the bitcode in chesses"
        );
    field7->suffixHint="cells";
    fields().push_back(field7);
    /*  */ 
    IntField* field8 = new IntField
        (
          BitcodeBoardParamsBase::CODEHEIGHT_ID,
          offsetof(BitcodeBoardParamsBase, mCodeHeight),
          2,
          "codeHeight",
          "codeHeight",
          "width and height of the bitcode in chesses"
        );
    field8->suffixHint="cells";
    fields().push_back(field8);
    /*  */ 
    DoubleField* field9 = new DoubleField
        (
          BitcodeBoardParamsBase::BITCODEIDENTSIZE_ID,
          offsetof(BitcodeBoardParamsBase, mBitcodeIdentSize),
          1,
          "bitcodeIdentSize",
          "bitcodeIdentSize",
          "ident between chessboard and bitcode in chesses"
        );
    field9->widgetHint=BaseField::SPIN_BOX;
    field9->suffixHint="cells";
    field9->precision=2;
    fields().push_back(field9);
    /*  */ 
    DoubleField* field10 = new DoubleField
        (
          BitcodeBoardParamsBase::BITCODECONFIDENCE_ID,
          offsetof(BitcodeBoardParamsBase, mBitcodeConfidence),
          0.25,
          "bitcodeConfidence",
          "bitcodeConfidence",
          "Area in which the stats are collected during detection"
        );
    field10->widgetHint=BaseField::SPIN_BOX;
    field10->suffixHint="cells";
    field10->precision=2;
    fields().push_back(field10);
    /*  */ 
    EnumField* field11 = new EnumField
        (
          BitcodeBoardParamsBase::BITCODEORIENTATION_ID,
          offsetof(BitcodeBoardParamsBase, mBitcodeOrientation),
          4,
          "bitcodeOrientation",
          "bitcodeOrientation",
          "bitcodeOrientation",
          new EnumReflection(5
          , new EnumOption(0,"Below",":/new/prefix1/down_alt.png@main.qrc")
          , new EnumOption(1,"Left",":/new/prefix1/back_alt.png@main.qrc")
          , new EnumOption(2,"Above",":/new/prefix1/up_alt.png@main.qrc")
          , new EnumOption(3,"Right",":/new/prefix1/forward_alt.png@main.qrc")
          , new EnumOption(4,"Any",":/new/prefix1/question.png@main.qrc")
          )
        );
    field11->widgetHint=BaseField::COMBO_BOX;
    fields().push_back(field11);
    /*  */ 
    DoubleField* field12 = new DoubleField
        (
          BitcodeBoardParamsBase::CENTERTOZEROX_ID,
          offsetof(BitcodeBoardParamsBase, mCenterToZeroX),
          -3.3,
          "CenterToZeroX",
          "CenterToZeroX",
          "X Distance from grid center to Traget Point",
          true,
         -255,
         255,
         1
        );
    field12->widgetHint=BaseField::SPIN_BOX;
    field12->suffixHint="cells";
    field12->precision=2;
    fields().push_back(field12);
    /*  */ 
    DoubleField* field13 = new DoubleField
        (
          BitcodeBoardParamsBase::CENTERTOZEROY_ID,
          offsetof(BitcodeBoardParamsBase, mCenterToZeroY),
          6,
          "CenterToZeroY",
          "CenterToZeroY",
          "Y Distance from grid center to Traget Point",
          true,
         -255,
         255,
         1
        );
    field13->widgetHint=BaseField::SPIN_BOX;
    field13->suffixHint="cells";
    field13->precision=2;
    fields().push_back(field13);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Bitcode Board Params Base")]= &reflection;
   return 0;
}
int BitcodeBoardParamsBase::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


