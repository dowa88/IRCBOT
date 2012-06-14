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
Interpreter* Kommunikater::Inter = new Interpreter();
status Kommunikater::state;

THREAD_FUNCTION(myThread)
{
    status * state = (status*) arg;

	while (!state->stop)
	{
		if(state->send)
		{
		    state->send = false;
		}

	}
    irc_cmd_quit(state->session, NULL);
}

Kommunikater::Kommunikater(Iam _iam)
{
    Kom = new SQL();
    Doc = new SQL();
    Kom->openDB("../DB/Kom");
    Doc->openDB("../DB/Doc");
    Doc->createTable("Mitschrift");
    Doc->deleteDB();
    Kom->createTable("Kommunikation");
    session = NULL;
    iam = _iam;

    state.stop = false;
    state.send = false;

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

    delete Inter;

    irc_destroy_session(session);
    session = NULL;
    state.session = NULL;
}

void Kommunikater::event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);
	irc_cmd_join (session, ctx->channel, 0);

	thread_id_t tid;
	CREATE_THREAD(&tid, myThread, &state);
}

void Kommunikater::event_channel (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
    irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);
    eintrag e;
    e.name = origin;
    e.inhalt = params[1];

    int ibf = Inter->searchBF(params[1], ctx->nick);

    if(ibf)
    {
        switch(ibf)
        {
            case 1:
            {
                state.stop = true;
            }break;
            case 2:
            {
                sendMassageLOG(session);
            }
        }
    }
    else
    {
        writeListen(e);
    }
}

void Kommunikater::sendMassageLOG(irc_session_t * session, std::string fromtime, std::string totime, std::string fromdate, std::string todate)
{

}

void Kommunikater::sendMassageLOG(irc_session_t * session)
{
    irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);

    std::vector<eintrag> e = Doc->readDB();

    for (std::vector<eintrag>::iterator it = e.begin(); it!=e.end(); ++it)
    {
        printf("%s\n", it->name.c_str());
        printf("%s\n", it->inhalt.c_str());
        printf("%s\n", it->date.c_str());
        printf("%s\n", it->time.c_str());

        irc_cmd_msg(session, ctx->channel, it->name.c_str());
        irc_cmd_msg(session, ctx->channel, it->inhalt.c_str());
        irc_cmd_msg(session, ctx->channel, it->date.c_str());
        irc_cmd_msg(session, ctx->channel, it->time.c_str());
    }
}

void Kommunikater::commitServer()
{
    callbacks.event_connect = event_connect;
    callbacks.event_channel = event_channel;

    session = irc_create_session (&callbacks);

    irc_set_ctx (session, &ctx);
	irc_option_set (session, LIBIRC_OPTION_STRIPNICKS);

    irc_connect (session, iam.server, 6667, 0, iam.nick, 0, 0);

    state.session = session;
    irc_run (session);
}

void Kommunikater::writeListen(eintrag e)
{
    Doc->writeDB(e);
}




