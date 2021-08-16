capitulo_1 := src/capitulo_1
listing-2.1 := src/capitulo_2/2.1
listing-2.2 := src/capitulo_2/2.2
listing-2.3 := src/capitulo_2/2.3
listing-2.6 := src/capitulo_2/2.6
listing-2.7 := src/capitulo_2/2.7
listing-3.1 := src/capitulo_3/3.1
listing-3.5 := src/capitulo_3/3.5
listing-4.2 := src/capitulo_4/4.2
listing-4.6 := src/capitulo_4/4.6

listings := $(capitulo_1) $(listing-2.1) $(listing-2.2) $(listing-2.3) $(listing-2.6) $(listing-2.7) $(listing-3.1) $(listing-3.5) $(listing-4.2) $(listing-4.6)

.PHONY: all clean $(listings)

all: $(listings)

$(listings):
	$(MAKE) --directory=$@

clean:
	rm -rf bin