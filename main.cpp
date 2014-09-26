#include<math.h>
#include<allegro.h>
#include<alpng.h>
#include<time.h>


BITMAP* buffer;
BITMAP* cursor;
BITMAP* npc_1;
BITMAP* skin_1;
BITMAP* skin_2;
BITMAP* skin_3;
BITMAP* skin_4;
BITMAP* skin_5;
BITMAP* vending_machine;

bool close_button_pressed;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

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
    float thirst;
    float happiness;
    bool alive;
    int priority;
    int social;
    int skin;
}npc[10];

// Function to check for collision
bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2)
{
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1){
    return true;
  }
  return false;
}

//Distance to object
int distance_to_object(int x_1, int y_1,int x_2,int y_2){
    return sqrt((pow(x_1-x_2,2))+(pow(y_1-y_2,2)));
}
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
    if(npc[i].alive){
        if(npc[i].happiness<1)npc[i].alive=false;
        if(npc[i].x<1)npc[i].x=1;
        if(npc[i].y<1)npc[i].y=1;

        npc[i].thirst-=0.001;
        npc[i].happiness-=0.1;
        //Get a drink
        if(npc[i].thirst<75){
            if(npc[i].priority<2)
                npc[i].priority=2;
        }
       if(npc[i].thirst<75 && npc[i].priority==2){
            //Find a vending machine
            int closest_vending_machine;
            int distance_will_travel=500;

            for(int j=0; j<10; j++){
                if(distance_to_object(npc[i].x,npc[i].y,vendingmachine[j].x,vendingmachine[j].y)<distance_will_travel)
                    closest_vending_machine=j;
            }
            if(vendingmachine[closest_vending_machine].x+15>npc[i].x)npc[i].x+=1*npc[i].speed;
            if(vendingmachine[closest_vending_machine].x+15<npc[i].x)npc[i].x-=1*npc[i].speed;
            if(vendingmachine[closest_vending_machine].y+30>npc[i].y)npc[i].y+=1*npc[i].speed;
            if(vendingmachine[closest_vending_machine].y+30<npc[i].y)npc[i].y-=1*npc[i].speed;
            if(collision(vendingmachine[closest_vending_machine].x,vendingmachine[closest_vending_machine].x+60,npc[i].x,npc[i].x,vendingmachine[closest_vending_machine].y,vendingmachine[closest_vending_machine].y+60,npc[i].y,npc[i].y)){
                if(npc[i].money>2){
                    npc[i].thirst+=50;
                    if(npc[i].thirst>75)npc[i].priority=0;
                    npc[i].money-=2;
                }
            }
        }
        if(npc[i].x<1)npc[i].x=1;
        if(npc[i].y<1)npc[i].y=1;
        //Get away from people

        for(int j=0; j<10; j++){
            if(distance_to_object(npc[i].x,npc[i].y,npc[j].x,npc[j].y)<npc[i].social){
                if(npc[i].priority==0){
                    if(npc[j].x>npc[i].x)npc[i].x-=1*npc[i].speed;
                    if(npc[j].x<npc[i].x)npc[i].x+=1*npc[i].speed;
                    if(npc[j].y<npc[i].y)npc[i].y-=1*npc[i].speed;
                    if(npc[j].y<npc[i].y)npc[i].y+=1*npc[i].speed;
                    if(npc[j].x==npc[i].x)npc[i].x+10;
                    if(npc[j].y==npc[i].y)npc[i].y+10;

                    }
                }
            }






        //Wander
        if(npc[i].priority<1){
            int randomnum=random(1,4);
            if(randomnum==1)
                npc[i].x+=1*npc[i].speed;
            if(randomnum==2)
                npc[i].y+=1*npc[i].speed;
            if(randomnum==3)
                npc[i].x-=1*npc[i].speed;
            if(randomnum==4)
                npc[i].y-=1*npc[i].speed;

            }
        }
    }


}
void draw(bool to_screen){
    rectfill(buffer,0,0,1024,768,makecol(255,255,255));
    for(int i=0; i<10; i++){
        draw_sprite(buffer,vending_machine,vendingmachine[i].x,vendingmachine[i].y);
    }
    for(int i=0; i<10; i++){
        if(npc[i].skin==1)draw_sprite(buffer,skin_1,npc[i].x,npc[i].y);
        if(npc[i].skin==2)draw_sprite(buffer,skin_2,npc[i].x,npc[i].y);
        if(npc[i].skin==3)draw_sprite(buffer,skin_3,npc[i].x,npc[i].y);
        if(npc[i].skin==4)draw_sprite(buffer,skin_4,npc[i].x,npc[i].y);
        if(npc[i].skin==4)draw_sprite(buffer,skin_4,npc[i].x,npc[i].y);
        if(npc[i].skin==5)draw_sprite(buffer,skin_5,npc[i].x,npc[i].y);
        textprintf_centre_ex( buffer, font, npc[i].x+16, npc[i].y-10, makecol(0,0,0), -1, "%i", npc[i].money);
        textprintf_centre_ex( buffer, font, npc[i].x+16, npc[i].y-18, makecol(0,0,0), -1, "%4.2f", npc[i].happiness);
        textprintf_centre_ex( buffer, font, npc[i].x+16, npc[i].y-26, makecol(0,0,0), -1, "%i", npc[i].priority);
    }
    draw_sprite(buffer,cursor,mouse_x,mouse_y);
    draw_sprite(screen,buffer,0,0);

}








void setup(){

    srand(time(NULL));

     // Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));

    // Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

    buffer=create_bitmap(1024,768);

    npc[0].x=500;
    npc[0].y=100;
    npc[0].speed=10;
    npc[0].hunger=25;
    npc[0].money=100;
    npc[0].thirst=0;
    npc[0].social=0;
    npc[0].skin=5;

    for(int i=1; i<10; i++){
        npc[i].speed=1;
        npc[i].skin=random(1,4);
        npc[i].money=100;
        npc[i].x=random(1,1000);
        npc[i].y=random(1,1000);
        npc[i].social=100;
        npc[i].happiness=100;
        npc[i].alive=true;
    }
    for(int i=0; i<10; i++){
        vendingmachine[i].x=random(1,1000);
        vendingmachine[i].y=random(1,600);
    }



    if (!(npc_1 = load_bitmap("npc_1.png", NULL)))
      abort_on_error("Cannot find image npc_1.png\nPlease check your files and try again");
    if (!(cursor = load_bitmap("cursor.png", NULL)))
      abort_on_error("Cannot find image cursor.png\nPlease check your files and try again");
    if (!(skin_1 = load_bitmap("skin_1.png", NULL)))
      abort_on_error("Cannot find image skin_1.png\nPlease check your files and try again");
    if (!(skin_2 = load_bitmap("skin_2.png", NULL)))
      abort_on_error("Cannot find image skin_2.png\nPlease check your files and try again");
    if (!(skin_3= load_bitmap("skin_3.png", NULL)))
      abort_on_error("Cannot find image skin_3.png\nPlease check your files and try again");
    if (!(skin_4 = load_bitmap("skin_4.png", NULL)))
      abort_on_error("Cannot find image skin_4.png\nPlease check your files and try again");
    if (!(skin_5 = load_bitmap("skin_5.png", NULL)))
      abort_on_error("Cannot find image skin_5.png\nPlease check your files and try again");


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


    while(!key[KEY_ESC] && !close_button_pressed){
        while(ticks == 0){
            rest(1);
        }
    while(ticks > 0){
        int old_ticks = ticks;

        update();

        ticks--;
        if(old_ticks <= ticks){
            break;
        }
    }
        if(game_time - old_time >= 10){
            fps = frames_done;
            frames_done = 0;
            old_time = game_time;
        }
        draw(true);
    }


	return 0;
}
END_OF_MAIN()
