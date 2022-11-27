all: libMyPeri.a ledtest.elf buttontest.elf fndtest.elf

fndtest.elf: fndtest.c libMyPeri.a
	arm-linux-gnueabi-gcc fndtest.c -lMyPeri -L. -o fndtest.elf

ledtest.elf: ledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc ledtest.c -lMyPeri -L. -o ledtest.elf

buttontest.elf: buttontest.c libMyPeri.a
	arm-linux-gnueabi-gcc buttontest.c -lMyPeri -L. -lpthread -o buttontest.elf

libMyPeri.a: button.o led.o fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o fnd.o

fnd.o : fnd.h fnddrv.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clean:
	rm *.o
	rm *.elf
	rm *.a
