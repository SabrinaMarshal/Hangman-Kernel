#define VGA_ADDRESS 0xB8000  
#define YELLOW 14
#define WHITE 15

#define KEYBOARD_H
#define KEYBOARD_PORT 0x60
#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

unsigned short *terminal_buffer;
unsigned int vga_index;

char *word="HELLO";
int gword[30];
char guessed[30];

uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

void clear_screen(void)
{
    int index = 0;
    while (index < 80 * 25 * 2) {
            terminal_buffer[index] = ' ';
            index ++;
    }
}

void print_char(char c, unsigned char color)
{
    terminal_buffer[vga_index] = (unsigned short)c|(unsigned short)color << 8;
    vga_index+=2;
}

void print_string(char *str, unsigned char color)
{
    int index = 0;
    while (str[index]) {
            terminal_buffer[vga_index] = (unsigned short)str[index]|(unsigned short)color << 8;
            index++;
            vga_index++;
    }
}

void main(void)
{
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    char guess,keycode=0;
    int len=0,flag=0,count=6,correct=0,gletters=0,flag2=0;
    while(word[len])
    len++;
    for(int i=0;i<len;i++)
    gword[i]=0;
    while(count>0)
    {
    clear_screen();
    vga_index = 0;
    print_string("Enter guess ", WHITE);
    keycode = get_input_keycode();
    switch(keycode){
      case KEY_A :
        guess='A';
        break;
      case KEY_B :
        guess='B';
        break;
      case KEY_C :
        guess='C';
        break;
      case KEY_D :
        guess='D';
        break;
      case KEY_E :
        guess='E';
        break;
      case KEY_F :
        guess='F';
        break;
      case KEY_G :
        guess='G';
        break;
      case KEY_H :
        guess='H';
        break;
      case KEY_I :
        guess='I';
        break;
      case KEY_J :
        guess='J';
        break;
      case KEY_K :
        guess='K';
        break;
      case KEY_L :
        guess='L';
        break;
      case KEY_M :
        guess='M';
        break;
      case KEY_N :
        guess='N';
        break;
      case KEY_O :
        guess='O';
        break;
      case KEY_P :
        guess='P';
        break;
      case KEY_Q :
        guess='Q';
        break;
      case KEY_R :
        guess='R';
        break;
      case KEY_S :
        guess='S';
        break;
      case KEY_T :
        guess='T';
        break;
      case KEY_U :
        guess='U';
        break;
      case KEY_V :
        guess='V';
        break;
      case KEY_W :
        guess='W';
        break;
      case KEY_X :
        guess='X';
        break;
      case KEY_Y :
        guess='Y';
        break;
      case KEY_Z :
        guess='Z';
        break;
      }
      print_char(guess,WHITE);
      flag2=0;
      for(int i=0;i<gletters;i++)
      {
      if(guessed[i]==guess)
      {
      vga_index=80;
      print_string("Letter already tried",WHITE);
      sleep(0x1FFFFFFF);
      flag2=1;
      break;
      }
      }
      if(flag2==1)
      continue;
      guessed[gletters]=guess;
      gletters++;
      flag=0;
      for(int i=0;i<len;i++)
      {
      if(guess==word[i])
      {
      gword[i]=1;
      flag=1;
      correct++;
      }
      }
      if(flag==0)
      count--;
      vga_index=100;
      for(int i=0;i<len;i++)
      {
      if(gword[i]==1) print_char(word[i],WHITE);
      else print_char('_',WHITE);
      }
      if(correct==len)
      {
      vga_index=260;
      print_string("You Win!!",WHITE);
      break;
      }
     
      switch(count)
      {
      case 0:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||   \\0/",YELLOW);
         vga_index=480;
         print_string("||    | ",YELLOW);
         vga_index=560;
         print_string("||   / \\",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 0",WHITE);
         break;
       case 1:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||   \\0/",YELLOW);
         vga_index=480;
         print_string("||    | ",YELLOW);
         vga_index=560;
         print_string("||   /  ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 1",WHITE);
         break;
       case 2:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||   \\0/",YELLOW);
         vga_index=480;
         print_string("||    | ",YELLOW);
         vga_index=560;
         print_string("||      ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 2",WHITE);
         break;
       case 3:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||   \\0/",YELLOW);
         vga_index=480;
         print_string("||      ",YELLOW);
         vga_index=560;
         print_string("||       ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 3",WHITE);
         break;
       case 4:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||   \\0 ",YELLOW);
         vga_index=480;
         print_string("||      ",YELLOW);
         vga_index=560;
         print_string("||      ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 4",WHITE);
         break;
       case 5:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||    0 ",YELLOW);
         vga_index=480;
         print_string("||      ",YELLOW);
         vga_index=560;
         print_string("||      ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 5",WHITE);
         break;
       case 6:
         vga_index=240;
         print_string("||===== ",YELLOW);
         vga_index=320;
         print_string("||    | ",YELLOW);
         vga_index=400;
         print_string("||      ",YELLOW);
         vga_index=480;
         print_string("||      ",YELLOW);
         vga_index=560;
         print_string("||      ",YELLOW);
         vga_index=640;
         print_string("||      ",YELLOW);
         vga_index=720;
         print_string("No of tries left: 6",WHITE);
         break;
       }
       if(count==0)
       {
       vga_index=820;
       print_string("You lose",WHITE);  
       break;
       }
       sleep(0x5FFFFFFF);
    }
    return;
}
