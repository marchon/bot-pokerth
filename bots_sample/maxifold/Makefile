# Declaration of variables
CC = g++
CFLAGS = -w -O0 -g -Wall -Wextra -Werror -fPIC -I../include
LIBS=-lefence

# File names
DLL = libmaxifold.so
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(DLL): $(OBJECTS) 
	$(CC) $(OBJECTS) -L $(LIBS) -shared -fPIC  -Wl,-soname,$@.1 -o $@

# To obtain object files
%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(DLL) $(OBJECTS)
