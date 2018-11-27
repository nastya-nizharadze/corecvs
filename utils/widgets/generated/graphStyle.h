#ifndef GRAPH_STYLE_H_
#define GRAPH_STYLE_H_
/**
 * \file graphStyle.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from graphPlot.xml
 */

/**
 * Helper namespace to hide GraphStyle enum from global context.
 */

namespace GraphStyle {

/** 
 * \brief Graph Style 
 * Graph Style 
 */
enum GraphStyle {
    /** 
     * \brief Draw Lines 
     * Draw Lines 
     */
    DRAW_LINES = 0,
    /** 
     * \brief Draw Dots 
     * Draw Dots 
     */
    DRAW_DOTS = 1,
    /** 
     * \brief Last virtual option to run cycles to
     */
    GRAPH_STYLE_LAST
};


static inline const char *getName(const GraphStyle &value)
{
    switch (value) 
    {
     case DRAW_LINES : return "DRAW_LINES"; break ;
     case DRAW_DOTS : return "DRAW_DOTS"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace GraphStyle

#endif  //GRAPH_STYLE_H_
