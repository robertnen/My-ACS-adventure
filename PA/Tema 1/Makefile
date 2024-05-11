CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm
ARCHIVE := 323CC_NenciuGeorgeRobert_Tema1.zip

.PHONY: build clean

build: servere colorare compresie criptat oferta

run-p1:
	./servere
run-p2:
	./colorare
run-p3:
	./compresie
run-p4:
	./criptat
run-p5:
	./oferta

servere: servere.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
colorare: colorare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
compresie: compresie.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
criptat: criptat.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
oferta: oferta.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

clean:
	rm -f servere colorare compresie criptat oferta

pack:
	zip $(ARCHIVE) Makefile
	zip $(ARCHIVE) servere.cpp colorare.cpp compresie.cpp criptat.cpp oferta.cpp
	zip $(ARCHIVE) README.md