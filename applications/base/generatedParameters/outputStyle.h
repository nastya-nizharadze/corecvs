#ifndef OUTPUT_STYLE_H_
#define OUTPUT_STYLE_H_
/**
 * \file outputStyle.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from presentation.xml
 */

/**
 * Helper namespace to hide OutputStyle enum from global context.
 */

namespace OutputStyle {

/** 
 * \brief Output Style 
 * Output Style 
 */
enum OutputStyle {
    /** 
     * \brief right Frame 
     * !right-cam.png! Frame from the right camera 
     */
    RIGHT_FRAME = 0,
    /** 
     * \brief left Frame 
     * !left-cam.png! Frame from the  left camera 
     */
    LEFT_FRAME = 1,
    /** 
     * \brief sidebyside stereo 
     * !2cam-active.png! Side-by-side images from right and left cameras 
     */
    SIDEBYSIDE_STEREO = 2,
    /** 
     * \brief anaglyph RG 
     * !3d_glasses_rg.png! Red-Green Anaglyph view 
     */
    ANAGLYPH_RG = 3,
    /** 
     * \brief anaglyph RC 
     * !3d_glasses_rc.png! Red-Cyan Anaglyph view 
     */
    ANAGLYPH_RC = 4,
    /** 
     * \brief blend 
     * !2cam-blend.png! Blend two images 
     */
    BLEND = 5,
    /** 
     * \brief none 
     * None. Show black output 
     */
    NONE = 6,
    /** 
     * \brief all 
     * All. Show all output 
     */
    ALL = 7,
    /** 
     * \brief Last virtual option to run cycles to
     */
    OUTPUT_STYLE_LAST
};


static inline const char *getName(const OutputStyle &value)
{
    switch (value) 
    {
     case RIGHT_FRAME : return "RIGHT_FRAME"; break ;
     case LEFT_FRAME : return "LEFT_FRAME"; break ;
     case SIDEBYSIDE_STEREO : return "SIDEBYSIDE_STEREO"; break ;
     case ANAGLYPH_RG : return "ANAGLYPH_RG"; break ;
     case ANAGLYPH_RC : return "ANAGLYPH_RC"; break ;
     case BLEND : return "BLEND"; break ;
     case NONE : return "NONE"; break ;
     case ALL : return "ALL"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace OutputStyle

#endif  //OUTPUT_STYLE_H_
