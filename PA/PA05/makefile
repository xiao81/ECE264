pa05: pa05.o answer_pa05.o
	gcc -Wall -Werror -Wshadow -g answer_pa05.o pa05.o -o pa05
answer_pa05.o: list_tree.h answer_pa05.c
	gcc -Wall -Werror -Wshadow -g -c answer_pa05.c
pa05.o: list_tree.h pa05.c
	gcc -Wall -Werror -Wshadow -g -c pa05.c
clean:
	rm -f*.o pa05 pa05.o answer_pa05.o
