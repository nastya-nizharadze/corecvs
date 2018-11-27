/**
 * \file hardcodeFont.cpp
 * \brief Add Comment Here
 *
 * \ingroup cppcorefiles
 * \date Jun 22, 2010
 * \author alexander
 */

#include "core/utils/global.h"

#include "core/buffers/rgb24/hardcodeFont.h"
namespace corecvs {


uint8_t HardcodeFont::num_glyphs[] = {
    /*0 glyph*/
    /*
    *     ***
    *    *   *
    *    *   *
    *    *   *
    *     ***
    */
    0x0E,
    0x11,
    0x11,
    0x11,
    0x0E,
    /*
    *     **
    *      *
    *      *
    *      *
    *      *
    */
    0x0C,
    0x04,
    0x04,
    0x04,
    0x04,
    /*
    *     ***
    *        *
    *     ***
    *    *
    *    *****
    */
/*    0x0E,
    0x11,
    0x01,
    0x04,
    0x1F,*/
    0x0E,
    0x01,
    0x0E,
    0x10,
    0x1F,
    /*
    *     ***
    *    *   *
    *       *
    *    *   *
    *     ***
    */
    0x0E,
    0x11,
    0x02,
    0x11,
    0x0E,
    /*
    *    *   *
    *    *   *
    *     ****
    *        *
    *        *
    */
    0x11,
    0x11,
    0x0F,
    0x01,
    0x01,
    /*
    *    *****
    *    *
    *     ***
    *        *
    *    ****
    */
    0x1F,
    0x10,
    0x0E,
    0x01,
    0x1E,
    /*
    *     ****
    *    *
    *    ****
    *    *   *
    *     ***
    */
    0x0F,
    0x10,
    0x1E,
    0x11,
    0x0E,
    /*
    *    *****
    *        *
    *      *
    *      *
    *      *
    */
    0x1F,
    0x01,
    0x04,
    0x04,
    0x04,
    /*
    *     ***
    *    *   *
    *     ***
    *    *   *
    *     ***
    */
    0x0E,
    0x11,
    0x0E,
    0x11,
    0x0E,
    /*
    *     ***
    *    *   *
    *     ****
    *        *
    *    ****
    */
    0x0E,
    0x11,
    0x0F,
    0x01,
    0x1E,


};

uint8_t HardcodeFont::symbols_glyphs[] = {
    /*
     *
     *
     *    *****
     *
     *
     */
     0x00,
     0x00,
     0x1F,
     0x00,
     0x00,
     /*
      *  *   *
      *     *
      *    *
      *   *
      *  *   *
      */
     0x11,
     0x02,
     0x04,
     0x08,
     0x11,
     /*
     *
     *
     *
     *    *
     *
     */
     0x00,
     0x00,
     0x00,
     0x00,
     0x04,
     /*
      *    *
      *
      *
      *
      *    *
      */
     0x04,
     0x00,
     0x00,
     0x00,
     0x04,
     /*
      *    *
      *    *
      *    *
      *
      *    *
      */
     0x04,
     0x04,
     0x04,
     0x00,
     0x04,
     /*
      *   ***
      *      *
      *    *
      *
      *    *
      */
     0x0E,
     0x01,
     0x04,
     0x00,
     0x04,
     /*
     *   ***
     *  * *
     *   ***
     *    * *
     *   ***
     */
     0x0E,
     0x14,
     0x0E,
     0x05,
     0x0E,
     /*
     *   * *
     *   * *
     *
     *
     *
     **/
     0x0A,
     0x0A,
     0x00,
     0x00,
     0x00,
     /*
     *    *
     *    *
     *
     *
     *
     **/
     0x04,
     0x04,
     0x00,
     0x00,
     0x00,
     /*
     *
     *
     *
     *
     *  *****
     **/
     0x00,
     0x00,
     0x00,
     0x00,
     0x1F,
     /*
     *  *****
     *  *   *
     *  *   *
     *  *   *
     *  *****
     **/
     0x1F,
     0x11,
     0x11,
     0x11,
     0x1F,
    /*
    *     *
    *    *
    *    *
    *    *
    *     *
    **/
     0x02,
     0x04,
     0x04,
     0x04,
     0x02,
    /*
    *   *
    *    *
    *    *
    *    *
    *   *
    **/
     0x08,
     0x04,
     0x04,
     0x04,
     0x08,
    /*
    *
    *
    *
    *    *
    *   *
    **/
     0x00,
     0x00,
     0x00,
     0x04,
     0x08,
    /*
    *
    *
    *
    *
    *    *
    **/
     0x00,
     0x00,
     0x00,
     0x00,
     0x04,
    /*
    *    **
    *    *
    *    *
    *    *
    *    **
    **/
     0x06,
     0x04,
     0x04,
     0x04,
     0x06,
    /*
    *   **
    *    *
    *    *
    *    *
    *   **
    **/
     0x0C,
     0x04,
     0x04,
     0x04,
     0x0C
};

uint8_t HardcodeFont::alpha_glyphs[] = {
    /*
    *     ***
    *    *   *
    *    *****
    *    *   *
    *    *   *
    */
    0x0E,
    0x11,
    0x1F,
    0x11,
    0x11,
    /*
    *    ****
    *    *   *
    *    ****
    *    *   *
    *    ****
    */
    0x1E,
    0x11,
    0x1E,
    0x11,
    0x1E,
    /*
    *     ***
    *    *   *
    *    *
    *    *   *
    *     ***
    */
    0x0E,
    0x11,
    0x10,
    0x11,
    0x0E,
    /*
    *    ****
    *    *   *
    *    *   *
    *    *   *
    *    ****
    */
    0x1E,
    0x11,
    0x11,
    0x11,
    0x1E,
    /*
    *    *****
    *    *
    *    *****
    *    *
    *    *****
    */
    0x1F,
    0x10,
    0x1F,
    0x10,
    0x1F,
    /*
    *    *****
    *    *
    *    *****
    *    *
    *    *
    */
    0x1F,
    0x10,
    0x1F,
    0x10,
    0x10,
    /*
    *     ***
    *    *
    *    *  **
    *    *   *
    *     ***
    */
    0x0E,
    0x10,
    0x13,
    0x11,
    0x0E,
    /*
    *    *   *
    *    *   *
    *    *****
    *    *   *
    *    *   *
    */
    0x11,
    0x11,
    0x1F,
    0x11,
    0x11,
    /*
    *     ***
    *      *
    *      *
    *      *
    *     ***
    */
    0x0E,
    0x04,
    0x04,
    0x04,
    0x0E,
    /*
    *     ***
    *      *
    *      *
    *      *
    *    **
    */
    0x0E,
    0x04,
    0x04,
    0x04,
    0x18,
    /*
    *    *  **
    *    * *
    *    **
    *    * *
    *    *  **
    */
    0x13,
    0x14,
    0x18,
    0x14,
    0x13,
    /*
    *    *
    *    *
    *    *
    *    *
    *    *****
    */
    0x10,
    0x10,
    0x10,
    0x10,
    0x1F,
    /*
    *    *   *
    *    ** **
    *    * * *
    *    *   *
    *    *   *
    */
    0x11,
    0x1B,
    0x15,
    0x11,
    0x11,
    /*
    *    *   *
    *    **  *
    *    * * *
    *    *  **
    *    *   *
    */
    0x11,
    0x19,
    0x15,
    0x13,
    0x11,
    /*
    *     ***
    *    *   *
    *    *   *
    *    *   *
    *     ***
    */
    0x0E,
    0x11,
    0x11,
    0x11,
    0x0E,
    /*
    *    ****
    *    *   *
    *    ****
    *    *
    *    *
    */
    0x1E,
    0x11,
    0x1E,
    0x10,
    0x10,
    /*
    *     ***
    *    *   *
    *    *   *
    *    *  **
    *     ****
    */
    0x0E,
    0x11,
    0x11,
    0x13,
    0x0F,
    /*
    *    ****
    *    *   *
    *    ****
    *    *   *
    *    *   *
    */
    0x1E,
    0x11,
    0x1E,
    0x11,
    0x11,
    /*
    *     ****
    *    *
    *     ***
    *        *
    *    ****
    */
    0x0F,
    0x10,
    0x0E,
    0x01,
    0x1E,
    /*
     *    *****
     *      *
     *      *
     *      *
     *      *
     */
    0x1F,
    0x04,
    0x04,
    0x04,
    0x04,
    /*
    *    *   *
    *    *   *
    *    *   *
    *    *   *
    *     ***
    */
    0x11,
    0x11,
    0x11,
    0x11,
    0x0E,
    /*
    *    *   *
    *    *   *
    *     * *
    *     * *
    *      *
    */
    0x11,
    0x11,
    0x0A,
    0x0A,
    0x04,
    /*
    *    *   *
    *    *   *
    *    * * *
    *    * * *
    *     * *
    */
    0x11,
    0x11,
    0x15,
    0x15,
    0xA,
    /*
    *    *   *
    *     * *
    *      *
    *     * *
    *    *   *
    */
    0x11,
    0x0A,
    0x04,
    0x0A,
    0x11,
    /*
    *    *   *
    *     * *
    *      *
    *      *
    *      *
    */
    0x11,
    0x0A,
    0x04,
    0x04,
    0x04,
    /*
    *    *****
    *       *
    *      *
    *     *
    *    *****
    */
    0x1F,
    0x02,
    0x04,
    0x08,
    0x1F,

};

HardcodeFont::HardcodeFont()
{
}

HardcodeFont::~HardcodeFont()
{
}

} //namespace corecvs

