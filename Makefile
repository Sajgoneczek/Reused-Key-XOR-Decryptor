# Compiler to use
CC = gcc

# Compiler flags:
# -Wall: enables all compiler's warning messages
# -Wextra: enables some extra warning messages
# -std=c99: use the C99 standard
CFLAGS = -Wall -Wextra -std=c99

# The name of the executable file to produce
TARGET = MTP_attack

# The 'all' target is the default when you run 'make'
all: $(TARGET)

# Rule to link the program. 
# It depends on MTP_attack.c
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Rule to remove the compiled binary (cleanup)
clean:
	rm -f $(TARGET)
