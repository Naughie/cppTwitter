CXX = g++
CXXFLAGS = -std=c++11 -fast -Wall
LDFLAGS = -L/usr/local/lib -L/usr/lib
LDLIBS = -lssl -lcurl -lcrypto
INCLUDE = -I./include -I/usr/local/include -I/usr/include
TARGET = ./bin/main
SRCDIR = ./src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = ./obj
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(TARGET)
