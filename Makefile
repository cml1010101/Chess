SRCS = $(wildcard src/*.cpp)
OBJS = ${SRCS:.cpp=.o}
all: ${OBJS}
	rm -f libchess.a
	ar rcs libchess.a ${OBJS}
	rm -f ${OBJS}
deploy: all
	rm -r /usr/include/chess
	cp -r include /usr/include/chess
	cp libchess.a /usr/lib
%.o: %.cpp
	g++ -c $< -o $@ -g -I/usr/include/torch/csrc/api/include -std=c++17