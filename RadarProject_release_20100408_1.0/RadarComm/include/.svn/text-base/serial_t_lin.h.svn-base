#ifndef C_SERIAL_T_LIN_H
#define C_SERIAL_T_LIN_H

/*!
  \file
  \brief シリアル制御の構造体 (Linux, Mac 実装)

  \author Satofumi KAMIMURA

  $Id: serial_t_lin.h 136 2008-07-29 10:27:20Z satofumi $
*/

#include <termios.h>


enum {
  SerialErrorStringSize = 256,
};


/*!
  \brief シリアル制御の構造体
*/
typedef struct {

  int errno_;                                //!< エラー番号
  char error_string_[SerialErrorStringSize]; //!< エラー文字列
  int fd_;                                   //!< 接続リソース
  struct termios sio_;                       //!< ターミナル制御
  char last_ch_;                             //!< 書き戻した１文字

} serial_t;

#endif /*! C_SERIAL_T_LIN_H */
