#pragma once

/*
* CODED BY Danoni631
* 
* Short System functions for payloads
*/

#include "Methylcyclohexane.h"

namespace System
{
	void EndPayload(HANDLE Payload) // end a thread
	{
		TerminateThread(Payload, 0);
		CloseHandle(Payload);
	}
};