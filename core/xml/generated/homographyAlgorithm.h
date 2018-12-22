#ifndef HOMOGRAPHY_ALGORITHM_H_
#define HOMOGRAPHY_ALGORITHM_H_
/**
 * \file homographyAlgorithm.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from parameters.xml
 */

/**
 * Helper namespace to hide HomographyAlgorithm enum from global context.
 */

namespace HomographyAlgorithm {

/** 
 * \brief Homography Algorithm 
 * Homography Algorithm 
 */
enum HomographyAlgorithm {
    /** 
     * \brief LSE 
     * LSE 
     */
    LSE = 0,
    /** 
     * \brief LSE1 
     * LSE1 
     */
    LSE1 = 1,
    /** 
     * \brief LSE2 
     * LSE2 
     */
    LSE2 = 2,
    /** 
     * \brief ML 
     * ML 
     */
    ML = 3,
    /** 
     * \brief ML_AFTER_LSE 
     * ML_AFTER_LSE 
     */
    ML_AFTER_LSE = 4,
    /** 
     * \brief Last virtual option to run cycles to
     */
    HOMOGRAPHY_ALGORITHM_LAST
};


static inline const char *getName(const HomographyAlgorithm &value)
{
    switch (value) 
    {
     case LSE : return "LSE"; break ;
     case LSE1 : return "LSE1"; break ;
     case LSE2 : return "LSE2"; break ;
     case ML : return "ML"; break ;
     case ML_AFTER_LSE : return "ML_AFTER_LSE"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace HomographyAlgorithm

#endif  //HOMOGRAPHY_ALGORITHM_H_
