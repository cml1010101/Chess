SRCS = $(wildcard src/*.cpp)
OBJS = ${SRCS:.cpp=.o}
all: libchess.a

deploy: libchess.a libchess_1.0-1_amd64.deb

libchess.a: ${OBJS}
	rm -f libchess.a
	ar rcs libchess.a ${OBJS}
	rm -f ${OBJS}
%.o: %.cpp
	g++ -c $< -o $@ -g -I/usr/include/torch/csrc/api/include -std=c++17
libchess_1.0-1_amd64.deb: libchess_1.0-1_amd64 libchess_1.0-1_amd64/usr/include libchess_1.0-1_amd64/usr/lib libchess_1.0-1_amd64/DEBIAN
	cp control libchess_1.0-1_amd64/DEBIAN/control
	cp libchess.a libchess_1.0-1_amd64/usr/lib/
	cp -r include libchess_1.0-1_amd64/usr/include/
	dpkg-deb --build --root-owner-group libchess_1.0-1_amd64
	rm -r libchess_1.0-1_amd64
libchess_1.0-1_amd64:
	mkdir libchess_1.0-1_amd64
libchess_1.0-1_amd64/usr/include:
	mkdir -p libchess_1.0-1_amd64/usr/include
libchess_1.0-1_amd64/usr/lib:
	mkdir -p libchess_1.0-1_amd64/usr/lib
libchess_1.0-1_amd64/DEBIAN:
	mkdir -p libchess_1.0-1_amd64/DEBIAN