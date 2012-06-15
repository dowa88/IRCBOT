/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
irc_bot.cpp

Autor: Dominic Wanner

Beschreibung:
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "IRCBOT.h"
#include <unistd.h>



int main(int argc, char* argv[])
{
    if ( argc != 4 )
	{
		printf ("Usage: %s <server> <nick> <channel>\n", argv[0]);
		return 1;
	}

    Iam iam;
    /*char s[] = "gti.twice-irc.de";
    char n[] = "nana";
    char c[] = "#test";*/
    iam.channel= argv[3];
    iam.nick = argv[2];
    iam.server = argv[1];

    IRCBOT *bot = new IRCBOT();
    bot->initBot(iam);
    bot->startBot();
    delete bot;
    bot = NULL;

    return 0;
}
