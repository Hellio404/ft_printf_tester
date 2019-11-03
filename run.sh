rm -rf EXPECTED OUT TESTS deepthought
gcc -Wall -Wextra -Werror printf_main.c libftprintf.a
./a.out > OUT
gcc -Wall -Wextra -Werror main.c gnl.a
./a.out
rm -rf EXPECTED OUT TESTS ./a.out