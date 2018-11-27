#ifndef OUTPUT_TYPE_H_
#define OUTPUT_TYPE_H_
/**
 * \file outputType.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from bufferFilters.xml
 */

/**
 * Helper namespace to hide OutputType enum from global context.
 */

namespace OutputType {

/** 
 * \brief Output Type 
 * Output Type 
 */
enum OutputType {
    /** 
     * \brief Left Frame 
     * Left Frame 
     */
    LEFT_FRAME = 0,
    /** 
     * \brief Right Frame 
     * Right Frame 
     */
    RIGHT_FRAME = 1,
    /** 
     * \brief Last virtual option to run cycles to
     */
    OUTPUT_TYPE_LAST
};


static inline const char *getName(const OutputType &value)
{
    switch (value) 
    {
     case LEFT_FRAME : return "LEFT_FRAME"; break ;
     case RIGHT_FRAME : return "RIGHT_FRAME"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace OutputType

#endif  //OUTPUT_TYPE_H_
