listing-2.7_2.8: test.c app.c
	gcc -c test.c
	ar cr libtest.a test.o
	gcc -c -w app.c 

	# Crea directorio si no existe y asigna el ejecutable
	@mkdir -p ../../../bin/capitulo_2/2.7_2.8/

	gcc -o ../../../bin/capitulo_2/2.7_2.8/app app.o -L. -ltest  

	# Para borrar los archivos .o 
	rm *.o
	

