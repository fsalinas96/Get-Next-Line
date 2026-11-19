SOURCES := get_next_line.c \
			get_next_line_utils.c

OBJECTS := $(SOURCES:.c=.o)
FLAGS := -Wall -Wextra -Werror
NAME :=  get_next_line.a
BONUS_SOURCES := get_next_line_bonus.c \
				get_next_line_utils_bonus.c

BONUS_OBJECTS := $(BONUS_SOURCES:.c=.o)
BONUS_NAME := get_next_line_bonus.a

all: $(NAME)

%.o: %.c
	cc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

bonus:	$(BONUS_NAME)


$(BONUS_NAME): $(BONUS_OBJECTS)
	ar -rcs $(BONUS_NAME) $(BONUS_OBJECTS)


.PHONY: all re clean fclean bonus