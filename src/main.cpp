#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include<iostream>
#include<vector>
//!GOTO: UTILITIES------------------12;
namespace utils{
  inline float hireTimeInSeconds(){
    float t = SDL_GetTicks();
    t *= 0.001f;
    return t;
  }
}

//!GOTO: VECTOR------------------11;
class vector2f{
  private:
  public:
    float x, y;
    vector2f(): x(0.0f), y(0.0f){

    }
    vector2f(float p_x, float p_y): x(p_x), y(p_y) {
      x = p_x ;
    }
    void print(){
      std::cout<< x << " , " << y <<std::endl;
    }
};
vector2f vec;
vector2f vec0(1.f,34.f);
//!GOTO: ENTITY------------------08;
class Entity{
  private:
    float x,y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    vector2f pos;
  public:
    Entity(vector2f p_pos, SDL_Texture* p_tex);
    float getx();
    float gety();
    SDL_Texture* getTex();
    SDL_Rect GetCurrentFrame();
    vector2f& getpos(){
      return pos;
    }
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
    int GetRefreshRate();
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
 render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

int RenderWindow::GetRefreshRate(){
  int displayIndex = SDL_GetWindowDisplayIndex(window);
  SDL_DisplayMode mode;
  SDL_GetDisplayMode(displayIndex,0,&mode);
    return mode.refresh_rate;
}
//!GOTO: AVOID MEMORY LEAK----------------07;

void RenderWindow::cleanup(){
  SDL_DestroyWindow(window);//Cleanup function for avoid memory leak;
}
void RenderWindow::clear(){//Clearing The window;
  SDL_RenderClear(render);
}

//!GOTO: ENTITY--------------------09 

Entity::Entity(vector2f p_pos, SDL_Texture* p_tex) : pos(p_pos), tex(p_tex){
  currentFrame.x = 0;
  currentFrame.y = 0;
  currentFrame.w = 32;
  currentFrame.h = 32;
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
    dst.x = p_entity.getpos().x * 4;
    dst.y = p_entity.getpos().y * 4;
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
RenderWindow window("Hulking Knight - A 2D Game v1.0",720,480);//Game Name and Size;
int windowRefreshRate = window.GetRefreshRate();
std::cout <<window.GetRefreshRate()<< std::endl;
//!Grass Texture;

SDL_Texture* grassTexture  = window.LoadTexture("res/gfx/ground_grass_1.png");//Grass Texture path;

// Entity entities[13] = {Entity(0,0,grassTexture),
//                       Entity(30,0,grassTexture),
//                       Entity(30,0,grassTexture),
//                       Entity(90,0,grassTexture),
//                       Entity(120,0,grassTexture),
//                       Entity(150,0,grassTexture),
//                       Entity(30,0,grassTexture),
//                       Entity(60,0,grassTexture),
//                       Entity(90,30,grassTexture),
//                       Entity(90,30,grassTexture),
//                       Entity(120,30,grassTexture),
//                       Entity(150,30,grassTexture),
//                       Entity(180,30,grassTexture),
                      // };
std::vector<Entity> entitiees = {
                      Entity(vector2f(0,0), grassTexture),
                      Entity(vector2f(30,0), grassTexture),
                      Entity(vector2f(90,0), grassTexture),
                      Entity(vector2f(30,0), grassTexture),
                      Entity(vector2f(120,0),grassTexture),
                      Entity(vector2f(150,0),grassTexture),
                      Entity(vector2f(30,0),grassTexture),
                      Entity(vector2f(60,0),grassTexture),
                      Entity(vector2f(90,30),grassTexture),
                      Entity(vector2f(90,30),grassTexture),
                      Entity(vector2f(120,30),grassTexture),
                      Entity(vector2f(150,30),grassTexture),
                      Entity(vector2f(180,30),grassTexture)
                      };
//!GOTO: GAMELOOP;-----------------05;

bool GameRunning = true;
SDL_Event event;
const float timestep = 0.01f;
float accumlator = 0.0f;
float currentTime = utils::hireTimeInSeconds();
while(GameRunning){
  int starTick = SDL_GetTicks();
  float newTime = utils::hireTimeInSeconds();
  float frameTime = newTime - currentTime;
  currentTime = newTime;
  accumlator+= frameTime;
  while(accumlator >= timestep){
  //!Game control and Events;
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT) GameRunning = false;
  }
  accumlator-=timestep;
}
  const float alpha = accumlator / timestep;
  
  window.clear();
  //!Grass Texture Render;
      for(Entity& e : entitiees){
          window.renderer(e);
      }
      // std:: cout << utils ::hireTimeInSeconds()<< std::endl;
  window.display();
  int fraameTicks = SDL_GetTicks() - starTick;
  if(fraameTicks < 100/window.GetRefreshRate()){
    SDL_Delay(100/window.GetRefreshRate()- fraameTicks);
  }
}





//!GOTO: Closing Window and Cleaning up Memory;----------------04;

  window.cleanup();
  SDL_Quit();
  return 0;
} 