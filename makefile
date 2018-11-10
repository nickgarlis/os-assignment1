all: compile run clean

compile: 
	@gcc -ggdb -Wall -o exercise2 read_write.c next_i.c

run: 
	@-./exercise2 $(offset) $(buff_size)

clean: 
	@rm exercise2