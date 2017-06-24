flags=-Wno-deprecated -g -ggdb
comp=g++
prog=SA

#problema
config=instancias/ejemplo

comp:$(prog)

exe:$(prog)
	./$(prog) $(config)

$(prog): main.o SimulatedAnnealing.o Bep.o
	$(comp) main.o SimulatedAnnealing.o Bep.o -o $(prog) $(flags)

main.o: main.cpp SimulatedAnnealing.h
	$(comp) -c main.cpp $(flags)

Bep.o: Bep.cpp Bep.h includes.h
	$(comp) -c Bep.cpp $(flags)

SimulatedAnnealing.o: SimulatedAnnealing.cpp SimulatedAnnealing.h
	$(comp) -c SimulatedAnnealing.cpp $(flags)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(prog)
	rm -f core*
