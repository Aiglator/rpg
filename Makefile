#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 12:11:44 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/27 16:04:10 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = main.exe

CC = g++
CFLAGS = -Wall -Wextra -std=c++17
INC = -I./includes
LIB_PATH = -L./lib -lsfml-graphics -lsfml-network -lsfml-system -lsfml-audio -lsfml-window -lopengl32 -lwinmm -lgdi32

SRC = main.cpp src/file/background.cpp 
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIB_PATH) $(INC)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
