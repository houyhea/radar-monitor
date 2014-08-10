#ifndef C_URG_T_H
#define C_URG_T_H

/*!
  \file
  \brief URG 制御用の構造体

  \author Satofumi KAMIMURA

  $Id: urg_t.h 341 2008-11-07 07:43:29Z satofumi $
*/

#include "urg_parameter_t.h"
#include "serial_t.h"


/*!
  \brief URG 制御用の定数
*/
typedef enum {
  UrgLaserOff = 0,
  UrgLaserOn,
  UrgLaserUnknown,
} urg_laser_state_t;


/*!
  \brief URG 制御用の構造体
*/
typedef struct {

  serial_t serial_;              /*!< シリアル制御の構造体 */
  int errno_;                    /*!< エラー番号の格納 */
  urg_parameter_t parameters_;   /*!< センサパラメータ */

  int skip_lines_;               /*!< ライン間引き数 */
  int skip_frames_;              /*!< スキャン間引き数(MD/MS のみ) */
  int capture_times_;            /*!< データ取得回数(MD/MS のみ) */

  urg_laser_state_t is_laser_on_; /*!< レーザ消灯中のときに 0 */

  long last_timestamp_;          /*!< 最終のタイムスタンプ */
  int remain_times_;             /*!< データ取得の残り回数 */

} urg_t;

#endif /* ! C_URG_T_H */
