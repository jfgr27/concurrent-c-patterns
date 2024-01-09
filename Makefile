build: *.c
	gcc -w $(SCRIPT).c -o $(SCRIPT).out

run: *.c
	gcc -w $(SCRIPT).c -o $(SCRIPT).out && ./$(SCRIPT).out

.PHONY : clean 
clean : 
	rm -f *.o *.out
