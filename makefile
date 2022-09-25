CFLAGS = -std=c++14 -Wall -g

huffman:	main.o frequencynode.o encoding.o tree.o
	g++ main.o frequencynode.o encoding.o tree.o -o huffman $(CFLAGS)

main.o:	frequencynode.h encoding.h tree.h main.cpp
	g++ -c main.cpp $(CFLAGS)

frequencynode.o: frequencynode.cpp frequencynode.h
	g++ -c frequencynode.cpp $(CFLAGS)

encoding.o: encoding.cpp encoding.h
	g++ -c encoding.cpp $(CFLAGS)

tree.o: tree.cpp tree.h
	g++ -c tree.cpp $(CFLAGS)

clean:
	rm -f *.o huffman
