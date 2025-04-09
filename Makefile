CC = g++
LDFLAGS = -lglfw -lGL -lGLU -lm
CFLAGS = -Wall -Werror

CFILES = $(wildcard *.cpp)
OBJFILES = $(patsubst %.cpp, %.o, $(CFILES))

prog : $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o:%.cpp
	$(CC)  $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean :
	rm -rf *.o prog
