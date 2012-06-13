/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
irc_bot.cpp

Autor: Dominic Wanner

Beschreibung:
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Datenbank.h"
#include "Kommunikater.h"
#include <unistd.h>



int main(int argc, char* argv[])
{
    SQL *GG = new SQL();
    Iam iam;
    char s[] = "gti.twice-irc.de";
    char n[] = "nana";
    char c[] = "#test";
    iam.channel= c;
    iam.nick = n;
    iam.server = s;
    Kommunikater* K = new Kommunikater(iam);
    K->commitServer();
    delete K;
    return 1;
}
