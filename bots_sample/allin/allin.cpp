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
#include "pbot_lib_intf.h"

/* IA strategy of this bot:
   play all in with strong cards, and fold any other cards */


static uint8_t card_color(uint8_t card)
{
	return card/13;
}

static uint8_t card_value(uint8_t card)
{
	return card%13;
}

/* return 1 if the hand is a good one */
static int is_good_hand(uint8_t cards[2])
{
	uint8_t c1 = card_value(cards[0]);
	uint8_t c2 = card_value(cards[1]);

	/* pair with at least {8,8} and up to {As,As} */
	if (c1 == c2 && c1 >= 7) {
		return 1;
	}
	/* both cards are at least Jack */
	if (c1 >= 10 && c2 >= 10) {
		return 1;
	}
	return 0;
}

/* main function called by bot-pokerth */
extern "C" double pb_process_frame(struct pb_frame *frame)
{
	uint8_t user_chair = frame->userchair;

	/* sanity check */
	if (frame->pbot_version != PBOT_INTF_VERSION) {
		printf("pbot_lib_intf version mismatch %d vs %d\n"
			, frame->pbot_version, PBOT_INTF_VERSION);
		return PB_ACT_ERROR;
	}

	if (is_good_hand(frame->players[user_chair].cards))
		return PB_ACT_ALLIN;
	else
		return PB_ACT_FOLD;
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

