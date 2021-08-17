capitulo_1 := src/capitulo_1
listing-1.1 := $(capitulo_1) #para que funcione make listing-1.1, ejecutando el make del capitulo 1
listing-1.2 := $(capitulo_1) #para que funcione make listing-1.2, ejecutando el make del capitulo 1
listing-1.3 := $(capitulo_1) #para que funcione make listing-1.3, ejecutando el make del capitulo 1
listing-2.1 := src/capitulo_2/2.1
listing-2.2 := src/capitulo_2/2.2
listing-2.3 := src/capitulo_2/2.3
listing-2.4 := src/capitulo_2/2.4
listing-2.5 := src/capitulo_2/2.5
listing-2.6 := src/capitulo_2/2.6
listing-2.7 := src/capitulo_2/2.7
listing-2.8 := src/capitulo_2/2.8
listing-2.9 := src/capitulo_2/2.9
listing-3.1 := src/capitulo_3/3.1
listing-3.2 := src/capitulo_3/3.2
listing-3.3 := src/capitulo_3/3.3
listing-3.4 := src/capitulo_3/3.4
listing-3.5 := src/capitulo_3/3.5
listing-3.6 := src/capitulo_3/3.6
listing-3.7 := src/capitulo_3/3.7
listing-4.1 := src/capitulo_4/4.1
listing-4.2 := src/capitulo_4/4.2
listing-4.3 := src/capitulo_4/4.3
listing-4.4 := src/capitulo_4/4.4
listing-4.5 := src/capitulo_4/4.5
listing-4.6 := src/capitulo_4/4.6
listing-4.7 := src/capitulo_4/4.7
listing-4.8 := src/capitulo_4/4.8
listing-4.10 := src/capitulo_4/4.10
listing-4.11 := src/capitulo_4/4.11
listing-4.12 := src/capitulo_4/4.12
listing-4.14 := src/capitulo_4/4.14
listing-5.3 := src/capitulo_5/5.3
listing-5.7 := src/capitulo_5/5.7
listing-5.11 := src/capitulo_5/5.11

listings := \
	$(capitulo_1) \
	$(listing-2.1) \
	$(listing-2.2) \
	$(listing-2.3) \
	$(listing-2.4) \
	$(listing-2.5) \
	$(listing-2.6) \
	$(listing-2.7) \
	$(listing-2.8) \
	$(listing-2.9) \
	$(listing-3.1) \
	$(listing-3.2) \
	$(listing-3.3) \
	$(listing-3.4) \
	$(listing-3.5) \
	$(listing-3.6) \
	$(listing-3.7) \
	$(listing-4.1) \
	$(listing-4.2) \
	$(listing-4.3) \
	$(listing-4.4) \
	$(listing-4.5) \
	$(listing-4.6) \
	$(listing-4.7) \
	$(listing-4.8) \
	$(listing-4.10) \
	$(listing-4.11) \
	$(listing-4.12) \
	$(listing-4.14) \
	$(listing-5.3) \
	$(listing-5.7) \
	$(listing-5.11)

.PHONY: all clean $(listings)

all: $(listings)

$(listings):
	$(MAKE) --directory=$@

%:
	$(if $($@), $(MAKE) --directory=$($@), $(error comando o listing "$@" no existe))

clean:
	rm -rf bin