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
*
* \file
*
* \brief   This file implements the helper functions to display message in Console.
*
*/

/*************************************************************************
****
 *  required includes

*************************************************************************/


#include <stdio.h>
#include "Helper.h"
#ifndef WINDOWS
#include "optiga/common/Logger.h"
#endif
#include "optiga/common/Datatypes.h"



/*************************************************************************

 *  Helper.c

*************************************************************************/


/*************************************************************************
*  defines
*************************************************************************/


/*************************************************************************
*  function prototypes
*************************************************************************/


/*************************************************************************
*  fundamental typedefs
*************************************************************************/


/*************************************************************************
*  functions
*************************************************************************/

/**
 * This function implements displaying of message without end of line
 *
 * \param[in]  pszString Pointer to a string to be displayed
 *
 * \return  None
 */
Void Print_String(char_t *pszString)
{
#if WINDOWS
	printf("%s", pszString);
	fflush(stdout);
#else
    Util_LogString(CONSOLE_PORT,pszString);
#endif
}

/**
 * This function implements displaying of message with end of line
 *
 * \param[in]  pszString Pointer to a string to be displayed
 *
 * \return  None
 */
Void Print_Stringline(char_t *pszString)
{
#if WINDOWS
	printf("%s\n", pszString);
	fflush(stdout);
#else
    Util_LogStringLine(CONSOLE_PORT,pszString);
#endif

}

/**
 * This function implements displaying of message with two byte value
 *
 * \param[in]  pszString Pointer to a string to be displayed
 * \param[in]  wLen Length of the string
 *
 * \return  None
 */
Void PrintLine_StringValueU16(char_t *pszString, uint16_t wLen)
{
#if WINDOWS
	printf("%s: ", pszString);
    printf("0x%2X\n", wLen);
	fflush(stdout);
#else
    Util_LogInt(CONSOLE_PORT,pszString,(uint32_t)wLen);
#endif
}

/**
 * This function implements displaying of message with four bytes of error code
 *
 * \param[in]  pszString Pointer to a string to be displayed
 * \param[in]  i4ErrorCode Error Code to be displayed
 *
 * \return  None
 */
Void PrintLine_ErrorCode(char_t *pszString, int32_t i4ErrorCode)
{
#if WINDOWS
	printf("%s: ", pszString);
    printf("0x%X\n", i4ErrorCode);
	fflush(stdout);
#else
    CONSOLE_LOGINTEGER(pszString,(uint32_t)i4ErrorCode);
#endif
}

/// Helper method to print array in hex format
/**
 * This function implements displaying of byte array in hex format
 *
 * \param[in]  prgbBuf Pointer to the byte array to be displayed
 * \param[in]  wLen Length of byte array to be displayed
 *
 * \return  None
 */
Void Print_Array(uint8_t* prgbBuf, uint16_t wLen)
{
#if WINDOWS
	uint16_t wIndex;

	for(wIndex = 0; wIndex < wLen; wIndex++)
	{
		if(*(prgbBuf+wIndex) < 16)
		{
			printf("0%X ", *(prgbBuf+wIndex));
		}
		else
		{
			printf("%X ", *(prgbBuf+wIndex));
		}
	}
	printf("\n");
	fflush(stdout);
#else
    Util_DumpHex(prgbBuf,wLen);
#endif
}

#if WINDOWS
/**
*
*  Appends the source string to the destination string.<br>
*
*\param[in,out]   psDest              Pointer to the destination buffer
*\param[in]       wSizeOfDestBuffer   Size of the destination buffer
*\param[in]       eTimeType           Pointer to the destination buffer
*
*/
int32_t Utility_Strcat(char_t * psDest, uint16_t wSizeOfDestBuffer, const char_t * psSrc)
{
    int32_t i4Status = (int32_t)STATUS_ERROR;
    do
    {
        if((NULL == psDest) || (NULL == psSrc))
        {
            break;
        }

        if(0 == wSizeOfDestBuffer)
        {
            break;
        }

        if((wSizeOfDestBuffer - 1) < (uint16_t)(strlen(psSrc)))
        {
            break;
        }

        if(strlen(psSrc) >= (wSizeOfDestBuffer - strlen(psDest)))
        {
            break;
        }

        if(0 != strcat_s(psDest, wSizeOfDestBuffer,  psSrc))
        {
            break;
        }
        i4Status = (int32_t)STATUS_OK;
    }while(0);

    return i4Status;
}
#endif
