all:
	cd src/capitulo_1 && make
	cd src/capitulo_2/2.1 && make
	cd src/capitulo_2/2.2 && make
	cd src/capitulo_2/2.3 && make
	cd src/capitulo_2/2.6 && make
	cd src/capitulo_2/2.7 && make

	cd src/capitulo_3/3.1 && make
	cd src/capitulo_3/3.5 && make

	cd src/capitulo_4/4.2 && make
clean:
	rm -rf bin