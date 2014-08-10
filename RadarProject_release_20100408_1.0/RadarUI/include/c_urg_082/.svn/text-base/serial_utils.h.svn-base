#ifndef QRK_SERIAL_UTILS_H
#define QRK_SERIAL_UTILS_H

/*!
  \file
  \brief シリアル送受信の補助

  \author Satofumi KAMIMURA

  $Id: serial_utils.h 783 2009-05-05 08:56:26Z satofumi $

  \todo 入力する引数には、const を付加する
*/

#include "serial_t.h"


/*!
  \brief 改行コードかを返す

  \retval true LF, CR のとき
  \retval false 上記以外のとき
*/
extern int serial_isLF(const char ch);


/*!
  \brief 受信データを読み飛ばす

  ConnectionInterface::clear() とは、タイムアウト時間を指定して読み飛ばせる点が異なる

  \param[in,out] serial シリアル制御の構造体
  \param[in] total_timeout タイムアウト時間の上限 [msec]
  \param[in] each_timeout 受信データ間におけるタイムアウト時間の上限 [msec]
*/
extern void serial_skip(serial_t *serial, int total_timeout,
                        int each_timeout);


/*!
  \brief 改行までの読みだし

  文字列終端に '\\0' を付加して返す

  \param[in,out] serial シリアル制御の構造体
  \param[in] data 受信データ格納バッファ
  \param[in] data_size_max 受信バッファの最大サイズ
  \param[in] timeout タイムアウト [msec]

  \return 受信文字数
*/
extern int serial_getLine(serial_t *serial,
                          char *data, int data_size_max, int timeout);

#endif /* !QRK_SERIAL_UTILS_H */
