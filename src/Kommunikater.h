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

    private:
    static void sendMassage();
    static void writeListen(eintrag e);

    static void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
    static void event_channel (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    static SQL* Kom;
    static SQL* Doc;
    irc_session_t * session;
    irc_callbacks_t	callbacks;
    Iam iam;
    irc_ctx_t ctx;
    unsigned short port;
};

#endif
