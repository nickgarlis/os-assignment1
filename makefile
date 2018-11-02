all: compile run clean

compile: 
	@gcc -o exercise2 read_write.c next_i.c

run: 
	@./exercise2 $(start) $(buff_size)

clean: 
	@rm exercise2