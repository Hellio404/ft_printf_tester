rm -rf EXPECTED OUT TESTS deepthought
gcc -Wall -Wextra -Werror printf_main.c libftprintf.a
valgrind --leak-check=full ./a.out > valgrind_out 2>&1
./a.out > OUT
gcc -Wall -Wextra -Werror main.c gnl.a
./a.out
rm -rf EXPECTED OUT TESTS