#ifndef QRK_C_URG_CTRL_H
#define QRK_C_URG_CTRL_H

/*!
  \file
  \brief URG 制御

  \author Satofumi KAMIMURA

  $Id: urg_ctrl.h 1300 2009-09-15 06:36:54Z satofumi $

  \todo 各関数に使用例を定義する
*/

#if !defined(NO_INTENSITY)
#define USE_INTENSITY
#endif

#include "urg_t.h"


/*!
  \brief オプション用パラメータ
*/
enum {
  UrgLineWidth = 64 + 1 + 1,    /*!< １行の最大長 */
  UrgInfinityTimes = 0,         /*!< 連続データ送信指定 */
};


/*!
  \brief URG のコマンドタイプ
*/
typedef enum {
  URG_GD,                       /*!< GD コマンド */
  URG_GD_INTENSITY,             /*!< GD コマンド(強度データ付き) */
  URG_GS,                       /*!< GS コマンド */
  URG_MD,                       /*!< MD コマンド */
  URG_MD_INTENSITY,             /*!< MD コマンド(強度データ付き) */
  URG_MS,                       /*!< MS コマンド */
} urg_request_type;


/*!
  \brief URG データ範囲指定の省略用
*/
enum {
  URG_FIRST = -1,          /*!< 全体データを取得するときの開始位置  */
  URG_LAST = -1,           /*!< 全体データを取得するときの終了位置  */

  UrgInvalidTimestamp = -1,     /*!< タイムスタンプのエラー値 */
};


/*!
  \brief 接続

  \param[in,out] urg URG 制御の構造体
  \param[in] device 接続デバイス
  \param[in] baudrate 接続ボーレート

  \retval 0 正常
  \retval <0 エラー

  \see gd_scan.c, md_scan.c

  使用例
\code
urg_t urg;

// 接続
if (urg_connect(&urg, "COM3", 115200) < 0) {
  printf("urg_connect: %s\n", urg_error(&urg));
  return -1;
}

...

urg_disconnect(&urg); \endcode
*/
extern int urg_connect(urg_t *urg, const char *device, long baudrate);


/*!
  \brief 切断

  \param[in,out] urg URG 制御の構造体

  \see urg_connect()
  \see gd_scan.c, md_scan.c
*/
extern void urg_disconnect(urg_t *urg);


/*!
  \brief 接続中かを返す

  \param[in,out] urg URG 制御の構造体

  \retval 0 接続中
  \retval <0 未接続

  \see urg_connect(), urg_disconnect()

  使用例
\code
if (urg_isConnected(&urg) < 0) {
  printf("not connected.\n");
} else {
  printf("connected.\n");
} \endcode
*/
extern int urg_isConnected(const urg_t *urg);


/*!
  \brief エラーを示す文字列の取得

  \param[in,out] urg URG 制御の構造体

  \return エラーを示す文字列

  \see urg_connect()
  \see gd_scan.c, md_scan.c
*/
extern const char *urg_error(const urg_t *urg);


/*!
  \brief バージョン文字列の取得

  \param[in,out] urg URG 制御の構造体
  \param[out] lines バージョン文字列の格納先バッファ
  \param[in] lines_max バージョン文字列格納の最大行

  \retval 0 正常
  \retval <0 エラー

  \attention バッファ１行の長さは #UrgLineWidth [byte] 以上でなければならない

  \see get_version_lines.c
*/
extern int urg_versionLines(urg_t *urg, char* lines[], int lines_max);


/*!
  \brief URG パラメータを返す

  \param[in,out] urg URG 制御の構造体
  \param[out] parameters URG パラメータの構造体

  \retval 0 正常
  \retval <0 エラー

  \see urg_maxDistance(), urg_minDistance(), urg_scanMsec(), urg_dataMax()
  \see get_parameters.c

  get_parameters.c の実行例 (Classic-URG)
  \verbatim
% ./get_parameters
urg_getParameters: No Error.
distance_min: 20
distance_max: 5600
area_total: 1024
area_min: 44
area_max: 725
area_front: 384
scan_rpm: 600

urg_getDistanceMax(): 5600
urg_getDistanceMin(): 20
urg_getScanMsec(): 100
urg_getDataMax(): 726 \endverbatim
  */
extern int urg_parameters(urg_t *urg, urg_parameter_t* parameters);


/*!
  \brief URG センサのタイプ文字列を返す

  \param[in,out] urg URG 制御の構造体

  \retval URG センサのタイプ

  \code
printf("URG type: %s\n", urg_model(&urg)); \endcode
*/
extern const char* urg_model(const urg_t *urg);


/*!
  \brief １スキャンの最大データ数を返す

  \param[in,out] urg URG 制御の構造体

  \retval >=0 １スキャンの最大データ数
  \retval <0 エラー

  \see gd_scan.c

使用例
\code
enum { BufferSize = 2048 };
long data[BufferSize];

...

// URG センサの取得データ最大値が、受信バッファを越えないか確認する
// (動的にバッファサイズを取得する場合には不要)
int data_max = urg_dataMax(&urg);
ASSERT(BufferSize >= data_max);
\endcode
*/
extern int urg_dataMax(const urg_t *urg);


/*!
  \brief １スキャンの計測時間を返す

  モータ速度が 100% 指定のときの１スキャンの計測時間を返す。

  \param[in,out] urg URG 制御の構造体

  \retval >=0 １スキャンの計測時間 [msec]
  \retval <0 エラー

  \see urg_setMotorSpeed()

  \see md_scan.c
*/
extern int urg_scanMsec(const urg_t *urg);


/*!
  \brief 測定可能な最大距離

  \param[in,out] urg URG 制御の構造体

  \retval >=0 測定可能な最大距離 [mm]
  \retval <0 エラー

  \see expand_2d.c

使用例
\code
...
n = urg_receiveData(&urg, data, data_max);

min_distance = urg_minDistance(&urg);
max_distance = urg_minDistance(&urg);

// 有効なデータのみ出力
for (i = 0; i < n; ++i) {
  long length = data[i];
  if ((length > min_distance) && (length < max_distance)) {
    printf("%d:%d\n", i, length);
  }
}
\endcode
*/
extern long urg_maxDistance(const urg_t *urg);


/*!
  \brief 測定可能な最小距離

  \param[in,out] urg URG 制御の構造体

  \retval >=0 測定可能な最小距離 [mm]
  \retval <0 エラー

  \see expand_2d.c
*/
extern long urg_minDistance(const urg_t *urg);


/* ---------------------------------------------------------------------- */


/*!
  \brief 取得データのグループ化設定

  複数個の取得データを１つにまとめ、取得データ量を減少させる。

  \param[in,out] urg URG 制御の構造体
  \param[in] lines １つにまとめる取得データ数

  \retval 0 正常
  \retval < エラー
*/
extern int urg_setSkipLines(urg_t *urg, int lines);


/*!
  \brief スキャン数の間引き設定

  １回のデータ取得後、指定スキャン回数だけデータ取得を休む。

  \param[in,out] urg URG 制御の構造体
  \param[in] frames 間引きフレーム数

  \retval 0 正常
  \retval <0 エラー

  \attention MD/MS コマンドでのデータ取得に対してのみ有効
*/
extern int urg_setSkipFrames(urg_t *urg, int frames);


/*!
  \brief 連続データ取得回数の設定

  \param[in,out] urg URG 制御の構造体
  \param[in] times データ取得回数

  \retval 0 正常
  \retval <0 エラー

  \attention MD/MS コマンドでのデータ取得に対してのみ有効
  \attention 100 回以上のデータ取得を行うときは、#UrgInfinityTimes を指定すること

  使用例
  \code
// 無限回のデータ取得
urg_setCaptureTimes(&urg, UrgInfinityTimes);

...

// レーザを消灯すると、データ取得は中止される
urg_laserOff(&urg);
  \endcode
*/
extern int urg_setCaptureTimes(urg_t *urg, int times);


/*!
  \brief MD/MS データ取得における残りスキャン数を取得

  \param[in,out] urg URG 制御の構造体

  \retval 残りスキャン数。ただし、無限回のデータ取得のときは 100 を返す

  \see md_scan.c
*/
extern int urg_remainCaptureTimes(const urg_t *urg);


/*!
  \brief 距離データの取得要求

  [first_index, last_index] の距離データを要求する。first_index, last_index にそれぞれ URG_FIRST, URG_LAST を指定することで、全範囲のデータ取得を行わせることができる。

  \param[in,out] urg URG 制御の構造体
  \param[in] request_type データ取得タイプ
  \param[in] first_index データ取得開始インデックス
  \param[in] last_index データ取得終了インデックス

  \retval 0 正常
  \retval <0 エラー

  \see urg_receiveData()
  \see gd_scan.c, md_scan.c

使用例
\code
// GD スキャンによる１スキャン分のデータ取得
urg_requestData(&urg, URG_GD, URG_FIRST, URG_LAST);
n = urg_receiveData(&urg, data, data_max);

// MD スキャンによる連続のデータ取得
urg_requestData(&urg, URG_MD, URG_FIRST, URG_LAST);
while (1) {
  n = urg_receiveData(&urg, data, data_max);
  if (n > 0) {
    // データの表示など
    ...
  }
}
\endcode
*/
extern int urg_requestData(urg_t *urg,
                           urg_request_type request_type,
                           int first_index,
                           int last_index);


/*!
  \brief URG データの受信

  \param[in,out] urg URG 制御の構造体
  \param[out] data 受信データの格納先
  \param[in] data_max 受信データの最大数

  \retval 0 > 取得データ数
  \retval <0 エラー

  \see urg_requestData()
*/
extern int urg_receiveData(urg_t *urg, long data[], int data_max);


#if defined(USE_INTENSITY)
/*!
  \brief 強度付きデータの取得

  \param[in,out] urg URG 制御の構造体
  \param[out] data 受信データの格納先
  \param[in] data_max 受信データの最大数
  \param[out] intensity 強度の受信データ格納先

  \attention Classic-URG, Top-URG のみ対応 (2009-04-19 現在)
  \attention Top-URG の ME 対応は、取得データのグルーピング数を２に固定
*/
extern int urg_receiveDataWithIntensity(urg_t *urg, long data[], int data_max,
                                        long intensity[]);
#endif


/*!
  \brief URG データの部分受信

  \param[in,out] urg URG 制御の構造体
  \param[out] data 受信データの格納先
  \param[in] data_max 受信データの最大数
  \param[in] first_index データ格納開始インデックス
  \param[in] last_index データ格納終了インデックス

  \retval 0 > 取得データ数
  \retval <0 エラー

  \attention 未実装

  \see gd_scan.c, md_scan.c
*/
extern int urg_receivePartialData(urg_t *urg, long data[], int data_max,
                                  int first_index, int last_index);


/*!
  \brief タイムスタンプの取得

  \param[in,out] urg URG 制御の構造体

  \retval タイムスタンプ [msec]

  \see md_scan.c

使用例
\code
urg_requestData(&urg, URG_GD, URG_FIRST, URG_LAST);
n = urg_receiveData(&urg, data, data_max);
if (n > 0) {
  long timestamp = urg_recentTimestamp(&urg);
  printf("timestamp: %d\n", timestamp);

  // データの表示など
  // !!!
}
\endcode
*/
extern long urg_recentTimestamp(const urg_t *urg);


/* ---------------------------------------------------------------------- */


/*!
  \brief インデックス値を radian 角度に変換

  \image html urg_sensor_radian.png センサ正面が X 軸の正の方向

  \param[in,out] urg URG 制御の構造体
  \param[in] index インデックス値

  \return 角度 [radian]

  \see index_convert.c
*/
extern double urg_index2rad(const urg_t *urg, int index);


/*!
  \brief インデックス値を degree 角度に変換

  \param[in,out] urg URG 制御の構造体
  \param[in] index インデックス値

  \return 角度 [degree]

  \see index_convert.c
*/
extern int urg_index2deg(const urg_t *urg, int index);


/*!
  \brief radian 角度をインデックス値に変換

  \image html urg_sensor_radian.png センサ正面が X 軸の正の方向

  \param[in,out] urg URG 制御の構造体
  \param[in] radian 角度

  \return インデックス値

  \see index_convert.c
*/
extern int urg_rad2index(const urg_t *urg, double radian);


/*!
  \brief degree 角度をインデックス値に変換

  \param[in,out] urg URG 制御の構造体
  \param[in] degree 角度

  \return インデックス値

  \see index_convert.c
*/
extern int urg_deg2index(const urg_t *urg, int degree);


/* ---------------------------------------------------------------------- */


/*!
  \brief レーザの点灯指示

  \param[in,out] urg URG 制御の構造体

  \retval 0 正常
  \retval <0 エラー

  \see gd_scan.c
*/
extern int urg_laserOn(urg_t *urg);


/*!
  \brief レーザの消灯指示

  \param[in,out] urg URG 制御の構造体

  \retval 0 正常
  \retval <0 エラー
*/
extern int urg_laserOff(urg_t *urg);


/*!
  \brief ハードウェア・リセット

  \retval 0 正常
  \retval <0 エラー
*/
extern int urg_reset(urg_t *urg);


/* ---------------------------------------------------------------------- */


/*!
  \brief タイムスタンプモードに入る

  \param[in,out] urg URG 制御の構造体

  \retval 0 正常
  \retval <0 エラー
*/
extern int urg_enableTimestampMode(urg_t *urg);


/*!
  \brief タイムスタンプモードから抜ける

  \param[in,out] urg URG 制御の構造体

  \retval 0 正常
  \retval <0 エラー
*/
extern int urg_disableTimestampMode(urg_t *urg);


/*!
  \brief タイムスタンプの取得

  TM1 の応答を返す。

  \param[in,out] urg URG 制御の構造体

  \retval >=0 タイムスタンプ [msec]
  \retval <0 エラー

使用例
\code
// タイムスタンプモードに入る
urg_enableTimestampMode(&urg);

// URG のタイムスタンプを連続して取得
for (i = 0; i < 5; ++i) {
  long timestamp = urg_currentTimestamp(&urg);
  printf("timestamp: %ld\n", timestamp)
}

// タイムスタンプモードから抜ける
urg_disableTimestampMode(&urg);
\endcode
*/
extern long urg_currentTimestamp(urg_t *urg);

#endif /* !QRK_C_URG_CTRL_H */
