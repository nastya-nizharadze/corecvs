#ifndef LINE_DISTORTION_ESTIMATOR_COST_H_
#define LINE_DISTORTION_ESTIMATOR_COST_H_
/**
 * \file lineDistortionEstimatorCost.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from distortion.xml
 */

/**
 * Helper namespace to hide LineDistortionEstimatorCost enum from global context.
 */

namespace LineDistortionEstimatorCost {

/** 
 * \brief Line Distortion Estimator Cost 
 * Line Distortion Estimator Cost 
 */
enum LineDistortionEstimatorCost {
    /** 
     * \brief Line Deviation Cost 
     * Line Deviation Cost 
     */
    LINE_DEVIATION_COST = 0,
    /** 
     * \brief Joint Angle Cost 
     * Joint Angle Cost 
     */
    JOINT_ANGLE_COST = 1,
    /** 
     * \brief Last virtual option to run cycles to
     */
    LINE_DISTORTION_ESTIMATOR_COST_LAST
};


static inline const char *getName(const LineDistortionEstimatorCost &value)
{
    switch (value) 
    {
     case LINE_DEVIATION_COST : return "LINE_DEVIATION_COST"; break ;
     case JOINT_ANGLE_COST : return "JOINT_ANGLE_COST"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace LineDistortionEstimatorCost

#endif  //LINE_DISTORTION_ESTIMATOR_COST_H_
