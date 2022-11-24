all: libMyPeri.a ledtest.elf buttontest.elf

ledtest.elf: ledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc ledtest.c -lMyPeri -L. -o ledtest.elf

buttontest.elf: buttontest.o libMyPeri.a
	arm-linux-gnueabi-gcc buttontest.c -lMyPeri -L. -lpthread -o buttontest.elf

libMyPeri.a: button.o led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o

button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clean:
	rm *.o
	rm *.elf
	rm *.a
