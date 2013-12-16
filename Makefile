all: 
	gcc pka_Strasburger_Okolovskis_Meister.c -o pka 
tests: test
test: 
	gcc -g -DTESTING=1 pka_Strasburger_Okolovskis_Meister.c test.c -o tests
	./tests
clean:
	rm *.o
	rm tests
	rm pka
