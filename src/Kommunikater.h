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
#include "Interpreter.h"
#include <string>
#include <stdbool.h>
#include <vector>

#define CREATE_THREAD(id,func,param)	(pthread_create (id, 0, func, (void *) param) != 0)
#define THREAD_FUNCTION(funcname)		static void * funcname (void * arg)
#define thread_id_t		pthread_t

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

typedef struct
{
	bool stop;
	bool send;
	bool log;
	irc_session_t * session;
}status;


class Kommunikater {
    public:
    Kommunikater(Iam _iam);
    ~Kommunikater();

    void commitServer();

    private:
    static void writeListen(eintrag e);

    static void sendMassageLOG(irc_session_t * session);
    static void sendMassageLOGFrom(irc_session_t * session, std::string name);

    static void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
    static void event_channel (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    static SQL* Doc;
    static Interpreter* Inter;
    static status state;
    irc_session_t * session;
    irc_callbacks_t	callbacks;
    Iam iam;
    irc_ctx_t ctx;
    unsigned short port;
};

#endif
