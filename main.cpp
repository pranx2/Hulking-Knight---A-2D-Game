#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
//Base;
class RenderWindow{
  private:
    SDL_Window* window;
    SDL_Renderer* render;
  public:
    RenderWindow(const char* p_title, int p_w,int p_h);//Constructor with three parameters;
    SDL_Texture* LoadTexture(const char* p_pathfile);//Texture finding path;
    void cleanup();//Cleanup function for avoid memory leak;
    void clear();
    void renderer(SDL_Texture* p_text);
    void display();

};
//!GOTO: 


};
//!GOTO: ENTITY
class Entity{
  private:
    float x,y;
  public:



};
//!GOTO: WINDOWS RENDERING
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h): window(NULL), render(NULL){//Default Initialized;
 window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);
 if(window == NULL){
  std::cout<<"Failed to Initializing Window.\nError : "<<SDL_GetError()<<std::endl;
 }
 render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 if(render == NULL){
  std::cout<<"Failed to Initializing Rendering.\nError : "<<SDL_GetError()<<std::endl;
 }
}
//!GOTO: TEXTURE RENDERING:
SDL_Texture* RenderWindow::LoadTexture(const char* p_pathfile){
  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(render,p_pathfile);
  if(texture == NULL){
    std::cout<<"Failed to Load Texture.\nError : "<<SDL_GetError()<<std::endl;
  }
  return texture;
}
//!GOTO: AVOID MEMORY LEAK;
void RenderWindow::cleanup(){
  SDL_DestroyWindow(window);//Cleanup function for avoid memory leak;
}
void RenderWindow::clear(){//Clearing The window;
  SDL_RenderClear(render);
}
//!GOTO: RENDERING UNIT;
void RenderWindow::renderer(SDL_Texture* p_text){//rendering the Texture;
  SDL_Rect src;//Define texture position on x,y and size at w,h;
    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

  SDL_Rect dst;
    dst.x = 400;
    dst.y = 200;
    dst.w = 32 * 4;
    dst.h = 32 * 4;

  SDL_RenderCopy(render, p_text,&src,&dst);
}
void RenderWindow::display(){//Previewing the rendering image;
  SDL_RenderPresent(render);
}


//!GOTO: MAIN 
int main(int argc, char* args[]){
if(SDL_Init(SDL_INIT_EVERYTHING) != 0){ //Checking SDL everything;
  std::cout<<"Failed to Initializing SDL.\nError : "<<SDL_GetError()<<std::endl;
}
if(SDL_Init(SDL_INIT_VIDEO) != 0){//Checking Video;
  std::cout<<"Failed to Initializing Video.\nError : "<<SDL_GetError()<<std::endl;
}
if(SDL_Init(IMG_INIT_PNG) != 0){//Checking Image;
  std::cout<<"Failed to Initializing Texture.\nError: "<<SDL_GetError()<<std::endl;
}
//Init Window;
RenderWindow window("Halking Knight - A 2D Game v1.0",720,480);//Game Name and Size;
//? Grass Texture;
SDL_Texture* grassTexture  = window.LoadTexture("res/gfx/ground_grass_1.png");//Grass Texture path;
float bobx, boby;
Entity bob;
//!GOTO: GAMELOOP;
bool GameRunning = true;
SDL_Event event;
while(GameRunning){
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT) GameRunning = false;
  }
  window.clear();
  window.renderer(grassTexture);
  window.display();
}





//!GOTO: Closing Window and Cleaning up Memory;
  window.cleanup();
  SDL_Quit();
  return 0;
} 