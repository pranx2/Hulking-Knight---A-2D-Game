#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>


//!GOTO: ENTITY------------------08;
class Entity{
  private:
    float x,y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
  public:
    Entity(float p_x,float p_y, SDL_Texture* p_tex);
    float getx();
    float gety();
    SDL_Texture* getTex();
    SDL_Rect GetCurrentFrame();
};

//!Base--------------01;
class RenderWindow{
  private:
    SDL_Window* window;
    SDL_Renderer* render;
  public:
    RenderWindow(const char* p_title, int p_w,int p_h);//Constructor with three parameters;
    SDL_Texture* LoadTexture(const char* p_pathfile);//Texture finding path;
    void cleanup();//Cleanup function for avoid memory leak;
    void clear();
    void renderer(Entity& p_entity);
    void display();

};
//!GOTO: 

//!GOTO: WINDOWS RENDERING-------------02

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

//!GOTO: TEXTURE RENDERING-------------06:

SDL_Texture* RenderWindow::LoadTexture(const char* p_pathfile){
  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(render,p_pathfile);
  if(texture == NULL){
    std::cout<<"Failed to Load Texture.\nError : "<<SDL_GetError()<<std::endl;
  }
  return texture;
}

//!GOTO: AVOID MEMORY LEAK----------------07;

void RenderWindow::cleanup(){
  SDL_DestroyWindow(window);//Cleanup function for avoid memory leak;
}
void RenderWindow::clear(){//Clearing The window;
  SDL_RenderClear(render);
}

//!GOTO: ENTITY--------------------09 

Entity::Entity(float p_x, float p_y,SDL_Texture* p_tex) : x(p_x), y(p_y), tex(p_tex){
  currentFrame.x = 0;
  currentFrame.y = 0;
  currentFrame.w = 32;
  currentFrame.h = 32;
}
float Entity::getx(){
  return x;
}
float Entity::gety(){
  return y;
}
SDL_Texture* Entity::getTex(){
  return tex;
}
SDL_Rect Entity::GetCurrentFrame(){
  return currentFrame;
} 
//!GOTO: RENDERING UNIT----------------------10;

void RenderWindow::renderer(Entity &p_entity){//rendering the Texture;
  SDL_Rect src;//Define texture position on x,y and size at w,h;
    src.x = p_entity.GetCurrentFrame().x;
    src.y = p_entity.GetCurrentFrame().y;
    src.w = p_entity.GetCurrentFrame().w;
    src.h = p_entity.GetCurrentFrame().h;

  SDL_Rect dst;
    dst.x = p_entity.getx() * 4;
    dst.y = p_entity.gety() * 4;
    dst.w = p_entity.GetCurrentFrame().w * 4;
    dst.h = p_entity.GetCurrentFrame().h * 4;

  SDL_RenderCopy(render,p_entity.getTex(),&src,&dst);
}
void RenderWindow::display(){//Previewing the rendering image;
  SDL_RenderPresent(render);
}

//!GOTO: MAIN-------------------03; 

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

//!Grass Texture;

SDL_Texture* grassTexture  = window.LoadTexture("res/gfx/ground_grass_1.png");//Grass Texture path;
int entities[3] = {56,43,65};

//!GOTO: GAMELOOP;-----------------05;

bool GameRunning = true;
SDL_Event event;
while(GameRunning){
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT) GameRunning = false;
  }
  window.clear();
  //!Grass Texture Render;
  window.rendereverything();
  window.display();
}





//!GOTO: Closing Window and Cleaning up Memory;----------------04;

  window.cleanup();
  SDL_Quit();
  return 0;
} 