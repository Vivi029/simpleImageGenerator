PROG = simpleImageGenerator
CC = g++
ODIR = obj
_OBJS = image.o bmpImage.o simpleImageGenerator.o pattern.o pointPattern.o rainbowPattern.o lineMessPattern.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(PROG): $(OBJS)
	$(CC) -o $(PROG).exe $(OBJS)

$(ODIR)/simpleImageGenerator.o:
	$(CC) -o $(ODIR)/simpleImageGenerator.o  -c src/simpleImageGenerator.cpp

$(ODIR)/image.o:
	$(CC) -o $(ODIR)/image.o -c src/image/image.cpp

$(ODIR)/bmpImage.o: $(ODIR)/image.o
	$(CC) -o $(ODIR)/bmpImage.o -c src/image/bmpImage.cpp

$(ODIR)/pattern.o: $(ODIR)/image.o
	$(CC) -o $(ODIR)/pattern.o -c src/patterns/pattern.cpp

$(ODIR)/pointPattern.o: $(ODIR)/pattern.o 
	$(CC) -o $(ODIR)/pointPattern.o -c src/patterns/pointPattern.cpp

$(ODIR)/rainbowPattern.o: $(ODIR)/pattern.o
	$(CC) -o $(ODIR)/rainbowPattern.o -c src/patterns/rainbowPattern.cpp

$(ODIR)/lineMessPattern.o: $(ODIR)/pattern.o
	$(CC) -o $(ODIR)/lineMessPattern.o -c src/patterns/lineMessPattern.cpp

makeClean: clean $(PROG)

clean:
	rm -rf ./obj/*.o
	rm -rf $(PROG).exe
	rm -rf $(PROG).exe.stackdump
	rm -rf testImage.bmp
