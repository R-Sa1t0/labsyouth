b() {
  if [ -z "$1" ]; then
    echo "Usage: b <filename.cpp>"
    return 1
  fi

  clang++-18 "$1" -g -Wall -Wextra && ./a.out
}

d() {
  if [ -z "$1" ]; then
    echo "Usage: d <filename.cpp>"
    return 1
  fi

  clang++-18 "$1" -g -Wall -Wextra -fsanitize=memory
  clang++-18 "$1" -g -Wall -Wextra -fsanitize=address
  valgrind --leak-check=full ./a.out
}

# source ./activate.sh