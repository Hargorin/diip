CC = g++
RM = rm -rf

CFLAGS = -Wall

SRCS = main.cpp
PROG = image2file

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

all: $(PROG)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	$(RM) $(PROG)