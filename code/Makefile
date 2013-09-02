CFLAGS=-Wall -g `pkg-config --cflags --libs gstreamer-1.0`

all: driver

driver: cue.o media.o menu.o

clean:
	rm -f driver *.o


