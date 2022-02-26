CC := gcc
scriptName := starAlign

$(scriptName): main.o cstarAlign.o PSA_fmindex.o PSA_kband.o FMindex.o getRank.o BWT.o fasta.o
	$(CC) -o $@ $^
	@echo COMPILE OVER!

fasta.o: fasta.c fasta.h
	$(CC) -c $<

BWT.o: BWT.c bwt.h
	$(CC) -c $<

getRank.o: getRank.c getRank.h
	$(CC) -c $<

FMindex.o: FMindex.c FMindex.h
	$(CC) -c $<

PSA_kband.o: PSA_kband.c PSA_kband.h
	$(CC) -c $<

PSA_fmindex.o: PSA_fmindex.c PSA_fmindex.h
	$(CC) -c $<

cstarAlign.o: cstarAlign.c cstarAlign.h
	$(CC) -c $<

main.o: main.c
	$(CC) -c $<


.PHONY: clean
clean:
	rm *.o
	rm $(scriptName)