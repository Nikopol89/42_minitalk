CC = gcc -Wall -Werror -Wextra

CLIENT = client

SERVER = server

SRCS_C = client.c

SRCS_S = server.c

OBJS_C = ${SRCS_C:.c=.o}

OBJS_S = ${SRCS_S:.c=.o}

LIBS = -L./libraries/ft_printf -L./libraries/libft -lftprintf -lft

all: lib $(CLIENT) $(SERVER)

$(CLIENT):$(OBJS_C)
	$(CC) -o $(CLIENT) $(OBJS_C) $(LIBS)

$(SERVER):$(OBJS_S)
	$(CC) -o $(SERVER) $(OBJS_S) $(LIBS)

lib:
	make -C ./libraries/ft_printf
	make -C ./libraries/libft

clean: cleanclient cleanserver

cleanclient:
	rm -f $(CLIENT) $(OBJS_C)

cleanserver:
	rm -f $(SERVER) $(OBJS_S)

cleanlib:
	make fclean -C ./libraries/ft_printf
	make fclean -C ./libraries/libft

fclean: cleanclient cleanserver cleanlib

re: clean all

reclient: cleanclient client

reserver: cleanserver server