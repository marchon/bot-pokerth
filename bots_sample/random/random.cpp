/*****************************************************************************
 * Bot-PokerTH - program your own poker bot                                  *
 * Copyright (C) 2012 ramone de castillon. ramone.castillon@gmail.com        *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "pbot_lib_intf.h"

/* Stupid IA which play randomly without looking at his cards 
 * if this bot is stronger than you, then you may considere 
 * playing an another game :p */

/* main function */
extern "C" double pb_process_frame(struct pb_frame *frame)
{
	/* sanity check */
	if (frame->pbot_version != PBOT_INTF_VERSION) {
		printf("pbot_lib_intf version mismatch %d vs %d\n"
			, frame->pbot_version, PBOT_INTF_VERSION);
		return PB_ACT_ERROR;
	}

	/* act randomly */
	int r = random()%10;
	if (r <= 2)
		return PB_ACT_FOLD;
	else if (r <= 5)
		return PB_ACT_CALL;
	else if (r <= 8)
		return frame->highestset *2;
	else
		return PB_ACT_ALLIN;
}

/* called when the dll is initialized */
static void init_dll(void)
{
#ifdef WIN32
	if (AllocConsole()){
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("IA Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
				, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("IA loaded\n");
	}
#endif
}

/* called when the dll is unloaded */
static void dest_dll(void)
{
#ifdef WIN32
	FreeConsole();
#endif
}

#ifdef WIN32


/* DLLMAIN */
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			init_dll();
			break; 
		case DLL_THREAD_ATTACH:
			break; 
		case DLL_THREAD_DETACH:
			break; 
		case DLL_PROCESS_DETACH:
			dest_dll();
			break;
	}

	return TRUE;
}

#else

void __attribute__ ((constructor)) __init_dll(void)
{
	init_dll();
}

void __attribute__ ((destructor)) __dest_dll(void)
{
	dest_dll();
}

#endif

