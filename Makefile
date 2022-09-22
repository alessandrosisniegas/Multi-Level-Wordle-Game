# Alessandro Sisniegas
# 04-21-22
create: wordle.o
	g++ wordle.o -o create

wordle.o: wordle.cpp
	g++ -c wordle.cpp -Wuninitialized -std=c++17

clean: 
	rm *.o	
	rm create

# target: dependencies
# command
# rm *.o (removes everything after the asterik in this case any file with .o)
# rm draw (removes the draw executable)