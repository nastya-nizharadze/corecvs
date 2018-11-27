#ifndef FLOW_STYLE_H_
#define FLOW_STYLE_H_
/**
 * \file flowStyle.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from presentation.xml
 */

/**
 * Helper namespace to hide FlowStyle enum from global context.
 */

namespace FlowStyle {

/** 
 * \brief Flow Style 
 * Flow Style 
 */
enum FlowStyle {
    /** 
     * \brief dont show flow 
     * don't show flow 
     */
    DONT_SHOW_FLOW = 0,
    /** 
     * \brief fast colored dots 
     * fast colored dots 
     */
    FAST_COLORED_DOTS = 1,
    /** 
     * \brief show lines only 
     * show lines only 
     */
    SHOW_LINES_ONLY = 2,
    /** 
     * \brief show colored dots 
     * show colored dots 
     */
    SHOW_COLORED_DOTS = 3,
    /** 
     * \brief show colored lines 
     * show colored lines 
     */
    SHOW_COLORED_LINES = 4,
    /** 
     * \brief show heat coloring 
     * show heat coloring 
     */
    SHOW_HEAT_COLORING = 5,
    /** 
     * \brief Last virtual option to run cycles to
     */
    FLOW_STYLE_LAST
};


static inline const char *getName(const FlowStyle &value)
{
    switch (value) 
    {
     case DONT_SHOW_FLOW : return "DONT_SHOW_FLOW"; break ;
     case FAST_COLORED_DOTS : return "FAST_COLORED_DOTS"; break ;
     case SHOW_LINES_ONLY : return "SHOW_LINES_ONLY"; break ;
     case SHOW_COLORED_DOTS : return "SHOW_COLORED_DOTS"; break ;
     case SHOW_COLORED_LINES : return "SHOW_COLORED_LINES"; break ;
     case SHOW_HEAT_COLORING : return "SHOW_HEAT_COLORING"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace FlowStyle

#endif  //FLOW_STYLE_H_
