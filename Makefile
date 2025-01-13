cc 		    := x86_64-w64-mingw32-g++
ld 		    := ld
rm		    := del
objcopy		:= objcopy
clear       := 
disk_builder:= ./tools/disk.exe

includes    := -Ishared -Iinc_arch -Iinc_arch/x86_64 -Iprintf

boot_cflags	:=-O3 -s 
boot_ldflags:=-nostdlib -Wl,--subsystem,10 -e emain -w -ffreestanding

vm 		  := qemu-system-x86_64
vm_flags  :=-m 4G -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime
vm_file   :=moss.iso
vm_bios   :=tools/bios64.bin

driver_cflags := -O3 -s -std=c++20 -w -ffreestanding -fno-stack-protector -mno-red-zone 
driver_ldflags:= -nostdlib -e dmain -T tools/driver.ld --image-base=0 -pie 

kernel_cflags :=-std=c++20 -w -ffreestanding -fno-stack-protector -mno-red-zone 
kernel_ldflags:=-nostdlib -e kmain -T tools/kernel.ld --image-base=0 -pie

driver_src:=$(wildcard drivers/*/main.cpp)
driver_obj := $(patsubst drivers/%/main.cpp, %.o, $(driver_src))

all: bootloader kern $(driver_obj) disk clean test

bootloader:
	$(clear)
	$(cc) boot/main.cpp printf/printf.cpp -o BOOTX64.EFI $(includes) -Iprintf $(boot_cflags) $(boot_ldflags)

kern:
	$(clear)
	$(cc) kernel/main.cpp $(kernel_cflags) $(includes) -c -o kernel.o
	$(ld) $(kernel_ldflags) kernel.o -o kernel.obj
	$(objcopy) -O binary kernel.obj kernel.krn

disk:
	$(clear)
	$(disk_builder) -i moss.iso -ae $(addprefix /DRIVER/ ,$(wildcard *.drv)) /EFI/BOOT/ kernel.krn

test:
	$(clear)
	$(vm) -drive format=raw,unit=0,file=$(vm_file) -bios $(vm_bios) $(vm_flags)

clean:
	$(clear)
	$(rm) BOOTX64.EFI DSKIMG.INF FILE.TXT kernel.krn $(wildcard *.drv) $(wildcard *.o) $(wildcard *.obj)

%.o %.obj %.drv: drivers/%/main.cpp
	$(clear)
	$(cc) $< $(driver_cflags) $(includes) -c -o $*.o
	$(ld) $(driver_ldflags) $*.o -o $*.obj
	$(objcopy) -O binary $*.obj $*.drv
