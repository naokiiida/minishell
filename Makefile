NAME := minishell

LIBFT = ../libft
SDIR := src/
ODIR := obj/
IDIR := inc/
LDIR := ext/lib/
LINC := ext/include/readline
SRCS := main.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
INCS = -DREADLINE_LIBRARY -I$(IDIR) -I$(LINC) -I$(LIBFT)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
LDFLAGS := -L$(LDIR) -lhistory -L$(LDIR) -lreadline -L$(LIBFT) -lft
CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS)
CC := cc
MKDIR := mkdir -p
OS = $(shell uname)

ifdef WITH_LEAKS
	CFLAGS += -DLEAK_CHECK -g3 -O0
endif
ifdef WITH_ASAN
	CFLAGS += -fsanitize=address -g3 -O0
endif
ifdef WITH_NDEF
	CFLAGS += -fsanitize=undefined -g3 -O0
endif
ifeq ($(OS), Linux)
	LDFLAGS +=
	CFLAGS += -D__Linux__
endif
ifeq ($(OS), Darwin)
	LDFLAGS +=
	CFLAGS += -D__Apple__
endif

$(NAME): $(OBJS) | $(ODIR)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)

$(ODIR)%.o:$(SDIR)%.c | $(ODIR)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

$(ODIR):
	@echo "Creating directory: $(ODIR)"
	$(MKDIR) $@

all: $(NAME)

clean:
	@make $@ -C $(LIBFT)
	rm -rf $(ODIR)

fclean: clean
	@make $@ -C $(LIBFT)
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean
	@make all

norm: requirements.txt
	pip list --outdated
	pip install -U -r requirements.txt
	norminette $(SRCS)

deps:
	nm -u $(NAME)

l: fclean
	@make WITH_LEAKS=1

san: fclean
	@make WITH_ASAN=1 WITH_NDEF=1

v: all
	valgrind $(NAME)

-include $(DEPS)

.PHONY: all clean fclean re
