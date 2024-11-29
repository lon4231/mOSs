cc := x86_64-w64-mingw32-g++
ld := x86_64-w64-mingw32-ld
clear_cmd:=clear 

bcflags := -std=c++20 -mno-red-zone -O3 -s 
bldflags := -nostdlib -Wl,--subsystem,10 -e emain -w -ffreestanding

kcflags := -std=c++20 -w -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -O3 -Os -s 

qemu := qemu-system-x86_64

all:
	$(clear_cmd)
	$(cc) boot/boot.cpp tools/printf.o $(bcflags) $(bldflags) -Imstd -o BOOTX64.EFI

	$(cc) kernel/kernel.cpp -c -nostdlib -ffreestanding -fPIE -o kernel.o -Imstd -Ikernel $(kcflags)
	$(ld) -nostdlib -T tools/kernel.ld --image-base=0 -pie -o kernel.obj kernel.o
	objcopy -O binary kernel.obj kernel.bin
	cp tools/config.bc ./ 
	cp tools\unifont.psf ./ 
	
	./tools/make_disk -i moss.iso -ae /EFI/BOOT/ kernel.bin /EFI/BOOT/ config.bc /EFI/BOOT/ unifont.psf
	rm -rf kernel.bin kernel.o kernel.obj BOOTX64.EFI DSKIMG.INF config.bc
	$(qemu) -drive format=raw,unit=0,file=moss.iso -bios tools/bios64.bin -m 2G -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime

test:
	$(qemu) -drive format=raw,unit=0,file=moss.iso -bios tools/bios64.bin -m 2G -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime
