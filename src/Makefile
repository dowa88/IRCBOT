CC = g++
LIBS = -lsqlite3 -lircclient 
OBJECTS = irc_bot.o
NAME = ircBot

ircBot: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<
