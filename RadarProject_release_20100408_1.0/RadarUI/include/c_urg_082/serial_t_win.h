#ifndef QRK_C_SERIAL_T_WIN_H
#define QRK_C_SERIAL_T_WIN_H

/*!
  \file
  \brief シリアル制御の構造体 (Windows 実装)

  \author Satofumi KAMIMURA

  $Id: serial_t_win.h 1286 2009-09-10 02:19:02Z satofumi $
*/

#include <windows.h>


enum {
  SerialErrorStringSize = 256,
};


/*!
  \brief シリアル制御の構造体
*/
typedef struct {
  HANDLE hCom_;                 /*!< 接続リソース */
  char has_last_ch_;            /*!< 書き戻した文字があるかのフラグ */
  char last_ch_;                /*!< 書き戻した１文字 */
  int current_timeout_;         /*!< タイムアウトの設定時間 [msec] */
} serial_t;

#endif /* !QRK_C_SERIAL_T_LIN_H */
