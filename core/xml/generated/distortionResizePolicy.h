#ifndef DISTORTION_RESIZE_POLICY_H_
#define DISTORTION_RESIZE_POLICY_H_
/**
 * \file distortionResizePolicy.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from distortion.xml
 */

/**
 * Helper namespace to hide DistortionResizePolicy enum from global context.
 */

namespace DistortionResizePolicy {

/** 
 * \brief Distortion Resize Policy 
 * Distortion Resize Policy 
 */
enum DistortionResizePolicy {
    /** 
     * \brief No Change 
     * No Change 
     */
    NO_CHANGE = 0,
    /** 
     * \brief Force Size 
     * Force Size 
     */
    FORCE_SIZE = 1,
    /** 
     * \brief To Fit Result 
     * To Fit Result 
     */
    TO_FIT_RESULT = 2,
    /** 
     * \brief To No Gaps 
     * To No Gaps 
     */
    TO_NO_GAPS = 3,
    /** 
     * \brief Last virtual option to run cycles to
     */
    DISTORTION_RESIZE_POLICY_LAST
};


static inline const char *getName(const DistortionResizePolicy &value)
{
    switch (value) 
    {
     case NO_CHANGE : return "NO_CHANGE"; break ;
     case FORCE_SIZE : return "FORCE_SIZE"; break ;
     case TO_FIT_RESULT : return "TO_FIT_RESULT"; break ;
     case TO_NO_GAPS : return "TO_NO_GAPS"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace DistortionResizePolicy

#endif  //DISTORTION_RESIZE_POLICY_H_
