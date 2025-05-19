CC = cc

#HEADER = ./

NAME = philo

SRCS =	main.c\
		input_validations.c\
		utils_validations.c\
		parser.c\
		init_mutex.c\
		actions.c\
		utils_actions.c\
		create_philo_thread.c\
		philo_routine.c 

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = build

#CFLAGS = -Werror -Wall -Wextra
THREAD_FLAGS = -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(THREAD_FLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
