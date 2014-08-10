#ifndef QRK_URG_PARAMETER_T_H
#define QRK_URG_PARAMETER_T_H

/*!
  \file
  \brief URG のパラメータ情報

  \author Satofumi KAMIMURA

  $Id: urg_parameter_t.h 1298 2009-09-14 20:46:35Z satofumi $
*/


enum {
  UrgParameterLines = 8 + 1 + 1,
};


/*!
  \brief URG のパラメータ情報
*/
typedef struct {
  char sensor_type[80];         /*!< センサタイプ */
  long distance_min_;           /*!< DMIN 情報 */
  long distance_max_;           /*!< DMAX 情報 */
  int area_total_;              /*!< ARES 情報 */
  int area_min_;                /*!< AMIN 情報 */
  int area_max_;                /*!< AMAX 情報 */
  int area_front_;              /*!< AFRT 情報 */
  int scan_rpm_;                /*!< SCAN 情報 */
} urg_parameter_t;

#endif /* !QRK_URG_PARAMETER_T_H */
