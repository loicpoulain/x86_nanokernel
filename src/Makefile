#ToDo: clean/split this makefile

all: image.bin

image.bin: bootloader/bootloader.bin kernel/kernel.bin
	dd status=noxfer conv=notrunc bs=512 seek=0 if=bootloader/bootloader.bin of=image.bin
	dd status=noxfer conv=notrunc bs=512 seek=1 if=kernel/kernel.bin of=image.bin

bootloader/bootloader.bin: bootloader/bootloader.asm
	nasm -f bin -o bootloader/bootloader.bin bootloader/bootloader.asm

kernel/kernel.bin: kernel/kernel.c
	gcc -m32 -ffreestanding -c -o kernel/kernel.o kernel/kernel.c
	nasm -f coff -o kernel/kernel_asm.o kernel/kernel.asm
	ld -melf_i386 -Ttext 0x100000 --oformat binary -o kernel/kernel.bin kernel/kernel.o kernel/kernel_asm.o

clean:
	rm -f -R *.flp
	rm -f *.bin
	rm -f bootloader/*.bin
	rm -f kernel/*.bin
	rm -f kernel/*.o
