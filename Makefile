ifeq ($(CC),cc)
	CC := clang
endif
RM =	/bin/rm
MAKE =	/usr/bin/make
MKDIR =	/bin/mkdir

NAME = ft_select

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/objs
CPATH =		$(ROOT)/srcs
HPATH =		$(ROOT)/includes
LIBPATH =	$(ROOT)/libft
LFTHPATH =	$(LIBPATH)/includes

CFLAGS = -g -O3 -Wall -Werror -Wextra -I $(HPATH) -I $(LFTHPATH)
LIBS = -L $(LIBPATH) -lft -ltermcap

SRC = 	ft_select.c \
		init.c \
		reset.c \
		first_steps.c \
		display.c \
		display_select.c \
		moves.c \
		actions.c \
		manage_struct.c \
		cduo_pushbk.c \
		signal.c \

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

.PHONY: all clean fclean re norm

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) -C $(LIBPATH) -j 8
	@echo "Creating OBJ files"
	@echo "Building $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[36mAll is done!\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@echo "Creating OBJ directory"
	@$(MKDIR) $@

clean:
	@echo "Deleting OBJ files"
	@$(RM) -rf $(OPATH)

lib.fclean:
	@$(MAKE) fclean -C $(LIBPATH)

fclean: clean lib.fclean
	@echo "Deleting $(NAME)"
	@$(RM) -f $(NAME)
	@echo "\033[36mAll clear!\033[0m"

re: fclean all

norm: all
	norminette **/*.[ch]

# lil memo
# $@ = rule's name
# $^ = all the rule dependecies
# $< = only the first dependence
# -j 8 => pour que la lib complie en multi thread ;)


# Color for c
#   reset	"\033[0m"
#   RED  	"\033[31m"
#   GRN  	"\033[32m"
#   YEL  	"\033[33m"
#   BLU  	"\033[34m"
#   MAG  	"\033[35m"
#   CYN  	"\033[36m"
#   WHT  	"\033[37m"
