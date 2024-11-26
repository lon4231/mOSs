#pragma once

#include "mstdi.h"
#include "globals.h"
#include "tty/tty.h"

#define EXTENDED_KEY 0xE0

enum SCANCODES
{
ESC_SCANCODE  =1,
DEL_SCANCODE  =2,
UP_SCANCODE   =3,
DOWN_SCANCODE =4,
LEFT_SCANCODE =5,
RIGHT_SCANCODE=6,
BACKSPACE_SCANCODE=7,
TAB_SCANCODE  =8,
ENTER_SCANCODE=9,
CTRL_SCANCODE =10,
};

enum KEY_FLAGS
{
TRIGGER_KEY=0x1,
SHIFT_KEY=0x2,
CAPS_LOCK_KEY=0x4,
};

static const keymap_entry_t keymap[128]=
{
{{0x00              ,0x00 },{0x00              ,0x00 },{0x00              ,0x00 },0},
{{ESC_SCANCODE      ,0x00 },{ESC_SCANCODE      ,0x00 },{ESC_SCANCODE      ,0x00 },TRIGGER_KEY},
{{0x00              ,u'1' },{0x00              ,u'!' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'2' },{0x00              ,u'"' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'3' },{0x00              ,u'#' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'4' },{0x00              ,u'$' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'5' },{0x00              ,u'%' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'6' },{0x00              ,u'&' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'7' },{0x00              ,u'/' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'8' },{0x00              ,u'(' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'9' },{0x00              ,u')' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'0' },{0x00              ,u'=' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'\''},{0x00              ,u'?' },{0x00              ,u'\\'},TRIGGER_KEY},
{{0x00              ,u'¿' },{0x00              ,u'¡' },{0x00              ,0x00 },TRIGGER_KEY},
{{BACKSPACE_SCANCODE,0x00 },{BACKSPACE_SCANCODE,0x00 },{BACKSPACE_SCANCODE,0x00 },TRIGGER_KEY},
{{TAB_SCANCODE      ,0x00 },{TAB_SCANCODE      ,0x00 },{TAB_SCANCODE      ,0x00 },TRIGGER_KEY},
{{0x00              ,u'q' },{0x00              ,u'Q' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'w' },{0x00              ,u'W' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'e' },{0x00              ,u'E' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'r' },{0x00              ,u'R' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u't' },{0x00              ,u'T' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'y' },{0x00              ,u'Y' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'u' },{0x00              ,u'U' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'i' },{0x00              ,u'I' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'o' },{0x00              ,u'O' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'p' },{0x00              ,u'P' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'´' },{0x00              ,u'¨' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'+' },{0x00              ,u'*' },{0x00              ,0x00 },TRIGGER_KEY},
{{ENTER_SCANCODE    ,0x00 },{ENTER_SCANCODE    ,0x00 },{ENTER_SCANCODE    ,0x00 },TRIGGER_KEY},
{{CTRL_SCANCODE     ,0x00 },{CTRL_SCANCODE     ,0x00 },{CTRL_SCANCODE     ,0x00 },0},
{{0x00              ,u'a' },{0x00              ,u'A' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u's' },{0x00              ,u'S' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'd' },{0x00              ,u'D' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'f' },{0x00              ,u'F' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'g' },{0x00              ,u'G' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'h' },{0x00              ,u'H' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'j' },{0x00              ,u'J' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'k' },{0x00              ,u'K' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'l' },{0x00              ,u'L' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'ñ' },{0x00              ,u'Ñ' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'{' },{0x00              ,u'[' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'|' },{0x00              ,u'°' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,0x00 },{0x00              ,0x00 },{0x00              ,0x00 },SHIFT_KEY  },
{{0x00              ,u'}' },{0x00              ,u']' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'z' },{0x00              ,u'Z' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'x' },{0x00              ,u'X' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'c' },{0x00              ,u'C' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'v' },{0x00              ,u'V' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'b' },{0x00              ,u'B' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'n' },{0x00              ,u'N' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'm' },{0x00              ,u'M' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u',' },{0x00              ,u';' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'.' },{0x00              ,u':' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,u'-' },{0x00              ,u'_' },{0x00              ,0x00 },TRIGGER_KEY},
{{0x00              ,0x00 },{0x00              ,0x00 },{0x00              ,0x00 },SHIFT_KEY  },

};

static const keymap_entry_t ext_keymap[128]=
{

};

uint8_t kb_read() 
{
while(!(inb(0x64)&1));
return inb(0x60);
}

uint8_t kb_read_nowait() 
{
return inb(0x60);
}

void kb_write(uint16_t port,uint8_t value) 
{
while(inb(0x64)&2);
outb(port,value);
}

void init_keyboard()
{
kb_write(0x64,0xae);
inb(0x60);

keyboard_shift=false;
keyboard_alt_gr=false;
keyboard_caps_lock=false;
}


key_t get_key()
{
UINT8 scancode;
UINT8 extended_scancode;
key_t key;
while (true)
{
scancode=kb_read();
if(scancode==EXTENDED_KEY)
{
extended_scancode=kb_read();



return key;
}


keymap_entry_t entry=keymap[scancode&0x7F];




if((entry.flags&SHIFT_KEY)==SHIFT_KEY)
{
if ((scancode&0x80)==0)
{keyboard_shift=true;}
else if(((scancode&0x80)==0x80))
{keyboard_shift=false;}
continue;
}


if(((scancode&0x80)==0) && ((entry.flags&TRIGGER_KEY)==TRIGGER_KEY))
{
if(keyboard_shift || keyboard_caps_lock)
{
key=entry.shifted;
}
else
{
key=entry.normal;

}

return key;
}
}
}
