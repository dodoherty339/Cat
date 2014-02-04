kitty: kitty.c
	gcc -Wall -ansi -pedantic kitty.c -o cat 
clean:
	rm -f kitty *.o
