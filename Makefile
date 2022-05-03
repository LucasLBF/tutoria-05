all: bin

bin: main.c
	gcc $< -o $@ -pthread

.PHONY: clean run

clean:
	rm -f bin

run:
	./bin 
