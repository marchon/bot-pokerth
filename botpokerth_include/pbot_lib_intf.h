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

#ifndef __PBOT_LIB_INTF_H__
#define __PBOT_LIB_INTF_H__

#include <stdint.h>

#define PBOT_INTF_VERSION 1  /* version of this file. to be checked  wen receiving pb_fram struct */
#define PB_MAX_NPLAYERS 10   /* maximum number of players */
#define PB_NB_HANDS 	1326
#define PB_CARD_NONE 	255  /* each card have a value between 0 to 63 */

/* pb_action */
#define PB_ACT_LEAVE  -1 /* stop to play */
#define PB_ACT_FOLD   -2 /* fold this hand */
#define PB_ACT_ALLIN  -3 /* go all-in */
#define PB_ACT_NONE   -4 /* no action */
#define PB_ACT_ERROR  -5 /* error (like pb_frame version mismatch */
#define PB_ACT_CHECK  0  /* FIXME */

/* special action */
#define PB_ACT_CALL  -6
#define PB_ACT_BET   -7
#define PB_ACT_RAISE -8

/* button */
#define PB_BT_DEALER 1
#define PB_BT_SBLIND 2
#define PB_BT_BBLIND 4
#define PB_BT_NONE   8
#define PB_BT_OUT    16

/* round name */
#define PB_RD_UNDEF   0
#define PB_RD_PREFLOP 1
#define PB_RD_FLOP    2
#define PB_RD_TURN    3
#define PB_RD_RIVER   4
#define PB_RD_END     5

struct pb_frame_player{
	double cash;		/* player cash */
	double set;		/* */
	int8_t action;		/* action like PB_ACT_FOLD */
	int8_t button;		/* PB_BT_SBLIND etc ... */
#define FL_PLAYER_AGRP 1	/* aggressive player. FIXME: remove me*/
#define FL_PLAYER_AGRF 2
#define FL_PLAYER_AGRT 4
#define FL_PLAYER_AGRR 8
#define FL_PLAYER_AGR_AFTERFLOP (FL_PLAYER_AGRF|FL_PLAYER_AGRT|FL_PLAYER_AGRR)
	int16_t flags;		/* private flags to use with your bot */
	uint8_t id;		/* player uniq id from 0 to 9 */
	uint8_t _pad;		
	uint8_t cards[2];	/* player cards. see cards format below */
#define MAX_STR_NAME 32
	char name[MAX_STR_NAME];/* player name */
	struct pb_frame_player *next;
}__attribute__((packed));

typedef struct pb_frame_player pb_player;

struct pb_frame {
	uint8_t pbot_version;	/* check that this value equal to PBOT_INTF_VERSION */
	uint8_t nplayers;	/* number of players */
	uint8_t naplayers;	/* number of active players */
//	int ismyturn;
	uint8_t playeridturn;	/* id of the player whose it's his turn */
	uint8_t userchair;	/* your id number */
	uint8_t dealerchair;	/* id of the dealer */
	uint8_t betround;	/* PB_RD_PREFLOP, etc ... */
	uint8_t betround_turn;	/* when someone raise, we have play an another turn 
				   and betround_turn is increased */
	double pot;		/* pot value */
	double sets;		/* */
	double sblind;		/* small blind value */
	double bblind;		/* */
	double ante;		/* ante value */
	double highestset;	/* */
	double call; 		/*amount to call */

	uint8_t cards[5];	/* board cards */
	uint8_t _pad2[3];
	
	struct pb_frame_player players[PB_MAX_NPLAYERS];
}__attribute__((packed));

/* every bot IA dll have a pb_process_frame function whose
 * the type is defined as LPPROCESSFRAME
 * this is the function which will be called ever when it
 * your turn to play */
typedef double (*LPPROCESSFRAME)(struct pb_frame *frame);


/* cards format:
 * the number is defined as uint8_t and can be between 0 to 51.
 * PB_CARD_NONE is a special number, used when we don't know the card
 * 
 * to get the card color and the card value from the number, you have
 * compute it like this;
 * card_color = card/13; (0=diamond, 1=heart, 2=spade, 3=club)
 * card_value = card%13; (0=card num°2, ..., 10=jack, ... 13=As) 
 */

#endif /* __PBV4_H__ */
