all: libMyPeri.a ledtest.elf buttontest.elf fndtest.elf buzzertest.elf textlcdtest.elf colorledtest.elf temperaturetest.elf

temperaturetest.elf: temperaturetest.c libMyPeri.a
	arm-linux-gnueabi-gcc temperaturetest.c -lMyPeri -L. -o temperaturetest.elf

colorledtest.elf: colorledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc colorledtest.c -lMyPeri -L. -o colorledtest.elf

textlcdtest.elf: textlcdtest.c libMyPeri.a
	arm-linux-gnueabi-gcc textlcdtest.c -lMyPeri -L. -o textlcdtest.elf

buzzertest.elf: buzzertest.c libMyPeri.a
	arm-linux-gnueabi-gcc buzzertest.c -lMyPeri -L. -o buzzertest.elf

fndtest.elf: fndtest.c libMyPeri.a
	arm-linux-gnueabi-gcc fndtest.c -lMyPeri -L. -o fndtest.elf

ledtest.elf: ledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc ledtest.c -lMyPeri -L. -o ledtest.elf

buttontest.elf: buttontest.c libMyPeri.a
	arm-linux-gnueabi-gcc buttontest.c -lMyPeri -L. -lpthread -o buttontest.elf

libMyPeri.a: button.o led.o fnd.o buzzer.o textlcd.o colorled.o temperature.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o fnd.o buzzer.o textlcd.o colorled.o temperature.o

temperature.o: temperature.h temperature.c
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o

colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o

textlcd.o: textlcd.h textlcd.c
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

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
