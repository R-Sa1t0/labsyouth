souce_files = main.c liblist.c

all: gcc exec

full: gcc clang vexec

gcc:
	gcc -g -Wall -Wextra $(souce_files)

clang:
	clang -g -Wall -Wextra -fsanitize=memory $(souce_files)

vexec:
	valgrind --leak-check=full ./a.out

exec:
	./a.out