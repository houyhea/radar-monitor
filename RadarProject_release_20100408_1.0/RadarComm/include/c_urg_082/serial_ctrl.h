#ifndef QRK_C_SERIAL_CTRL_H
#define QRK_C_SERIAL_CTRL_H

/*!
  \file
  \brief シリアル通信

  Serial Communication Interface 制御

  \author Satofumi KAMIMURA

  $Id: serial_ctrl.h 1298 2009-09-14 20:46:35Z satofumi $
*/

#include "serial_t.h"


/*!
  \brief 接続

  \param[in,out] serial シリアル制御の構造体
  \param[in] device 接続デバイス
  \param[in] baudrate 接続ボーレート

  \retval 0 正常
  \retval < 0 エラー
*/
extern int serial_connect(serial_t *serial, const char *device, long baudrate);


/*!
  \brief 切断

  \param[in,out] serial シリアル制御の構造体
*/
extern void serial_disconnect(serial_t *serial);


/*!
  \brief 接続中かを返す

  \param[in] serial シリアル制御の構造体

  \retval 1 接続中
  \retval 0 切断中
*/
extern int serial_isConnected(const serial_t *serial);


/*!
  \brief ボーレートの変更

  \param[in,out] serial シリアル制御の構造体
  \param[in] baudrate ボーレート

  \retval 0 正常
  \retval < 0 エラー
*/
extern int serial_setBaudrate(serial_t *serial, long baudrate);


/*!
  \brief 送信

  \param[in,out] serial シリアル制御の構造体
  \param[in] data 送信データ
  \param[in] data_size 送信サイズ

  \retval >= 0 送信サイズ
  \retval < 0 エラー
*/
extern int serial_send(serial_t *serial, const char *data, int data_size);


/*!
  \brief 受信

  \param[in,out] serial シリアル制御の構造体
  \param[in] data 受信データ格納バッファ
  \param[in] data_size_max 受信バッファの最大サイズ
  \param[in] timeout タイムアウト [msec]

  \retval >= 0 受信サイズ
  \retval < 0 エラー
*/
extern int serial_recv(serial_t *serial,
                       char *data, int data_size_max, int timeout);


/*!
  \brief 受信した１文字を書き戻す

  \param[in,out] serial シリアル制御の構造体
  \param[in] ch 書き戻す１文字

  \attention 読み出しを行わずに、連続して書き戻してはならない
*/
extern void serial_ungetc(serial_t *serial, char ch);


/*!
  \brief 送受信バッファを破棄
*/
extern void serial_clear(serial_t* serial);

#endif /* !QRK_C_SERIAL_CTRL_H */
