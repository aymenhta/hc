.PHONY: run
run:
	@./bin/hc file* *.c 

.PHONY: build
build:
	@gcc --std=c11 -Werror -Wall -Wconversion -O3 -o ./bin/hc ./hc.c

.PHONY: clean
clean:
	rm ./bin/hc
