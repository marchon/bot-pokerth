/*****************************************************************************
 * PokerTH - The open source texas holdem engine                             *
 * Copyright (C) 2006-2011 Felix Hammer, Florian Thauer, Lothar May          *
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

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "pbot_lib_intf.h"

struct bot_intf {
	void *handle;
	LPPROCESSFRAME run;
};

static inline int load_bot(const char *dll_name, struct bot_intf *bot)
{
	memset(bot, 0, sizeof(*bot));
	bot->handle = dlopen(dll_name, RTLD_NOW);
	if (!bot->handle) {
		fprintf(stderr, "could not load dll %s\n", dll_name);
		goto err;
	}
	bot->run  = (LPPROCESSFRAME)dlsym(bot->handle, "pb_process_frame" );

	if (!bot->run) {
		fprintf(stderr, "dll bot func not found\n");
		goto err;
	}
	printf("bot loaded\n");
	return 0;

err:
	fprintf(stderr, "%s\n", dlerror());
	if (bot->handle) {
		dlclose(bot->handle);
		bot->handle = NULL;
	}
	return -1;
}

static inline int unload_bot(struct bot_intf *bot)
{
	if (bot->handle) {
		dlclose(bot->handle);
		bot->handle = NULL;
	}
	return 0;
}

