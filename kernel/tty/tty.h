#pragma once

#include "mstdi.h"
#include "font.h"
#include "globals.h"
#include "alloc.h"

void clear_tty()
{
memset(tty_buffer,'\0',tty_w*tty_h*2);
memset(tty_changed_buffer,true,tty_w*tty_h);
tty_cursor_x=0;
tty_cursor_y=0;
memset(sgi.buffer,0,sgi.w*sgi.h*4);
}

void init_tty()
{
tty_w=sgi.w/8;
tty_h=sgi.h/8;
tty_buffer=(CHAR16*)mmap_allocate_pages(SIZE_TO_PAGES(tty_w*tty_h*2));
tty_changed_buffer=(bool*)mmap_allocate_pages(SIZE_TO_PAGES(tty_w*tty_h));
clear_tty();
}



extern "C" void _putchar(CHAR16 chr)
{
if(tty_cursor_x>tty_w)
{tty_cursor_y++;tty_cursor_x=0;}

if(tty_cursor_y>tty_h-1)
{
tty_cursor_y=tty_h-1;
memcpy(tty_buffer,tty_buffer+(tty_w*sizeof(CHAR8)),tty_w*(tty_h-1)*sizeof(CHAR16));
memset(tty_buffer+(tty_h-1)*tty_w,u'\0',tty_w*sizeof(CHAR16));
memset(tty_changed_buffer,true,tty_w*tty_h);
}

tty_changed_buffer[tty_cursor_x+(tty_cursor_y*tty_w)]=true;

switch (chr)
{
case u'\n':tty_cursor_y++;break;
case u'\r':tty_cursor_x=0;break;
case u'\0':break;

default:
tty_buffer[tty_cursor_x+(tty_cursor_y*tty_w)]=chr;
tty_cursor_x++;
break;
}
}

void _draw_char(UINTN chr_x,UINTN chr_y,CHAR16 chr)
{
static int x,y;
static int set=0;
for(y=0;y<8;y++) 
{
for(x=0;x<8;x++)
{
set=font[chr][y]&1<<x;
if(set)
{sgi.buffer[(chr_x+x)+(chr_y+y)*sgi.w]=0xDDDDDDDD;}
else
{sgi.buffer[(chr_x+x)+(chr_y+y)*sgi.w]=0;}
}
}
}

void draw_tty()
{
for (UINTN i=0;i<tty_w*tty_h;++i)
{
if((tty_buffer[i]<256) && (tty_changed_buffer[i]==true))
{
_draw_char((i%tty_w)*8,(i/tty_w)*8,tty_buffer[i]);
tty_changed_buffer[i]=false;
}
}
}