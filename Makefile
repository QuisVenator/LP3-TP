all:
	cd src/capitulo_1 && make
	cd src/capitulo_2/2.1 && make
	cd src/capitulo_2/2.3 && make
	cd src/capitulo_2/2.7 && make
clean:
	rm -rf bin