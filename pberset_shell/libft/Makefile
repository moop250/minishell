# Target executable/library name
NAME	= libft.a

# Compiler
CC		= cc

# Compiler flags
CFLAGS	= -Wall -Wextra -Werror

# Folders
SRCDIR	= src/
OBJDIR	= obj/
HEADDIR	= header/

FD_DIR	= fd_/
MEMDIR	= mem/
CHRDIR	= chr/
NUMDIR	= num/
STRDIR	= str/
LSTDIR	= lst/
GNLDIR	= gnl/
PRTFDIR	= prtf/

# Header files
HEADSRC	= $(HEADDIR)libft.h \
		$(HEADDIR)ft_printf.h \
		$(HEADDIR)get_next_line.h

# Source files
SRCFD_	= ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_puterr_fd \
		ft_puthex_fd \
		ft_putptr_fd \
		ft_putuint_fd

SRCMEM	= ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_memcmp_int \
		ft_free_tab \
		ft_free_int_tab \
		ft_calloc

SRCCHR	= ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_isspace

SRCNUM	= ft_itoa \
		ft_pow10

SRCSTR	= ft_strlen \
		ft_atoi \
		ft_strrchr \
		ft_split \
		ft_strtrim \
		ft_strjoin \
		ft_strmapi \
		ft_striteri \
		ft_strchr \
		ft_strnstr \
		ft_strncmp \
		ft_strlcpy \
		ft_strlcat \
		ft_strdup \
		ft_substr \
		ft_tolower \
		ft_toupper

SRCLST	= ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap

SRCGNL	= get_next_line

SRCPRTF	= ft_printf

SRC		= $(addprefix $(SRCDIR)$(FD_DIR), $(addsuffix .c, $(SRCFD_))) \
		$(addprefix $(SRCDIR)$(MEMDIR), $(addsuffix .c, $(SRCMEM))) \
		$(addprefix $(SRCDIR)$(CHRDIR), $(addsuffix .c, $(SRCCHR))) \
		$(addprefix $(SRCDIR)$(NUMDIR), $(addsuffix .c, $(SRCNUM))) \
		$(addprefix $(SRCDIR)$(STRDIR), $(addsuffix .c, $(SRCSTR))) \
		$(addprefix $(SRCDIR)$(LSTDIR), $(addsuffix .c, $(SRCLST))) \
		$(addprefix $(SRCDIR)$(GNLDIR), $(addsuffix .c, $(SRCGNL))) \
		$(addprefix $(SRCDIR)$(PRTFDIR), $(addsuffix .c, $(SRCPRTF)))

# Object files
OBJ		= $(addprefix $(OBJDIR)$(FD_DIR), $(addsuffix .o, $(SRCFD_))) \
		$(addprefix $(OBJDIR)$(MEMDIR), $(addsuffix .o, $(SRCMEM))) \
		$(addprefix $(OBJDIR)$(CHRDIR), $(addsuffix .o, $(SRCCHR))) \
		$(addprefix $(OBJDIR)$(NUMDIR), $(addsuffix .o, $(SRCNUM))) \
		$(addprefix $(OBJDIR)$(STRDIR), $(addsuffix .o, $(SRCSTR))) \
		$(addprefix $(OBJDIR)$(LSTDIR), $(addsuffix .o, $(SRCLST))) \
		$(addprefix $(OBJDIR)$(GNLDIR), $(addsuffix .o, $(SRCGNL))) \
		$(addprefix $(OBJDIR)$(PRTFDIR), $(addsuffix .o, $(SRCPRTF)))

# Default target
all: $(OBJDIR) $(NAME)
	@echo "Compilation of $(NAME) done!"

# Build target
$(NAME): $(OBJ)
	@echo "Archiving $(NAME)..."
	@ar -rcs $@ $(OBJ)

# Create object files directory
$(OBJDIR):
	@echo "Creating obj directories..."
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(FD_DIR)
	@mkdir -p $(OBJDIR)$(MEMDIR)
	@mkdir -p $(OBJDIR)$(CHRDIR)
	@mkdir -p $(OBJDIR)$(NUMDIR)
	@mkdir -p $(OBJDIR)$(STRDIR)
	@mkdir -p $(OBJDIR)$(LSTDIR)
	@mkdir -p $(OBJDIR)$(GNLDIR)
	@mkdir -p $(OBJDIR)$(PRTFDIR)

# Build object files
$(OBJDIR)%.o: $(SRCDIR)%.c | $(HEADSRC)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $^ -o $@

# Clean compiled files
clean:
	@echo "$(yb)Cleaning obj/ directory...$x"
	@rm -rf $(OBJDIR)

# Full clean
fclean: clean
	@echo "$(bb)Removing $(NAME)...$x"
	@rm -rf $(NAME)

# Rebuild from scratch
re: fclean
	@echo "$(rb)Reseting...$x"
	@echo ""
	@$(MAKE) --no-print-directory all

# Phony targets
.PHONY: all clean fclean re progress_bar

# $@ nom de la cible
# $< nom de la premiere dependance
# $ˆ liste des dependances
# $? liste des dependances mises a jour
# $* nom du fichier sans son extension
# $(wildcard *.c)
