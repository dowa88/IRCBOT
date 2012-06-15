///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
IRCBOT.cpp

Autor: Dominic Wanner

Beschreibung:
-------------

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "IRCBOT.h"

IRCBOT::IRCBOT()
{
    Kom = NULL;
}

IRCBOT::~IRCBOT()
{
    delete Kom;
    Kom = NULL;
}

void IRCBOT::initBot(Iam _iam)
{
    Kom = new Kommunikater(_iam);
}

void IRCBOT::startBot()
{
    Kom->commitServer();
}