NAME = philo
VERMILION_RED=\033[1;31m
AZURE_BLUE=\033[1;34m
GOLD_COLOR=\033[38;5;220m
GREEN=\033[0;32m
RESET=\033[0m

SRC_FILES = checker.c \
			free.c \
			init_philosophy.c \
			init_threads.c \
			main.c \
			parsing.c \
			philo_alone.c \
			time.c \
			utils.c \
			utils2.c \

OBJECTS = $(SRC_FILES:.c=.o)
INCLUDE = philo.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I -Ilibft 

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) :$(OBJECTS) $(INCLUDE) Makefile
	@echo "$(GOLD_COLOR)Compiling Philo... $(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) -g3 $(OBJECTS)
	@echo "$(GOLD_COLOR)Philo Compiled !$(RESET)"

clean:
	@echo "$(AZURE_BLUE)Cleaning in progress...$(RESET)"
	@rm -f $(OBJECTS)
	@echo "$(AZURE_BLUE)Cleanup done ! :)$(RESET)"

fclean: clean
	@echo "$(AZURE_BLUE)Deep cleaning in progress...$(RESET)"
	@rm -f $(NAME)
	@echo "$(AZURE_BLUE)Deep Cleaning over ! :)$(RESET)"	

re: fclean $(NAME)

.PHONY: all clean fclean re