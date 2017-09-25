all: tp_qrcode

tp_qrcode: imageBase.o tp_qrcode.o
	g++ -o tp_qrcode imageBase.o tp_qrcode.o

imageBase.o: ImageBase.cpp
	g++ -o imageBase.o -c ImageBase.cpp -W -Wall -ansi -pedantic

tp_qrcode.o: tp1_qrcode.cpp ImageBase.h
	g++ -o tp_qrcode.o -c tp1_qrcode.cpp -W -Wall -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf tp_qrcode
