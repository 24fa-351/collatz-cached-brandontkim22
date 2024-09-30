collatz: collatz.c
	gcc -o collatz collatz.c

cache: cache.c
	gcc -o cache cache.c

main: main.c
	gcc -o main main.c collatz.c cache.c

clean:
	rm main
	rm collatz
	rm cache