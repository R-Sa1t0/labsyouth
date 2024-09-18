CC = clang-18
MAIN = libdeque_test.c
LIBS = libdeque.c ../libdoublylinklist/libdoublylinklist.c
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS_1 = -g -Wall -Wextra -fsanitize=memory
DEBUGFLAGS_2 = -g -Wall -Wextra -fsanitize=address

all: format build exec

debug: format sanitize build vexec

format:
	@for file in *.c *.h; do \
		if [ -f "$$file" ]; then \
			clang-format -i "$$file"; \
		fi; \
	done

build:
	$(CC) $(CFLAGS) $(MAIN) $(LIBS)

sanitize: 
	$(CC) $(DEBUGFLAGS_1) $(MAIN) $(LIBS)
	$(CC) $(DEBUGFLAGS_2) $(MAIN) $(LIBS)

vexec:
	valgrind --leak-check=full ./a.out

exec:
	./a.out