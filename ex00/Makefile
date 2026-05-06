# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/06 16:22:38 by mcaro-ro          #+#    #+#              #
#    Updated: 2026/05/06 18:05:19 by mcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= btc

INCDIR		= inc
SRCDIR		= src

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I$(INCDIR)

SRCS		=	$(SRCDIR)/main.cpp				\
				$(SRCDIR)/BitcoinExchange.cpp	\

BUILDDIR	= build
OBJS		= $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Colors
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

clean:
	@echo "$(YELLOW)$(NAME): Cleaning object files...$(RESET)"
	@rm -rf $(BUILDDIR)
	@echo "$(GREEN)$(NAME): All objects have been cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)$(NAME): Cleaning all files...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME): All files have been cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
