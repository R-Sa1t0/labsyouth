CXX = clang++-18
MAIN = ringbuf.cpp
CFLAGS = -g -Wall -Wextra
DEBUGFLAGS_1 = -g -Wall -Wextra -fsanitize=memory
DEBUGFLAGS_2 = -g -Wall -Wextra -fsanitize=address

all: format build exec
test: override MAIN = ringbuf_test.cpp
test: format build exec

debug: clean format sanitize build vexec

format:
	@for file in *.c *.h *.cpp *.hpp; do \
		if [ -f "$$file" ]; then \
			clang-format -i "$$file"; \
		fi; \
	done

build:
	$(CXX) $(CFLAGS) $(MAIN)

sanitize: 
	$(CXX) $(DEBUGFLAGS_1) $(MAIN)
	$(CXX) $(DEBUGFLAGS_2) $(MAIN)

vexec:
	valgrind --leak-check=full ./a.out

exec:
	./a.out

clean:
	rm -f a.out