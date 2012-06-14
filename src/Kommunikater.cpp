///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Kommunikater.cpp

Autor: Dominic Wanner

Beschreibung:
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Kommunikater.h"

SQL* Kommunikater::Kom = new SQL();
SQL* Kommunikater::Doc = new SQL();

void Kommunikater::event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);
	irc_cmd_join (session, ctx->channel, 0);
}

void Kommunikater::event_channel (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
    //printf ("DCC chat [%d] requested from '%s' (%s)\n", dccid, nick, addr);
    eintrag e;
    e.name = origin;
    e.inhalt = params[1];
    writeListen(e);

	//irc_dcc_accept (session, dccid, 0, dcc_recv_callback);
}

Kommunikater::Kommunikater(Iam _iam)
{
    Kom = new SQL();
    Doc = new SQL();
    Kom->openDB("../DB/Kom");
    Doc->openDB("../DB/Doc");
    Doc->deleteDB();
    Doc->createTable("Mitschrift");
    session = NULL;
    iam = _iam;

    ctx.channel = iam.channel;
    ctx.nick = iam.nick;

    memset (&callbacks, 0, sizeof(callbacks));

    port = 6667;

}

Kommunikater::~Kommunikater()
{
    Kom->closeDB();
    delete Kom;

    Doc->closeDB();
    delete Doc;

    irc_destroy_session(session);
    session = NULL;
}

void Kommunikater::commitServer()
{
    callbacks.event_connect = event_connect;
    callbacks.event_channel = event_channel;

    session = irc_create_session (&callbacks);

    irc_set_ctx (session, &ctx);
	irc_option_set (session, LIBIRC_OPTION_STRIPNICKS);

    irc_connect (session, iam.server, 6667, 0, iam.nick, 0, 0);


    irc_run (session);
}

void Kommunikater::writeListen(eintrag e)
{
    Doc->writeDB(e);
}




