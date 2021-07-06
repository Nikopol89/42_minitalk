CC = gcc -Wall -Werror -Wextra

CLIENT = client

SERVER = server

SRCS_C = client.c

SRCS_S = server.c

OBJS_C = ${SRCS_C:.c=.o}

OBJS_S = ${SRCS_S:.c=.o}

LIBS = -L./libraries/ft_printf -L./libraries/libft -lftprintf -lft

all: $(CLIENT) $(SERVER)

$(CLIENT):$(OBJS_C) lib
	$(CC) -o $(CLIENT) $(OBJS_C) $(LIBS)

$(SERVER):$(OBJS_S) lib
	$(CC) -o $(SERVER) $(OBJS_S) $(LIBS)

lib:
	cd ./libraries/ft_printf; make;
	cd ./libraries/libft; make && make bonus;

clean: cleanclient cleanserver

cleanclient:
	rm -f $(CLIENT) $(OBJS_C)

cleanserver:
	rm -f $(SERVER) $(OBJS_S)

cleanlib:
	cd ./libraries/ft_printf; make fclean;
	cd ./libraries/libft; make fclean;

fclean: cleanclient cleanserver cleanlib

re: clean all

reclient: cleanclient client

reserver: cleanserver server