capitulo_1 := src/capitulo_1
listing-1.1 := $(capitulo_1) #para que funcione make listing-1.1, ejecutando el make del capitulo 1
listing-1.2 := $(capitulo_1) #para que funcione make listing-1.2, ejecutando el make del capitulo 1
listing-1.3 := $(capitulo_1) #para que funcione make listing-1.3, ejecutando el make del capitulo 1
listing-2.1 := src/capitulo_2/2.1
listing-2.2 := src/capitulo_2/2.2
listing-2.3 := src/capitulo_2/2.3
listing-2.5 := src/capitulo_2/2.5
listing-2.6 := src/capitulo_2/2.6
listing-2.7 := src/capitulo_2/2.7
listing-3.1 := src/capitulo_3/3.1
listing-3.2 := src/capitulo_3/3.2
listing-3.5 := src/capitulo_3/3.5
listing-4.2 := src/capitulo_4/4.2
listing-4.6 := src/capitulo_4/4.6

listings := \
	$(capitulo_1) \
	$(listing-2.1) \
	$(listing-2.2) \
	$(listing-2.3) \
	$(listing-2.5) \
	$(listing-2.6) \
	$(listing-2.7) \
	$(listing-3.1) \
	$(listing-3.5) \
	$(listing-4.2) \
	$(listing-4.6)

.PHONY: all clean $(listings)

all: $(listings)

$(listings):
	$(MAKE) --directory=$@

%:
	$(if $($@), $(MAKE) --directory=$($@), $(error comando o listing "$@" no existe))

clean:
	rm -rf bin