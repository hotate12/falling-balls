CC = gcc
FLAGS = -w
LDLIBS = -lncursesw

SRCS = main.c ui.c file_io.c falling_balls.c game_result.c
OBJS = $(SRCS:.c=.o)

game: $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

start: game
	./game

clean:
	rm -f $(OBJS) game
