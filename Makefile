# Executable
NAME_C			= client
NAME_S			= server
BONUS_C			= client_bonus
BONUS_S			= server_bonus

# Libraries
LIBFT			= ./libft/libft.a

# Compiler and flags
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra

# Sources files
SRC_C			= ./src/client.c
SRC_S			= ./src/server.c

BONUS_SRC_C		= ./bonus/client_bonus.c
BONUS_SRC_S		= ./bonus/server_bonus.c

# Objects files
OBJ_C			= $(addprefix $(OBJDIR)/, $(notdir $(SRC_C:.c=.o)))
OBJ_S			= $(addprefix $(OBJDIR)/, $(notdir $(SRC_S:.c=.o)))
BONUS_OBJ_C		= $(addprefix $(OBJDIR)/, $(notdir $(BONUS_SRC_C:.c=.o)))
BONUS_OBJ_S		= $(addprefix $(OBJDIR)/, $(notdir $(BONUS_SRC_S:.c=.o)))

# Object Directory
OBJDIR 			= obj

# Colors
BOLD			= \033[1m
ITALIC			= \033[3m
UNDER 			= \033[4m
GREEN			= \033[32;1m
INDIGO			= \033[38;2;75;0;130m
CORAL			= \033[38;2;255;127;80m
RESET			= \033[0m

# Targets
all:		$(NAME_C) $(NAME_S)

bonus:		$(BONUS_C) $(BONUS_S)

$(NAME_C): $(LIBFT) $(OBJ_C)
		$(CC) $(CFLAGS) $(OBJ_C) $(LIBFT) -o $(NAME_C)

$(NAME_S): $(LIBFT) $(OBJ_S)
		$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) -o $(NAME_S)
		@echo "$(INDIGO) $(UNDER) $(BOLD) $(ITALIC) ✨Compilation Done✨   $(RESET)"

$(BONUS_C): $(LIBFT) $(BONUS_OBJ_C)
		@$(CC) $(CFLAGS) $(BONUS_OBJ_C) $(LIBFT) -o $(BONUS_C)

$(BONUS_S): $(LIBFT) $(BONUS_OBJ_S)
		@$(CC) $(CFLAGS) $(BONUS_OBJ_S) $(LIBFT) -o $(BONUS_S)
		@echo "$(CORAL) $(UNDER) $(BOLD) $(ITALIC) ✨BONUS Compilation Done✨   $(RESET)"

$(LIBFT): 
		@$(MAKE) -C ./libft

$(OBJDIR)/%.o: ./src/%.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./bonus/%.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
		@$(MAKE) clean -C ./libft
		@rm -rf $(OBJDIR)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -f $(NAME_C)
		@rm -f $(NAME_S)
		@rm -f $(BONUS_C)
		@rm -f $(BONUS_S)
		@echo "$(GREEN) $(ITALIC)	  ✅ ✅ ✅ $(RESET)"

re:		fclean all

.PHONY: all clean fclean re bonus
