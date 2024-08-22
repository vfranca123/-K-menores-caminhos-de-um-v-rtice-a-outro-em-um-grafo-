all: obj/tp2.o obj/main.o 
	gcc obj/tp1.o  obj/main.o -o tp1
	

obj/tp1.o: desenvolvimento_funcoes/func.c
	gcc desenvolvimento_funcoes/func.c -c
	mv tp2.o obj/

obj/main.o:main.c 
gcc main.c -c main
mv main.o obj

apagar:
	rm obj/* tp1