# Varsayılan hedef
all: program run

# Programı derle ve çalıştırılabilir dosya oluştur
program: main.o Proje1.o
	gcc -g main.o Proje1.o -o program -Wall -Wextra

# main.c dosyasını derle ve main.o oluştur
main.o: main.c Proje1.h
	gcc -c main.c

# Proje1.c dosyasını derle ve Proje1.o oluştur
Proje1.o: Proje1.c Proje1.h
	gcc -c Proje1.c -o Proje1.o

# Programı çalıştır (argümanlarla)
run:
	./program calisanlar.txt birimler.txt

# Clean up object files and executable
clean:
	rm -f *.o program

.PHONY: all run clean