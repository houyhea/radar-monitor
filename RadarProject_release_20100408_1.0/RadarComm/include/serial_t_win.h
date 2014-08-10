#ifndef C_SERIAL_T_WIN_H
#define C_SERIAL_T_WIN_H

/*!
  \file
  \brief シリアル制御の構造体 (Windows 実装)

  \author Satofumi KAMIMURA

  $Id: serial_t_win.h 136 2008-07-29 10:27:20Z satofumi $
*/

#include <windows.h>


enum {
  SerialErrorStringSize = 256,
};


/*!
  \brief シリアル制御の構造体
*/
typedef struct {

  HANDLE hCom_;                 //!< 接続リソース
  char last_ch_;                //!< 書き戻した１文字

} serial_t;

#endif /*! C_SERIAL_T_LIN_H */
