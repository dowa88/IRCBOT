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

/**
* @class Kommunikater
*
* @brief Diese Klasse kümmert sich um die Kommunikation mit dem IRC Server
*
* Der Kommunikater kümmert sich um alle arbeitsteile der Kommunikation. Er verbindet den Bot mit dem Server und Channel, speichert die Log in die Datenbank und gibt Befehle an den Interpreter weiter.
*
*/

/**
* Ein struct das Informationen für das Verbinden mit Sever und Channel beinhaltet
 */
struct Iam
{
    /*@{*/
    char 	* channel; /**< Channel Name*/
	char 	* nick; /**< Nickname */
	char    * server; /**< Server URL */
	/*@}*/
};

/**
* Ein struct das für die libircclient Verbindungsdaten enthält
 */
typedef struct
{
    /*@{*/
	char 	* channel; /**< Channel Name*/
	char 	* nick; /**< Nickname */
	/*@}*/

} irc_ctx_t;

/**
* Diese struct entählt den Status der Kommunikation so wie ein Session von libircclient
 */
typedef struct
{
    /*@{*/
	bool stop; /**< Stopt die Verbindung bei true*/
	bool log; /**< Stopt und Startet das Log führen*/
	irc_session_t * session; /**< Pointer auf die Laufende Session*/
	/*@}*/
}status;


class Kommunikater {
    public:
     /**
    * @brief Kommunikater() Instaliert Kommunikater benötigt Iam struct
    * @param _iam ist das beinhaltet jeweils einen string zu Server, Channel und Nickname
    *
    * Kommunikater wird erstellt benötigt dazu ein Iam struct für die Verbindungsdaten. Zudem wird eine neue Log Datenbank erstellt (alte Datenbank wird gelöscht)
    */
    Kommunikater(Iam _iam);
    ~Kommunikater();

    /**
    * @brief commitServer() verbindet mit Server und Startet irc_run
    *
    * Startet die Verbindung und die irc_run Schleife.
    */
    void commitServer();

    private:
     /**
    * @brief writeListen() Schribt Log einträge in die Log Datenbank
    * @param e Enthät die einzutragende Information
    *
    * Mit dieser Funktion kann der Kommunikater Log daten in die Datenbank schreiben
    */
    static void writeListen(eintrag e);

     /**
    * @brief sendMassageLOG() Gibt gesammte Log Datenbank im Channel zu wie im Terminal aus
    * @param session Benötigt die Session um Log daten in den Channel zu Schreiben - DArf nicht NULL sein
    *
    * Mit dieser Funktion kann der Kommunikater die gesammten LOG daten Ausgeben
    */
    static void sendMassageLOG(irc_session_t * session);

     /**
    * @brief sendMassageLOGFrom() Gibt gesammte Log einträge eines bestimmten User aus.
    * @param session Benötigt die Session um Log daten in den Channel zu Schreiben - DArf nicht NULL sein
    * @param name String vom Nickname
    * Mit dieser Funktion kann der Kommunikater die gesammten LOG daten eines bestimmten Users ausgeben
    */
    static void sendMassageLOGFrom(irc_session_t * session, std::string name);

    /**
    * @brief event_connect() Callback funktion für irc_run Schleife für Connect Event.
    *
    * Für genaue beschreibung der Parameter siehe Dokumentation von libircclient.<br>
    * Beinhaltet Rutine nach der Verbindung mit dem Server.
    */
    static void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /**
    * @brief event_channel() Callback funktion für irc_run Schleife für Connect Event.
    *
    * Für genaue beschreibung der Parameter siehe Dokumentation von libircclient.<br>
    * Beinhaltet Rutine bei Channel Aktivität. So wird ihr geprüft ob eine Eingabe ein Befehl war oder Daten in den Log gehören.
    */
    static void event_channel (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

 /**
    * static Private Variable.
    * SQL* Datenbank für Logeinträge
    */
    static SQL* Doc;
     /**
    * static Private Variable.
    * Interpreter* für Interpretierung von Befehlen
    */
    static Interpreter* Inter;
     /**
    * static Private Variable.
    * status für Akktuellen Status
    */
    static status state;
     /**
    * Private Variable.
    * irc_session_t* Pointer der Session
    */
    irc_session_t * session;
     /**
    * Private Variable.
    * irc_callbacks_t beinhaltet die Callbackfunktionen
    */
    irc_callbacks_t	callbacks;
     /**
    * Private Variable.
    * Iam für Verbindungsdaten
    */
    Iam iam;
     /**
    * Private Variable.
    * irc_ctx_t für libircclient Verbindungsdaten
    */
    irc_ctx_t ctx;
     /**
    * Private Variable.
    * unsigned short für port
    */
    unsigned short port;
};

#endif
