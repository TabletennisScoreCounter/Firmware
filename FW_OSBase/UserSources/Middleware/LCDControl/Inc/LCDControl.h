#ifndef LCDCONTROL_H_
#define LCDCONTROL_H_

#include "MiddlewareCommon.h"

/**
 * @brief LCDの初期化を行う
 *
 * @return 正常終了 : Middleware_OK, 異常あり : Middleware_NG
 */
MiddlewareResultTypeDef_t LCDControl_Init();
/**
 * @brief LCDの表示文字列更新
 *
 * @param _line1Str 1行目の文字列
 * @param _line2Str 2行目の文字列
 *
 * @return 正常終了 : Middleware_OK, 異常あり : Middleware_NG
 * @detail 引数にNULLを与えると現状維持
 */
MiddlewareResultTypeDef_t LCDControl_Print(const char* _line1Str, const char* _line2Str);

#endif
