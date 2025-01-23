CXX = g++
CXXFLAGS = -std=c++23 -Wall
LDFLAGS = -lncurses

TARGET = typing_game

SRCS = main.cpp getFile.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o ${TARGET} ${OBJS} ${LDFLAGS}

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

print:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"