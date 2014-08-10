#ifndef URG_PARAMETER_T_H
#define URG_PARAMETER_T_H

/*!
  \file
  \brief URG のパラメータ情報

  \author Satofumi KAMIMURA

  $Id: urg_parameter_t.h 411 2008-12-22 05:48:43Z satofumi $
*/


enum {
  UrgParameterLines = 8 + 1 + 1,
};


/*!
  \brief URG のパラメータ情報
*/
typedef struct {
  long distance_min_;		/*!< DMIN 情報 */
  long distance_max_;		/*!< DMAX 情報 */
  int area_total_;		/*!< ARES 情報 */
  int area_min_;		/*!< AMIN 情報 */
  int area_max_;		/*!< AMAX 情報 */
  int area_front_;		/*!< AFRT 情報 */
  int scan_rpm_;		/*!< SCAN 情報 */
} urg_parameter_t;

#endif /* !URG_PARAMETER_T_H */
