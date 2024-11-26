#pragma once

#include "mstdi.h"



static kernel_args_t   kargs;
static MEMORY_MAP_INFO mmap;
static sgi_t           sgi;
static alloc_context_t alloc_context;

static xsdp_t*         xsdp;
static fadt_t*         fadt;
static madt_t*         madt;
static mcfg_t*         mcfg;

static mcfg_entry_t*   mcfg_entries;
static UINTN           mcfg_entry_count;


static CHAR16*tty_buffer;
static bool*tty_changed_buffer;
static UINTN tty_cursor_x=0;
static UINTN tty_cursor_y=0;
static UINTN tty_w;
static UINTN tty_h;

static bool keyboard_shift;
static bool keyboard_caps_lock;
static bool keyboard_alt_gr;

static idt_desc_t idt[256];
static idtr_t     idtr;
