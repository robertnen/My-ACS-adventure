CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm
ARCHIVE := 323CC_NenciuGeorgeRobert_Tema2.zip

.PHONY: build clean

build: numarare trenuri drumuri scandal

run-p1:
	./numarare
run-p2:
	./trenuri
run-p3:
	./drumuri
run-p4:
	./scandal

numarare: numarare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
trenuri: trenuri.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
drumuri: drumuri.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
scandal: scandal.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

clean:
	rm -f numarare trenuri drumuri scandal

pack:
	zip $(ARCHIVE) Makefile
	zip $(ARCHIVE) numarare.cpp trenuri.cpp drumuri.cpp scandal.cpp
	zip $(ARCHIVE) README.md