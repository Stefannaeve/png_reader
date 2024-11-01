TARGET = main
INCLDIR = ./include
SRCDIR = src
BINDIR = bin
LIBS = lib/SNLogger.a
CC = gcc
CFLAGS = -O0 -g -lncurses
CFLAGS += -I$(INCLDIR)
RM = rm -f

OBJDIR = obj

# PATHS
_DEPS = main.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

_OBJS = main.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# RULES
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

run:
	make
	./$(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o *~core $(INCLDIR)/*~