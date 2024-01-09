build: *.c
	gcc -Wall $(SCRIPT).c -o $(SCRIPT).out

run: *.c
	gcc -Wall $(SCRIPT).c -o $(SCRIPT).out && ./$(SCRIPT).out

.PHONY : clean 
clean : 
	rm -f *.o *.out
