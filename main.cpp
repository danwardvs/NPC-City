#include<allegro.h>
#include<alpng.h>

BITMAP* buffer;
BITMAP* npc_1;

struct npcs{
    int x;
    int y;
    int gender;
    int type;
}npc[10];

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



}
void draw(){
    rectfill(buffer,0,0,1024,768,makecol(255,255,255));
    draw_sprite(buffer,npc_1,npc[1].x,npc[1].y);
    draw_sprite(screen,buffer,0,0);

}








void setup(){
    buffer=create_bitmap(1024,768);

    npc[1].x=100;
    npc[1].y=200;
    npc[1].gender=1;

    if (!(npc_1 = load_bitmap("npc_1.png", NULL)))
      abort_on_error("Cannot find image npc_1.png\nPlease check your files and try again");
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
