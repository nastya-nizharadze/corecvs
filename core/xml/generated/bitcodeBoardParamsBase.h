#ifndef BITCODE_BOARD_PARAMS_BASE_H_
#define BITCODE_BOARD_PARAMS_BASE_H_
/**
 * \file bitcodeBoardParamsBase.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from patternDetector.xml
 */

#include "core/reflection/reflection.h"
#include "core/reflection/defaultSetter.h"
#include "core/reflection/printerVisitor.h"

/*
 *  Embed includes.
 */
/*
 *  Additional includes for Composite Types.
 */

// using namespace corecvs;

/*
 *  Additional includes for Pointer Types.
 */

// namespace corecvs {
// }
/*
 *  Additional includes for enum section.
 */
#include "core/xml/generated/bitcodeBoardOrientation.h"

/**
 * \brief Bitcode Board Params Base 
 * Bitcode Board Params Base 
 **/
class BitcodeBoardParamsBase : public corecvs::BaseReflection<BitcodeBoardParamsBase>
{
public:
    enum FieldId {
        VERTICAL_ID,
        CELLSIZE_ID,
        BLACKCOLOR_ID,
        WHITECOLOR_ID,
        IDENTSIZE_ID,
        BOARDHEIGHT_ID,
        BOARDWIDTH_ID,
        CODEWIDTH_ID,
        CODEHEIGHT_ID,
        BITCODEIDENTSIZE_ID,
        BITCODECONFIDENCE_ID,
        BITCODEORIENTATION_ID,
        CENTERTOZEROX_ID,
        CENTERTOZEROY_ID,
        BITCODE_BOARD_PARAMS_BASE_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief vertical 
     * Orientation 
     */
    bool mVertical;

    /** 
     * \brief cellSize 
     * Chess cells size in pixels 
     */
    int mCellSize;

    /** 
     * \brief blackColor 
     * shades of gray for black chesses 
     */
    int mBlackColor;

    /** 
     * \brief whiteColor 
     * shades of gray for white chesses 
     */
    int mWhiteColor;

    /** 
     * \brief identSize 
     * white ident size around chessboard in chesses 
     */
    double mIdentSize;

    /** 
     * \brief boardHeight 
     * size of the chessboard in chesses 
     */
    int mBoardHeight;

    /** 
     * \brief boardWidth 
     * size of the chessboard in chesses 
     */
    int mBoardWidth;

    /** 
     * \brief codeWidth 
     * width and height of the bitcode in chesses 
     */
    int mCodeWidth;

    /** 
     * \brief codeHeight 
     * width and height of the bitcode in chesses 
     */
    int mCodeHeight;

    /** 
     * \brief bitcodeIdentSize 
     * ident between chessboard and bitcode in chesses 
     */
    double mBitcodeIdentSize;

    /** 
     * \brief bitcodeConfidence 
     * Area in which the stats are collected during detection 
     */
    double mBitcodeConfidence;

    /** 
     * \brief bitcodeOrientation 
     * bitcodeOrientation 
     */
    int mBitcodeOrientation;

    /** 
     * \brief CenterToZeroX 
     * X Distance from grid center to Traget Point 
     */
    double mCenterToZeroX;

    /** 
     * \brief CenterToZeroY 
     * Y Distance from grid center to Traget Point 
     */
    double mCenterToZeroY;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit();

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    bool vertical() const
    {
        return mVertical;
    }

    int cellSize() const
    {
        return mCellSize;
    }

    int blackColor() const
    {
        return mBlackColor;
    }

    int whiteColor() const
    {
        return mWhiteColor;
    }

    double identSize() const
    {
        return mIdentSize;
    }

    int boardHeight() const
    {
        return mBoardHeight;
    }

    int boardWidth() const
    {
        return mBoardWidth;
    }

    int codeWidth() const
    {
        return mCodeWidth;
    }

    int codeHeight() const
    {
        return mCodeHeight;
    }

    double bitcodeIdentSize() const
    {
        return mBitcodeIdentSize;
    }

    double bitcodeConfidence() const
    {
        return mBitcodeConfidence;
    }

    BitcodeBoardOrientation::BitcodeBoardOrientation bitcodeOrientation() const
    {
        return static_cast<BitcodeBoardOrientation::BitcodeBoardOrientation>(mBitcodeOrientation);
    }

    double centerToZeroX() const
    {
        return mCenterToZeroX;
    }

    double centerToZeroY() const
    {
        return mCenterToZeroY;
    }

    /* Section with setters */
    void setVertical(bool vertical)
    {
        mVertical = vertical;
    }

    void setCellSize(int cellSize)
    {
        mCellSize = cellSize;
    }

    void setBlackColor(int blackColor)
    {
        mBlackColor = blackColor;
    }

    void setWhiteColor(int whiteColor)
    {
        mWhiteColor = whiteColor;
    }

    void setIdentSize(double identSize)
    {
        mIdentSize = identSize;
    }

    void setBoardHeight(int boardHeight)
    {
        mBoardHeight = boardHeight;
    }

    void setBoardWidth(int boardWidth)
    {
        mBoardWidth = boardWidth;
    }

    void setCodeWidth(int codeWidth)
    {
        mCodeWidth = codeWidth;
    }

    void setCodeHeight(int codeHeight)
    {
        mCodeHeight = codeHeight;
    }

    void setBitcodeIdentSize(double bitcodeIdentSize)
    {
        mBitcodeIdentSize = bitcodeIdentSize;
    }

    void setBitcodeConfidence(double bitcodeConfidence)
    {
        mBitcodeConfidence = bitcodeConfidence;
    }

    void setBitcodeOrientation(BitcodeBoardOrientation::BitcodeBoardOrientation bitcodeOrientation)
    {
        mBitcodeOrientation = bitcodeOrientation;
    }

    void setCenterToZeroX(double centerToZeroX)
    {
        mCenterToZeroX = centerToZeroX;
    }

    void setCenterToZeroY(double centerToZeroY)
    {
        mCenterToZeroY = centerToZeroY;
    }

    /* Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mVertical,                  static_cast<const corecvs::BoolField *>(fields()[VERTICAL_ID]));
        visitor.visit(mCellSize,                  static_cast<const corecvs::IntField *>(fields()[CELLSIZE_ID]));
        visitor.visit(mBlackColor,                static_cast<const corecvs::IntField *>(fields()[BLACKCOLOR_ID]));
        visitor.visit(mWhiteColor,                static_cast<const corecvs::IntField *>(fields()[WHITECOLOR_ID]));
        visitor.visit(mIdentSize,                 static_cast<const corecvs::DoubleField *>(fields()[IDENTSIZE_ID]));
        visitor.visit(mBoardHeight,               static_cast<const corecvs::IntField *>(fields()[BOARDHEIGHT_ID]));
        visitor.visit(mBoardWidth,                static_cast<const corecvs::IntField *>(fields()[BOARDWIDTH_ID]));
        visitor.visit(mCodeWidth,                 static_cast<const corecvs::IntField *>(fields()[CODEWIDTH_ID]));
        visitor.visit(mCodeHeight,                static_cast<const corecvs::IntField *>(fields()[CODEHEIGHT_ID]));
        visitor.visit(mBitcodeIdentSize,          static_cast<const corecvs::DoubleField *>(fields()[BITCODEIDENTSIZE_ID]));
        visitor.visit(mBitcodeConfidence,         static_cast<const corecvs::DoubleField *>(fields()[BITCODECONFIDENCE_ID]));
        visitor.visit((int &)mBitcodeOrientation, static_cast<const corecvs::EnumField *>(fields()[BITCODEORIENTATION_ID]));
        visitor.visit(mCenterToZeroX,             static_cast<const corecvs::DoubleField *>(fields()[CENTERTOZEROX_ID]));
        visitor.visit(mCenterToZeroY,             static_cast<const corecvs::DoubleField *>(fields()[CENTERTOZEROY_ID]));
    }

    BitcodeBoardParamsBase()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    BitcodeBoardParamsBase(
          bool vertical
        , int cellSize
        , int blackColor
        , int whiteColor
        , double identSize
        , int boardHeight
        , int boardWidth
        , int codeWidth
        , int codeHeight
        , double bitcodeIdentSize
        , double bitcodeConfidence
        , BitcodeBoardOrientation::BitcodeBoardOrientation bitcodeOrientation
        , double centerToZeroX
        , double centerToZeroY
    )
    {
        mVertical = vertical;
        mCellSize = cellSize;
        mBlackColor = blackColor;
        mWhiteColor = whiteColor;
        mIdentSize = identSize;
        mBoardHeight = boardHeight;
        mBoardWidth = boardWidth;
        mCodeWidth = codeWidth;
        mCodeHeight = codeHeight;
        mBitcodeIdentSize = bitcodeIdentSize;
        mBitcodeConfidence = bitcodeConfidence;
        mBitcodeOrientation = bitcodeOrientation;
        mCenterToZeroX = centerToZeroX;
        mCenterToZeroY = centerToZeroY;
    }

    bool operator ==(const BitcodeBoardParamsBase &other) const 
    {
        if ( !(this->mVertical == other.mVertical)) return false;
        if ( !(this->mCellSize == other.mCellSize)) return false;
        if ( !(this->mBlackColor == other.mBlackColor)) return false;
        if ( !(this->mWhiteColor == other.mWhiteColor)) return false;
        if ( !(this->mIdentSize == other.mIdentSize)) return false;
        if ( !(this->mBoardHeight == other.mBoardHeight)) return false;
        if ( !(this->mBoardWidth == other.mBoardWidth)) return false;
        if ( !(this->mCodeWidth == other.mCodeWidth)) return false;
        if ( !(this->mCodeHeight == other.mCodeHeight)) return false;
        if ( !(this->mBitcodeIdentSize == other.mBitcodeIdentSize)) return false;
        if ( !(this->mBitcodeConfidence == other.mBitcodeConfidence)) return false;
        if ( !(this->mBitcodeOrientation == other.mBitcodeOrientation)) return false;
        if ( !(this->mCenterToZeroX == other.mCenterToZeroX)) return false;
        if ( !(this->mCenterToZeroY == other.mCenterToZeroY)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, BitcodeBoardParamsBase &toSave)
    {
        corecvs::PrinterVisitor printer(out);
        toSave.accept<corecvs::PrinterVisitor>(printer);
        return out;
    }

    void print ()
    {
        std::cout << *this;
    }
};
#endif  //BITCODE_BOARD_PARAMS_BASE_H_
