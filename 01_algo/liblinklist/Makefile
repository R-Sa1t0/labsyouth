CC = gcc
MAIN = linklist_test.c
LIBS = liblinklist.c
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS_1 = -g -Wall -Wextra -fsanitize=memory
DEBUGFLAGS_2 = -g -Wall -Wextra -fsanitize=address

all: format gcc clang exec

test: format debug vexec

format:
	@for file in *.c *.h; do \
		if [ -f "$$file" ]; then \
			clang-format -i "$$file"; \
		fi; \
	done

gcc:
	gcc $(CFLAGS) $(MAIN) $(LIBS)

clang:
	clang $(CFLAGS) $(MAIN) $(LIBS)

debug: 
	clang $(DEBUGFLAGS_1) $(MAIN) $(LIBS)
	clang $(DEBUGFLAGS_2) $(MAIN) $(LIBS)

vexec:
	valgrind --leak-check=full ./a.out

exec:
	./a.out