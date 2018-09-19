/**
* MIT License
*
* Copyright (c) 2018 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
* \file
*
* \brief    This file defines helper functions used in the use case
*
*/


#ifndef __HELPER_H__
#define __HELPER_H__

/*************************************************************************

 *  required includes

*************************************************************************/

#include "optiga/common/Datatypes.h"

/*************************************************************************

 *  Helper.h

*************************************************************************/

/*************************************************************************

 *  defines

*************************************************************************/
/// Success status
#define STATUS_OK    0x00000000
/// Failure status
#define STATUS_ERROR 0xFFFFFFFF
/*************************************************************************

 *  fundamental typedefs

*************************************************************************/

/*************************************************************************

 *  function prototypes

*************************************************************************/

/// Implements displaying the message in the console without end of line
void Print_String(char_t *pszString);

/// Implements displaying the message in the console with end of line
void Print_Stringline(char_t *pszString);

/// Implements displaying the message with two bytes of value
void PrintLine_StringValueU16(char_t *pszString, uint16_t wLen);

/// Implements displaying the message with error code of four bytes
void PrintLine_ErrorCode(char_t *pszString, int32_t i4ErrorCode);

/// Implements displaying the byte array of specified length
void Print_Array(uint8_t* prgbBuf, uint16_t wLen);

/// Copies the string from the source buffer to the destination buffer.<br>
int32_t Utility_Strcat(char_t * psDest, uint16_t wSizeOfDestBuffer, const char_t * psSrc);

#endif
