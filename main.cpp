#include<allegro.h>
#include<alpng.h>
#include<time.h>

BITMAP* buffer;
BITMAP* npc_1;
BITMAP* vending_machine;

struct vendingmachines{
    int x;
    int y;
}vendingmachine[10];

struct npcs{
    int x;
    int y;
    int gender;
    int type;
    int speed;
    int hunger;
    int money;
    int thirst;
    int priority;
}npc[10];

// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest)
{
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}


//A function to streamline error reporting in file loading
void abort_on_error(const char *message){
	 set_window_title("Error!");
	 if (screen != NULL){
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message, allegro_error);
	 exit(-1);
}


void update(){
    //NPC Parser
    for(int i=0; i<10; i++){



    //Wander
    if(npc[i].priority<1){
        int randomnum=random(1,npc[i].speed);
        if(randomnum==1)
            npc[i].x++;
        if(randomnum==2)
            npc[i].y++;
        if(randomnum==3)
            npc[i].x--;
        if(randomnum==4)
            npc[i].y--;

        }
    }



}
void draw(){
    rectfill(buffer,0,0,1024,768,makecol(255,255,255));
    draw_sprite(buffer,npc_1,npc[1].x,npc[1].y);
    draw_sprite(screen,buffer,0,0);

}








void setup(){

    srand(time(NULL));

    buffer=create_bitmap(1024,768);

    npc[1].x=100;
    npc[1].y=200;
    npc[1].gender=1;
    npc[1].speed=100;
    npc[1].hunger=25;
    npc[1].money=100;
    npc[1].thirst=100;

    if (!(npc_1 = load_bitmap("npc_1.png", NULL)))
      abort_on_error("Cannot find image npc_1.png\nPlease check your files and try again");
    if (!(vending_machine = load_bitmap("vending_machine.png", NULL)))
      abort_on_error("Cannot find image vending_machine.png\nPlease check your files and try again");
}






int main(){

  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);


  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");



  set_window_title("NPC City");
  setup();


    while(!key[KEY_ESC]){
        update();
        draw();
  	}

	return 0;
}
END_OF_MAIN()
