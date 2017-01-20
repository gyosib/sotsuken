LIBS = `pkg-config --libs opencv`
CFLAGS = `pkg-config --cflags opencv`

E_cruz: o_cruz.o
	g++ -o $@ $(LIBS) o_cruz.o

o_cruz.o: cruz.cpp
	g++ -c $(CFLAGS) cruz.cpp -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
