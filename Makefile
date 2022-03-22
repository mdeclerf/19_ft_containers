CXX		= clang++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -D STL=${STL}

SRCS	= main.cpp

OBJS	= ${SRCS:.cpp=.o}

NAME		= exec

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CXX) $(CXXFLAGS_FT) -o $(NAME) $(OBJS)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re

# STL=1 ------------------> STL version
# STL=0 ------------------> FT version
