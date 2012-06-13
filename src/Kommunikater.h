///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Kommunikater.h

Autor: Dominic Wanner

Beschreibung:
------------------
Dieser teil wählt sich im Server ein und gibt nachrichten nach ausen und hört zu
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _Kommunikater_H_
#define _Kommunikater_H_

#include <stdio.h>
#include "../bib/libircclient-1.6/include/libircclient.h"
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include "Datenbank.h"
#include <string>

struct Iam
{
    char 	* channel;
	char 	* nick;
	char    * server;
};

typedef struct
{
	char 	* channel;
	char 	* nick;

} irc_ctx_t;


class Kommunikater {
    public:
    Kommunikater(Iam _iam);
    ~Kommunikater();

    void commitServer();

    void chanceServerChanelNick(Iam _iam);

    void sendMassage(eintrag e);
    void readListen(eintrag e);

    private:
    SQL* Kom;
    SQL* Doc;
    irc_session_t * session;
    irc_callbacks_t	callbacks;
    Iam iam;
    irc_ctx_t ctx;
    unsigned short port;
};

#endif
