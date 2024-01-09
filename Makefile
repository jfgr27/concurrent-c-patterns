build: *.c
	gcc -Wall $(SCRIPT).c -o $(SCRIPT).out


run: *.c
	make build $(SCRIPT) && ./$(SCRIPT).out

.PHONY : clean 
clean : 
	rm -f *.o *.out
