cc := x86_64-w64-mingw32-g++
ld := ld
clear_cmd:=cls 

includes:= -Imstd -Iprintf

bcflags := -std=c++20 -mno-red-zone -O3 -s -fno-stack-protector -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2
bldflags := -nostdlib -Wl,--subsystem,10 -e emain -w -ffreestanding

kcflags := -std=c++20 -w -ffreestanding -fno-pic -mcmodel=large -m64 -fno-stack-protector -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-avx -O3 -Os -s 

qemu := qemu-system-x86_64
qemu_flags:=-m 2G -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime


all:
	$(cc) printf/printf.cpp $(bcflags) $(bldflags) $(includes) -c -o printf.o

	$(clear_cmd)
	$(cc) boot/boot.cpp printf.o $(bcflags) $(bldflags) $(includes) -o BOOTX64.EFI

	$(cc) kernel/kernel.cpp -c -nostdlib -ffreestanding -fPIE -o kernel.o $(includes) $(kcflags)
	$(ld) -nostdlib -e kmain -T tools/kernel.ld --image-base=0 -pie kernel.o -o kernel.obj
	objcopy -O binary kernel.obj kernel.bin

	copy tools\config.bc 
	./tools/disk.exe -i moss.iso -ae /EFI/BOOT/ kernel.bin /EFI/BOOT/ config.bc
	del kernel.bin kernel.o kernel.obj BOOTX64.EFI DSKIMG.INF config.bc
	$(qemu) -drive format=raw,unit=0,file=moss.iso -bios tools/bios64.bin $(qemu_flags)

test:
	$(qemu) -drive format=raw,unit=0,file=moss.iso -bios tools/bios64.bin $(qemu_flags)