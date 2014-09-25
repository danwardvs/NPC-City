#include<allegro.h>
#include<alpng.h>

BITMAP* buffer;

void update(){
    draw_sprite(screen,buffer,0,0);

}








void setup(){
    buffer=create_bitmap(800,600);
}






int main(){

  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);


  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800,600, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");



  set_window_title("Window title here!");
  setup();


    while(!key[KEY_ESC]){
        update();
  	}

	return 0;
}
END_OF_MAIN()
