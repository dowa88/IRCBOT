///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Kommunikater.cpp

Autor: Dominic Wanner

Beschreibung:
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Kommunikater.h"

SQL* Kommunikater::Doc = new SQL();
Interpreter* Kommunikater::Inter = new Interpreter();
status Kommunikater::state;

THREAD_FUNCTION(myThread)
{
    status * state = (status*) arg;

	while (!state->stop)
	{

	}
    irc_cmd_quit(state->session, NULL);
}

Kommunikater::Kommunikater(Iam _iam)
{
    Doc = new SQL();
    Doc->openDB("../DB/Doc");
    Doc->createTable("Mitschrift");
    Doc->deleteDB();

    session = NULL;
    iam = _iam;

    state.stop = false;
    state.log = true;

    ctx.channel = iam.channel;
    ctx.nick = iam.nick;

    memset (&callbacks, 0, sizeof(callbacks));

    port = 6667;

}

Kommunikater::~Kommunikater()
{
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
    std::string bs;

    int ibf = Inter->searchBF(params[1], ctx->nick, &bs);

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
            }break;
            case 3:
            {
                state.log = true;
            }break;
            case 4:
            {
                state.log = false;
            }break;
            case 5:
            {
                sendMassageLOGFrom(session, bs);
            }break;
        }
    }
    else if(state.log)
    {
        writeListen(e);
    }
}

void Kommunikater::sendMassageLOGFrom(irc_session_t * session, std::string name)
{
    irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);

    std::vector<eintrag> e = Doc->search(name);

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
    if(irc_run (session) && !state.stop)
        printf ("Could not connect or I/O error");
}

void Kommunikater::writeListen(eintrag e)
{
    Doc->writeDB(e);
}




