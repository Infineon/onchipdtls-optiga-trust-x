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
* \brief This file implements the platform abstraction layer APIs for uart/rs232.
*
* \ingroup  grPAL
* @{
*/

/*************************************************************************
*  required includes
*  Setup common include order for the used types and definitions
*************************************************************************/

#include <DAVE.h>
#include "pal_rs232.h"
#include "optiga/common/ErrorCodes.h"
#include "optiga/common/Logger.h"
/*************************************************************************
*  pal_rs232.c
*************************************************************************/

pal_rs232_t logger_console =
{
  .rs232_config_ptr = (void*)(&uart_0),
  .rs232_rx_flag = 1,
  .rs232_tx_flag = 1
};

pal_rs232_t cunit_console =
{
  .rs232_config_ptr = (void*)(&uart_1),
  .rs232_rx_flag = 1,
  .rs232_tx_flag = 1
};
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
/// @cond hidden
void logger_console_uart_end_of_transmit_callback(void)
{
	logger_console.rs232_tx_flag = 0;
}
void logger_console_uart_end_of_receive_callback(void)
{
	logger_console.rs232_rx_flag = 0;
}
void cunit_console_uart_end_of_transmit_callback(void)
{
	cunit_console.rs232_tx_flag = 0;
}
void cunit_console_uart_end_of_receive_callback(void)
{
	cunit_console.rs232_rx_flag = 0;
}

/**
* Rend Data via UART/RS232
*
*/
//lint --e{714} suppress "Functions are only used for testing purpose"
int32_t UartReadData (uint32_t PdwUartPort, uint8_t* PprgbBuf, uint32_t PdwDataLen)
{
    int32_t i4Status = (int32_t)E_COMMS_FAILURE;
    pal_rs232_t *UartHandler = NULL;
    do
    {

        if(NULL == PprgbBuf)
        {
            break;
        }
        
        switch(PdwUartPort)
        {
            case CONSOLE_PORT:
            {
#ifndef ENABLE_UART_CODE_COVERAGE
                UartHandler = &logger_console;
#endif
            }
            break;
            case CUNIT_PORT:
            {
                UartHandler = &cunit_console;
            }
            break;
            case CODE_COVERAGE_PORT:
            {
#ifdef  ENABLE_UART_CODE_COVERAGE
                UartHandler = &logger_console;
#endif
            }
            break;
            default:
            {
                break;
            }
        }

        if (NULL == UartHandler)
        {
            break;
        }
      
        //lint --e{534} suppress "Return value is not required to be checked"
        pal_rs232_read_data(UartHandler, PprgbBuf, PdwDataLen);

        i4Status = E_COMMS_SUCCESS;
    }while(0);
    
    return i4Status;

}

/**
* Send Data via UART/RS232
*
*/
//lint --e{714} suppress "Functions are only used for testing purpose"
int32_t UartWriteData(uint32_t PdwUartPort, uint8_t* PprgbBuf, uint32_t PdwDataLen)
{
    int32_t i4Status = (int32_t)E_COMMS_FAILURE;
    pal_rs232_t *UartHandler = NULL;

    do
    {

        switch(PdwUartPort)
        {
            case CONSOLE_PORT:
            {
#ifndef ENABLE_UART_CODE_COVERAGE
                UartHandler = &logger_console;
#endif
            }
            break;
            case CUNIT_PORT:
            {
                UartHandler = &cunit_console;
            }
            break;
            case CODE_COVERAGE_PORT:
            {
#ifdef  ENABLE_UART_CODE_COVERAGE
                UartHandler = &logger_console;
#endif
            }
            break;
            default:
            {
                break;
            }
        }
        
        if (NULL == UartHandler)
        {
            break;
        }

        //lint --e{534} suppress "Return value is not required to be checked"
        pal_rs232_write_data(UartHandler, PprgbBuf, PdwDataLen);
         
    } while(0);

    return i4Status;
}
/// @endcond

/**
 * Platform abstraction layer API to write the data to RS232 port.
 * <br>
 *
 *
 *<b>API Details:</b>
 * - The API writes to rs232 port and waits until the transmission is completed and returns success<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #pal_rs232_t pal_rs232_t must not be NULL.<br>
 * - The input #pal_rs232_t p_data_buffer must not be NULL.<br>
 *
 *
 * \param[in] p_rs232_context     Pointer to the pal rs232 context #pal_rs232_t
 * \param[in] p_data_buffer       Pointer to the data to be written
 * \param[in] data_length         Length of the data to be written
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the rs232 write is successfull
 * \retval  #PAL_STATUS_FAILURE  Returns when the rs232 write fails.
 *
 */
pal_status_t pal_rs232_read_data (pal_rs232_t* p_rs232_context,
		                          uint8_t* p_data_buffer,
								  uint32_t data_length)
{
	pal_status_t return_status = PAL_STATUS_FAILURE;

	p_rs232_context->rs232_rx_flag = 1U;

    //lint --e{534} suppress "Return value is not required to be checked"
    UART_Receive(p_rs232_context->rs232_config_ptr, p_data_buffer, data_length);

	while (p_rs232_context->rs232_rx_flag){;}

    return_status = PAL_STATUS_SUCCESS;
    
    return return_status;
}

/**
 * Platform abstraction layer API to read the data from RS232 port.
 * <br>
 *
 *
 *<b>API Details:</b>
 * - The API writes to rs232 port and waits until the transmission is completed and returns success<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #pal_rs232_t pal_rs232_t must not be NULL.<br>
 * - The input #pal_rs232_t p_data_buffer must not be NULL.<br>
 *
 *
 * \param[in] p_rs232_context     Pointer to the pal rs232 context #pal_rs232_t
 * \param[in] p_data_buffer       Pointer to the data to be written
 * \param[in] data_length         Length of the data to be written
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the rs232 write is successfull
 * \retval  #PAL_STATUS_FAILURE  Returns when the rs232 write fails.
 *
 */
pal_status_t pal_rs232_write_data(pal_rs232_t* p_rs232_context,
		                          uint8_t* p_data_buffer,
								  uint32_t data_length)
{
	pal_status_t return_status = PAL_STATUS_FAILURE;

	p_rs232_context->rs232_tx_flag = 1U;

    //lint --e{534} suppress "Return value is not required to be checked"
    UART_Transmit(p_rs232_context->rs232_config_ptr, p_data_buffer, data_length);

	while (p_rs232_context->rs232_tx_flag){;}

    return_status = PAL_STATUS_SUCCESS;

    return return_status;
}

/**
* @}
*/

