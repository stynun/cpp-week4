FLAGS = -Werror -std=c++11

SRCS = main.cpp util.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main.exe

$(TARGET): $(OBJS)
	g++ -o $@ $^

%.o: %.cpp
	g++ ${FLAGS} -c $<

clean:
	rm -f $(OBJS) $(TARGET)