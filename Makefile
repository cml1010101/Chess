SRCS = $(wildcard src/*.cpp)
OBJS = ${SRCS:.cpp=.o}
all: ${OBJS}
	rm -f libchess.a
	ar rcs libchess.a ${OBJS}
	rm -f ${OBJS}
%.o: %.cpp
	g++ -c $< -o $@