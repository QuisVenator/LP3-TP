listing-2.7: test.c app.c
	gcc -c test.c

	# Para crear la libreria 
	ar cr libtest.a test.o
	gcc -c app.c 

	# Crea directorio si no existe y asigna el ejecutable
	@mkdir -p ../../../bin/capitulo_2/2.7/

	gcc -o ../../../bin/capitulo_2/2.7/app app.o -L. -ltest

	# Para borrar los archivos .o / 
	rm *.o
	# Para borrar la libreria 
	rm *.a