// RCSerial.cpp: implementation of the CSerialCommHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SerialCommHelper.h"
#include <Process.h>
#include <string>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CSerialCommHelper::InvalidateHandle(HANDLE& hHandle )
{
	hHandle = INVALID_HANDLE_VALUE;
}


void CSerialCommHelper::CloseAndCleanHandle(HANDLE& hHandle)
{

	BOOL abRet  = CloseHandle( hHandle ) ;
	if ( !abRet )
	{
	}
	InvalidateHandle ( hHandle );

}
CSerialCommHelper::CSerialCommHelper()
{

	InvalidateHandle( m_hThreadTerm );
	InvalidateHandle( m_hThread	);
	InvalidateHandle( m_hThreadStarted );
	InvalidateHandle( m_hCommPort );
	InvalidateHandle( m_hDataRx );
 	
	InitLock();
	m_eState = SS_UnInit;
}

CSerialCommHelper::~CSerialCommHelper()
{

	m_eState = SS_Unknown;
	DelLock();
}

HRESULT CSerialCommHelper:: Init(BYTE byParity,BYTE byStopBits,BYTE byByteSize)
{
	HRESULT hr = S_OK;
	try
	{
		m_hDataRx  = CreateEvent(0,0,0,0);
		//open the COM Port
		std::wstring wtext(szPortName.begin(), szPortName.end());
		m_hCommPort = ::CreateFile(wtext.c_str (),
									GENERIC_READ|GENERIC_WRITE,//access ( read and write)
									0,	//(share) 0:cannot share the COM port						
									0,	//security  (None)				
									OPEN_EXISTING,// creation : open_existing
									FILE_FLAG_OVERLAPPED,// we want overlapped operation
									0// no templates file for COM port...
									);
		if ( m_hCommPort == INVALID_HANDLE_VALUE )
		{
			return E_FAIL;
		}
		
		//now start to read but first we need to set the COM port settings and the timeouts
		if (! ::SetCommMask(m_hCommPort,EV_RXCHAR|EV_TXEMPTY) )
		{
			return E_FAIL;
		}
		
		//now we need to set baud rate etc,
		DCB dcb = {0};
		
		dcb.DCBlength = sizeof(DCB);
		
		if (!::GetCommState (m_hCommPort,&dcb))
		{
			return E_FAIL;
		}
		
		dcb.BaudRate	= this->baud;
		dcb.ByteSize	= byByteSize;
		dcb.Parity		= byParity;
		if ( byStopBits == 1 )
			dcb.StopBits	= ONESTOPBIT;
		else if (byStopBits == 2 ) 
			dcb.StopBits	= TWOSTOPBITS;
		else 
			dcb.StopBits	= ONE5STOPBITS;

		dcb.fDsrSensitivity = 0;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fOutxDsrFlow = 0;

		
		if (!::SetCommState (m_hCommPort,&dcb))
		{
			return E_FAIL;
		}		
		
		//now set the timeouts ( we control the timeout overselves using WaitForXXX()
		COMMTIMEOUTS timeouts;
		
		timeouts.ReadIntervalTimeout					= MAXDWORD; 
		timeouts.ReadTotalTimeoutMultiplier		= 0;
		timeouts.ReadTotalTimeoutConstant			= 0;
		timeouts.WriteTotalTimeoutMultiplier	= 0;
		timeouts.WriteTotalTimeoutConstant		= 0;
		
		if (!SetCommTimeouts(m_hCommPort, &timeouts))
		{
			return E_FAIL;
		}
		//create thread terminator event...
		m_hThreadTerm = CreateEvent(0,0,0,0);
		m_hThreadStarted = CreateEvent(0,0,0,0);
		
		m_hThread			= 	(HANDLE)_beginthreadex(0,0,CSerialCommHelper::ThreadFn,(void*)this,0,0 );

		DWORD dwWait = WaitForSingleObject ( m_hThreadStarted , INFINITE );
				
		CloseHandle(m_hThreadStarted);
		
		InvalidateHandle(m_hThreadStarted );
		m_abIsConnected = true;
		
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	if ( SUCCEEDED(hr) ) 
	{
		m_eState = SS_Init;
	}
	return hr;
 	
}	
	
 
HRESULT CSerialCommHelper:: Start()
{
		
		m_eState = SS_Started;
		return S_OK;

}
HRESULT CSerialCommHelper:: Stop()
{
	
	
	m_eState = SS_Stopped;
	return S_OK;
}
HRESULT CSerialCommHelper:: UnInit()
{
	HRESULT hr = S_OK;
	try
	{
		m_abIsConnected = false;
		SignalObjectAndWait(m_hThreadTerm,m_hThread,INFINITE,FALSE);
		CloseAndCleanHandle( m_hThreadTerm);
		CloseAndCleanHandle( m_hThread);
		CloseAndCleanHandle( m_hDataRx );
		CloseAndCleanHandle( m_hCommPort );
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	if ( SUCCEEDED(hr)) 
		m_eState = SS_UnInit;
	return hr;
}


unsigned __stdcall CSerialCommHelper::ThreadFn(void*pvParam)
{

	CSerialCommHelper* apThis = (CSerialCommHelper*) pvParam ;
	bool abContinue = true;
	DWORD dwEventMask=0;
	
	OVERLAPPED ov;
	memset(&ov,0,sizeof(ov));
	ov.hEvent = CreateEvent( 0,true,0,0);
	HANDLE arHandles[2];
	arHandles[0] = apThis->m_hThreadTerm;

	DWORD dwWait;
	SetEvent(apThis->m_hThreadStarted);
	while (  abContinue )
	{
		
		BOOL abRet = ::WaitCommEvent(apThis->m_hCommPort,&dwEventMask, &ov) ;
		if ( !abRet )
		{
			
		}
		arHandles[1] = ov.hEvent ;
		
		dwWait = WaitForMultipleObjects (2,arHandles,FALSE,INFINITE);
		switch ( dwWait )
		{
		case WAIT_OBJECT_0:
			{
				_endthreadex(1);
			}
			break;
		case WAIT_OBJECT_0 + 1:
			{
				DWORD dwMask;
				if (GetCommMask(apThis->m_hCommPort,&dwMask) )
				{
					if ( dwMask == EV_TXEMPTY )
					{
						ResetEvent ( ov.hEvent );
						continue;
					}
					
				}

				//read data here...
				int iAccum = 0;
				
				apThis->m_theSerialBuffer.LockBuffer();
				
				try 
				{
					std::string szDebug;
					BOOL abRet = false;
					
					DWORD dwBytesRead = 0;
					OVERLAPPED ovRead;
					memset(&ovRead,0,sizeof(ovRead));
					ovRead.hEvent = CreateEvent( 0,true,0,0);

					do
					{
						ResetEvent( ovRead.hEvent  );
						char szTmp[1];
						int iSize  = sizeof ( szTmp );
						memset(szTmp,0,sizeof szTmp);
						abRet = ::ReadFile(apThis->m_hCommPort,szTmp,sizeof(szTmp),&dwBytesRead,&ovRead);
						if (!abRet ) 
						{
							abContinue = FALSE;
							break;
						}
						if ( dwBytesRead > 0 )
						{
							apThis->m_theSerialBuffer.AddData ( szTmp,dwBytesRead );
							iAccum += dwBytesRead;
						}
					}while (/*0);*/dwBytesRead > 0 );
					CloseHandle(ovRead.hEvent );
				}
				catch(...)
				{
				}
				
				//if we are not in started state then we should flush the queue...( we would still read the data)
				if (apThis->GetCurrentState() != SS_Started ) 
				{
					iAccum  = 0;
					apThis->m_theSerialBuffer.Flush ();
				}
				
				apThis->m_theSerialBuffer.UnLockBuffer();
				
				if ( iAccum > 0 )
				{
					apThis->SetDataReadEvent(); 
				}
				ResetEvent ( ov.hEvent );
			}
			break;
		}//switch
	}
	return 0;
}


HRESULT  CSerialCommHelper::CanProcess()
{
	
switch ( m_eState  ) 
{
	case SS_Unknown	:return E_FAIL;
	case SS_UnInit	:return E_FAIL;
	case SS_Started :return S_OK;
	case SS_Init		:
	case SS_Stopped :
			return E_FAIL;
	default:;	

}	
	return E_FAIL;
}

HRESULT CSerialCommHelper::Write (const char* data,DWORD dwSize)
{
	HRESULT hr = CanProcess();
	if ( FAILED(hr)) return hr;
	int iRet = 0 ;
	OVERLAPPED ov;
	memset(&ov,0,sizeof(ov));
	ov.hEvent = CreateEvent( 0,true,0,0);
	DWORD dwBytesWritten = 0;
	//do
	{
		iRet = WriteFile (m_hCommPort,data,dwSize,&dwBytesWritten  ,&ov);
		if ( iRet == 0 )
		{
			WaitForSingleObject(ov.hEvent ,INFINITE);
		}
 
	}//	while ( ov.InternalHigh != dwSize ) ;
	CloseHandle(ov.hEvent);
	std::string szData(data);
	
	return S_OK;
}

HRESULT CSerialCommHelper::Read_Upto	(std::string& data,char chTerminator ,long* alCount,long alTimeOut)
{
	HRESULT hr = CanProcess();
	if ( FAILED(hr)) return hr;

	try
	{
	 	
		std::string szTmp;
		szTmp.erase ();
		long alBytesRead;
		
		bool abFound =  m_theSerialBuffer.Read_Upto(szTmp ,chTerminator,alBytesRead,m_hDataRx );

		if ( abFound ) 
		{
			data = szTmp ;
		}
		else
		{//there are either none or less bytes...
			long iRead = 0;
			bool abContinue =  true;
			while (  abContinue )
			{
				DWORD dwWait  = ::WaitForSingleObject ( m_hDataRx , alTimeOut ) ;
				
				if  ( dwWait == WAIT_TIMEOUT) 
				{
					hr = E_FAIL;
					return hr;
				}
   				
				bool abFound =  m_theSerialBuffer.Read_Upto(szTmp ,chTerminator,alBytesRead,m_hDataRx );
				
				if ( abFound ) 
				{
					data = szTmp;
					return S_OK;
				}

			}
		}
	}
	catch(...)
	{
	}
	return hr;
	
}
HRESULT CSerialCommHelper::Read_N		(std::string& data,long alCount,long  alTimeOut )
{
	HRESULT hr = CanProcess();
	
	if ( FAILED(hr)) 
	{
		return hr;
	}
	
	try
	{
	 	
		std::string szTmp ;
		szTmp.erase();

		
		int iLocal =  m_theSerialBuffer.Read_N(szTmp ,alCount ,m_hDataRx );
		
		if ( iLocal == alCount ) 
		{
			data = szTmp;
		}
		else
		{//there are either none or less bytes...
			long iRead = 0;
			int iRemaining = alCount - iLocal;
			while (  1 )
			{
				
				
				DWORD dwWait  = WaitForSingleObject ( m_hDataRx , alTimeOut ) ;

				if  ( dwWait == WAIT_TIMEOUT ) 
				{
					data.erase ();
					hr = E_FAIL;
					return hr;

				}
				 				
				
				iRead =  m_theSerialBuffer.Read_N(szTmp , iRemaining  ,m_hDataRx);
				iRemaining -= iRead ;
				


				if (  iRemaining  == 0) 
				{
					data = szTmp;
					return S_OK;
				}
			}
		}
	}
	catch(...)
	{
	}
	return hr;
	
}
/*-----------------------------------------------------------------------
	-- Reads all the data that is available in the local buffer.. 
	does NOT make any blocking calls in case the local buffer is empty
-----------------------------------------------------------------------*/
HRESULT CSerialCommHelper::ReadAvailable(std::string& data)
{
	
	HRESULT hr = CanProcess();
	if ( FAILED(hr)) return hr;
	try
	{
		std::string szTemp;
		bool abRet = m_theSerialBuffer.Read_Available (szTemp,m_hDataRx);

		data = szTemp;
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	return hr;

}

std::string CSerialCommHelper::GetPort()
{
	return szPortName;
}
void CSerialCommHelper::SetCPort(std::string PortName)
{
	this->szPortName = PortName;
}
long CSerialCommHelper::GetBaudRate()
{
	return this->baud;
}
void CSerialCommHelper::SetBaudRate(long baudrate)
{
	if (baudrate < 300) baud = CBR_110;
	else if (baudrate < 600) baud = CBR_300;
	else if (baudrate < 1200) baud = CBR_600;
	else if (baudrate < 2400) baud = CBR_1200;
	else if (baudrate < 4800) baud = CBR_2400;
	else if (baudrate < 9600) baud = CBR_4800;
	else if (baudrate < 14400) baud = CBR_9600;
	else if (baudrate < 19200) baud = CBR_14400;
	else if (baudrate < 38400) baud = CBR_19200;
	else if (baudrate < 57600) baud = CBR_38400;
	else if (baudrate < 115200) baud = CBR_57600;
	else if (baudrate < 128000) baud = CBR_115200;
	else if (baudrate < 256000) baud = CBR_128000;
	else baud = CBR_256000;
}

