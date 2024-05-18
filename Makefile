NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRC = ft_split.c ft_strjoin.c ft_strncmp.c get_path.c parsing.c pipex.c here_doc.c get_next_line.c get_next_line_utils.c

OBJ_DIR = obj

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -DBONUS=0 $(CFLAGS) -o $(NAME) $(OBJ)

bonus:
	$(CC) -DBONUS=1 $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean fclean re bonus make