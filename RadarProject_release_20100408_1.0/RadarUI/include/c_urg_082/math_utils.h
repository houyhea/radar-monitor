#ifndef QRK_C_MATH_UTILS_H
#define QRK_C_MATH_UTILS_H

/*!
  \file
  \brief 数学関数の補助ファイル

  \author Satofumi KAMIMURA

  $Id: math_utils.h 1300 2009-09-15 06:36:54Z satofumi $
*/

#include "detect_os.h"
#if defined(WINDOWS_OS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifndef M_PI
/* Visual C++ 6.0 用 */
#define M_PI 3.14159265358979323846
#endif

#endif /* !QRK_C_MATH_UTILS_H */
