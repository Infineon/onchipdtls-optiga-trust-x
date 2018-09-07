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
 * \file  main_xmc4500_sample.c
 *
 * \brief   This sample demonstrates OPTIGA use cases.
 *
 */

/*************************************************************************
 *  required includes
*************************************************************************/

#include <DAVE.h>			//Declarations from DAVE Code Generation (includes SFR declaration)
#include "optiga/comms/optiga_comms.h"
#include "optiga/optiga_util.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"
#include "optiga/common/AuthLibSettings.h"
#include "Helper.h"
#include "optiga/optiga_dtls.h"
#include "optiga/pal/pal_socket.h"

/*************************************************************************
 *  main_xmc4500.c
*************************************************************************/


/*************************************************************************
*  defines and typdefs
*************************************************************************/
#define MAX_BUFFER 1600
uint8_t data_buffer[MAX_BUFFER];

typedef struct sNetworkParameters_d
{
	///Socket type (Datagram or stream)
	int32_t dwSocketType;
	///Communication protocol (TCP or UDP)
	uint8_t bCommsProtType;
	///Port number
	uint16_t wPort;
	/// IP address
	char *pzIpAddress;
	///Timeout
	int32_t wTimeout;
}sNetworkParameters_d;

sNetworkParameters_d psNetworkParameters_d;
optiga_comms_t optiga_comms = {(void*)&ifx_i2c_context_0,NULL,NULL, OPTIGA_COMMS_SUCCESS};

pal_socket_t ethServer_Log = { 0 };

/*************************************************************************
*  function prototypes
*************************************************************************/
static int32_t optiga_init(void);
static uint32_t proxy_get_unix_timer(uint32_t* PdwUnixTime);
/*************************************************************************
*  Global
*************************************************************************/


/*************************************************************************
*  functions
*************************************************************************/
static uint32_t proxy_get_unix_timer(uint32_t* PdwUnixTime)
{
    *PdwUnixTime = 0x58178DA8;

    return 1;
}

static int32_t optiga_init(void)
{
	int32_t status = (int32_t) OPTIGA_LIB_ERROR;

	do
	{
		status = optiga_util_open_application(&optiga_comms);
		if(OPTIGA_LIB_SUCCESS != status)
		{
			XMC_DEBUG( ("Failure: CmdLib_OpenApplication(): 0x%04X\n\r", status) );
			break;
		}

		status = OPTIGA_LIB_SUCCESS;
	} while(0);

	return status;
}

uint8_t message[] = {"\n\n******Mutual Authentication Succesful.This data is from DTLS Client.******\n\n"};

int main(void)
{
	//Return value
	optiga_lib_status_t return_status = OPTIGA_LIB_ERROR;

	// OPTIGA Communication Protection (OCP)
    hdl_t hAppOCPApp;
	sAppOCPConfig_d sAppOCPConfig;
//    uint16_t wRecvDataLen = sizeof(data_buffer);

	DAVE_STATUS_t status;

	// Initialisation of DAVE Apps
    status = DAVE_Init(); /* Initialization of DAVE APPs  */
    if (status == DAVE_STATUS_FAILURE)
    {
        /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
        XMC_DEBUG("DAVE APPs initialization failed\n");

        while (1U)
        {

        }
    }

	do
	{
        if (OPTIGA_LIB_SUCCESS != optiga_init())
        {
        	break;
        }

        Print_Stringline("***Starting Dtls mutual authentication use case***");
        //Configure OCP as DTLS over uDP using Hardware Crypto
        sAppOCPConfig.eConfiguration = eDTLS_12_UDP_HWCRYPTO;
        //Set the mode of OCP library to client
        sAppOCPConfig.eMode = eClient;
        //Set the IP address to which client sends data
        sAppOCPConfig.sNetworkParams.pzIpAddress = "192.168.0.2";
        //Set the port on which this client send the data
        sAppOCPConfig.sNetworkParams.wPort = (uint16_t)50000;
        //Set the PMTU size
        sAppOCPConfig.sNetworkParams.wMaxPmtu = 1500;
        //Set any logging handle if available
        sAppOCPConfig.sLogger.pHdl =  NULL;
        //Set writer to log data
        sAppOCPConfig.sLogger.phfWriter =  NULL;
        //Set callback to get unix time
        sAppOCPConfig.pfGetUnixTIme = (fGetUnixTime_d)proxy_get_unix_timer;
        //Set Certificate type
        sAppOCPConfig.wOIDDevCertificate = (uint16_t)eDEVICE_PUBKEY_CERT_IFX;
        //Set the private key
        sAppOCPConfig.wOIDDevPrivKey = (uint16_t)eFIRST_DEVICE_PRIKEY_1;

        //Invoke OCP_Init to initialise the OCP library
        return_status = OCP_Init(&sAppOCPConfig, &hAppOCPApp);
        Print_Stringline("Result:");
        if(return_status != OCP_LIB_OK)
        {
                PrintLine_ErrorCode("OCP_Init() - Failed:", return_status);
                break;
        }

        // This delay is expected in case of XMC4500 for the LWIP stack initialization.
        // This delay might not be required for other platforms.
        pal_os_timer_delay_in_milliseconds(10000);

        //Invokes OCP_Connect to connect to DTLS server and perform Mutual Authentication
        return_status = OCP_Connect(hAppOCPApp);
        if(return_status != OCP_LIB_OK)
        {
                PrintLine_ErrorCode("OCP_Connect() - Failed:", return_status);
                break;
        }

        Print_Stringline("Data sent to server:");
        Print_Array(message, sizeof(message));

        //Invoke OCP_Send to send data to the DTLS server
        return_status = OCP_Send(hAppOCPApp, message, sizeof(message));
        if(return_status != OCP_LIB_OK)
        {
                PrintLine_ErrorCode("OCP_Send() - Failed:", return_status);
                break;
        }
//
//        //Invokde OCP_Receive to receive Data from DTLS server
//        return_status = OCP_Receive(hAppOCPApp,data_buffer,&wRecvDataLen,5000);
//        if(return_status != OCP_LIB_OK)
//        {
//                PrintLine_ErrorCode("OCP_Receive() - Failed:", return_status);
//                break;
//        }
//
//        Print_Stringline("Data received from server:");
//        Print_Array(data_buffer, wRecvDataLen);
//        Print_Stringline(" ");


	}while(FALSE);
    //Invoke OCP_Disconnect to disconnect with the DTLS Server
    OCP_Disconnect(hAppOCPApp);
	Print_Stringline("***Exiting Dtls mutual authentication use case***");

    return return_status;
}
