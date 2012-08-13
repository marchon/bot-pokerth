#!/bin/bash

# build bot pokerth from pokerth source
# ramone.castillon@gmail.com


VERSION=0.9.5
PROG=PokerTH-${VERSION}
DIR=${PROG}-src
TAR=${DIR}.tar.bz2

function download()
{
	if [ ! -e ${TAR} ]; then
		wget "http://downloads.sourceforge.net/project/pokerth/pokerth/0.9/PokerTH-0.9.5-src.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fpokerth%2Ffiles%2Fpokerth%2F0.9%2FPokerTH-0.9.5-src.tar.bz2%2Fdownload%3Fuse_mirror%3Dfreefr&ts=1344642091&use_mirror=freefr"
		mv ${TAR}* ${TAR}
	fi

	if [ ! -e ${TAR} ]; then
		echo "cannot get $TAR}"
		exit 1
	fi

	tar -xvjf ${TAR}
}

function apply_bot_patches()
{
	if [ ! -e patches ]; then
		ln -s ../patches patches && \
		quilt push 
	fi

	BOTPOKETH_INCLUDE=./src/engine/local_engine/botpokerth_include
	if [ ! -e $BOTPOKETH_INCLUDE ]; then
		pushd .
		cd ./src/engine/local_engine/
		ln -s ../../../../botpokerth_include botpokerth_include
		popd
	fi	
}

if [ ! -e "${DIR}" ]; then
	download;
fi

if [ ! -e "${DIR}" ]; then
	echo "fatal error. exit"
	exit 1
fi

cd ${DIR} && \
apply_bot_patches
qmake pokerth.pro && \
make

