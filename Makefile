# Static library name
NAME = build/minitalk.a

# Executable names
CLIENT = client
SERVER = server

# Compiler and rules
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 

# Directories
SRC_DIR = source
OBJ_DIR = build/obj
LIBFT_DIR = source/libft

# Client and Server sources
SRC_FILES = $(SRC_DIR)/utils.c
CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c

SRC_OBJ = $(OBJ_DIR)/utils.o
CLIENT_OBJ = $(OBJ_DIR)/client.o
SERVER_OBJ = $(OBJ_DIR)/server.o

# # Sub-sources
LIBFT_LIB = $(LIBFT_DIR)/build/libft.a

# Default rule
all: $(NAME) $(CLIENT) $(SERVER)

$(NAME):  $(LIBFT_LIB) $(SRC_OBJ)
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;32mCREATING STATIC LIBRARY $@\033[0m"
	ar rcs $@ $(SRC_OBJ)
	ranlib $@
	@echo "\033[1;36mCOMPILING AND GENERATE THE EXECUTABLE...\033[0m"
	
# Rule to compile .c files into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;33mCOMPILING $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

# Rules for Client and Server
$(CLIENT): $(CLIENT_OBJ) $(NAME)
	@echo "\033[1;32mCOMPILING CLIENT EXECUTABLE...\033[0m"
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(NAME) $(LIBFT_LIB) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(NAME)
	@echo "\033[1;32mCOMPILING SERVER EXECUTABLE...\033[0m"
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(NAME) $(LIBFT_LIB) -o $(SERVER)

# Rule to compile client.c and server.c into object files
$(CLIENT_OBJ): $(CLIENT_SRC)
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;33mCOMPILING CLIENT SOURCE...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJ): $(SERVER_SRC)
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;33mCOMPILING SERVER SOURCE...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the libft library
$(LIBFT_LIB):
	@echo "\033[1;35mCOMPILING LIBFT LIBRARY...\033[0m"
	$(MAKE) -C $(LIBFT_DIR)

# Rule to clean object files and executables
clean:
		@echo "\033[1;31mCLEANING OBJECT FILES AND EXECUTABLES...\033[0m" 
		rm -rf $(OBJ_DIR) $(CLIENT) $(SERVER)
		$(MAKE) -C $(LIBFT_DIR) clean
		@echo "\033[1;32mCLEANING DONE.\033[0m"

# Rule for full clean
fclean:	clean
		@echo "\033[1;31mDELETING FILES $(NAME)...\033[0m"
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean		
		@echo "\033[1;32mALL CLEANED UP.\033[0m" 

# Rule to rebuild the project
re:		fclean all
		@echo "\033[1;34mPROJECT REBUILD.\033[0m"		

# Phony rules
.PHONY:	all clean fclean re