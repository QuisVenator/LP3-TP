listing-2.8: app.c test.c
	gcc -c test.c
	gcc -c app.c

	#se crea una librería de test.c para seguir lo que se hizo en el libro en este listing
	ar cr libtest.a test.o

	@mkdir -p ../../../bin/capitulo_2/2.8
	gcc -o ../../../bin/capitulo_2/2.8/app app.o -L. -ltest
	rm *.o
	rm *.a