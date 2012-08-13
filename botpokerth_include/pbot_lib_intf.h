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
#define PB_RD_UNDEF		0
#define PB_RD_PREFLOP	1
#define PB_RD_FLOP		2
#define PB_RD_TURN		3
#define PB_RD_RIVER		4
#define PB_RD_END		5

struct pb_frame_player{
	double cash;
	double set;
	int8_t action;
	int8_t button;
#define FL_PLAYER_AGRP 1	/*aggressive player */
#define FL_PLAYER_AGRF 2
#define FL_PLAYER_AGRT 4
#define FL_PLAYER_AGRR 8
#define FL_PLAYER_AGR_AFTERFLOP (FL_PLAYER_AGRF|FL_PLAYER_AGRT|FL_PLAYER_AGRR)
	int16_t flags;
	uint8_t id;
	uint8_t _pad;
	uint8_t cards[2];
#define MAX_STR_NAME 32
	char name[MAX_STR_NAME];
	struct pb_frame_player *next;
}__attribute__((packed));

typedef struct pb_frame_player pb_player;

struct pb_frame {
	uint8_t pbot_version;
	uint8_t nplayers;	/* number of players */
	uint8_t naplayers;	/* number of active players */
//	int ismyturn;
	uint8_t playeridturn;
	uint8_t userchair;
	uint8_t dealerchair;
	uint8_t betround;
	uint8_t betround_turn;
	double pot;
	double sets;
	double sblind;
	double bblind;
	double ante;
	double highestset;
	double call; 		/*amount to call */

	uint8_t cards[5];	/* board cards */
	uint8_t _pad2[3];
	
	struct pb_frame_player players[PB_MAX_NPLAYERS];
}__attribute__((packed));

typedef double (*LPPROCESSFRAME)(struct pb_frame *frame);

#endif /* __PBV4_H__ */
