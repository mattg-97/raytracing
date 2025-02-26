CC = clang
CFLAGS = -g -Wall -Wextra -Wdouble-promotion -fsanitize=undefined -std=c99
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/raytracing

# Find all .c files recursively
SRCS = $(shell find $(SRCDIR) -type f -name "*.c")
# Generate corresponding .o file names
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
# Generate include directories
INCLUDES = -I$(SRCDIR) $(shell find $(SRCDIR) -type d -exec echo -I{} \;) -I/Library/Frameworks/SDL2.framework/Headers -I/opt/homebrew/Cellar/raylib/5.5/include

.PHONY: all clean run bear

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -F/Library/Frameworks -framework SDL2 -Wl,-rpath,/Library/Frameworks -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)