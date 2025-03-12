.PHONY: all boot_fstage kernel_fstage build_wgpt build_disk qemu_test
.NOTPARALLEL: all boot_fstage kernel_fstage build_wgpt build_disk qemu_test

gcc:=gcc
cc :=g++
objcopy:=objcopy
ld :=ld
cls:=cls
rm :=del

wgpt		        :=tools/wgpt.exe


wgpt_src            :=tools/wgpt/wgpt.c
wgpt_cflags         :=-O3 -s

qemu		        :=qemu-system-x86_64
qemu_flags          :=-bios tools/bios64.bin -m 4G -vga std -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime -net none

boot_src	        :=$(wildcard boot/*.cpp) printf/printf.cpp $(wildcard std/*.cpp) $(wildcard arch/*.cpp)
boot_inc            :=-Iinc -Iprintf -Iboot
boot_cflags         :=-w -O3 -s -mno-red-zone -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -std=c++20
boot_ldflags        :=-nostdlib -Wl,--subsystem,10 -e emain

boot_targets  	    :=$(patsubst %.cpp,%.boot,$(boot_src))
boot_real_targets   :=$(notdir $(patsubst %.cpp,%.o,$(boot_src)))

kernel_src     	    :=$(wildcard kernel/*.cpp) $(wildcard arch/*.cpp)
kernel_inc	   	    :=-Iinc -Iprintf
kernel_cflags  	    :=-w -O3 -s -mno-red-zone -ffreestanding -nostdlib -fno-stack-protector -fno-exceptions -fno-rtti -fPIE -std=c++20
kernel_ldflags 	    :=-e kmain -nostdlib -pie

kernel_targets 		:=$(patsubst %.cpp,%.krn,$(kernel_src))
kernel_real_targets :=$(notdir $(patsubst %.cpp,%.o,$(kernel_src)))


all: $(boot_targets) boot_fstage $(kernel_targets) kernel_fstage build_disk qemu_test

build_disk:
	$(wgpt) -i moss.img -ae /EFI/BOOT/ kernel.bin 
	$(rm) BOOTX64.EFI FILE.TXT kernel.bin

boot_fstage:
	$(cc) $(boot_real_targets) -o BOOTX64.EFI $(boot_cflags) $(boot_ldflags) $(boot_inc)
	$(rm) $(boot_real_targets)

kernel_fstage:
	$(ld) $(kernel_ldflags) -Tkernel/kernel.ld --image-base=0 -o kernel.obj $(kernel_real_targets)
	$(objcopy) -O binary kernel.obj kernel.bin
	$(rm) $(kernel_real_targets) kernel.obj

build_wgpt:
	$(gcc) -o tools/wgpt $(wgpt_src) $(wgpt_cflags)

qemu_test:
	$(qemu) -drive format=raw,file=moss.img $(qemu_flags)
	$(cls)


%.krn : %.cpp
	$(cc) $< -o $(notdir $*.o) -c $(kernel_cflags) $(kernel_ldflags) $(kernel_inc)

%.boot : %.cpp
	$(cc) $< -o $(notdir $*.o) -c $(boot_cflags) $(boot_ldflags) $(boot_inc)
