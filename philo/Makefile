CC = cc

NAME = philo

SRCS =	main.c\
		input_validations.c\
		utils_validations.c\
		init_rules.c\
		init_forks_mutexes.c\
		actions.c\
		utils_actions.c\
		init_philo.c\
		philo_routine.c\
		handle_threads.c\
		actions_tools.c

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = build

CFLAGS = -Werror -Wall -Wextra
THREAD_FLAGS = -pthread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(THREAD_FLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(OBJS) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
