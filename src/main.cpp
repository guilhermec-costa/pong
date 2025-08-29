#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int main()  {
  int WINDOW_HEIGHT = 600;
  int WINDOW_WIDTH = 900;

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("my window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if(!window) {
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    return -1;
  }

  int running = 1;

  int left_paddle_direction = -1;
  float left_paddle_y  = (WINDOW_HEIGHT / 2.0f) - 100.0f;

  int right_paddle_direction = 1;
  float right_paddle_y = (WINDOW_HEIGHT / 2.0f) - 100.0f;

  float paddle_velocity = 0.009f;

  const int FPS = 60;
  const int MS_FRAME_DELAY = 1000 / FPS;
  Uint32 frame_start;
  int frame_time;

  SDL_Event event;
  while(running) {
    frame_start = SDL_GetTicks();
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT: {
          running = false;
          std::cout << "Quitting \n";
        }

        case SDL_KEYDOWN: {
          if(event.key.keysym.sym == SDLK_UP) right_paddle_direction = -1;
          if(event.key.keysym.sym == SDLK_DOWN) right_paddle_direction = 1;

          if(event.key.keysym.sym == SDLK_w) left_paddle_direction = -1;
          if(event.key.keysym.sym == SDLK_s) left_paddle_direction = 1;
          break;
        }
      }
    }
    right_paddle_y += right_paddle_direction *  paddle_velocity;
    left_paddle_y += left_paddle_direction *  paddle_velocity;

    if(right_paddle_y < 0 || right_paddle_y + 200 >= WINDOW_HEIGHT) {
      right_paddle_direction *= -1;
    }

    if(left_paddle_y < 0 || left_paddle_y + 200 >= WINDOW_HEIGHT) {
      left_paddle_direction *= -1;
    }

    SDL_Rect left_paddle = {20, (int)left_paddle_y, 30, 200};
    SDL_Rect right_paddle = {WINDOW_WIDTH - 50, (int)right_paddle_y, 30, 200};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &right_paddle);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &left_paddle);

    SDL_RenderPresent(renderer);

    frame_time = SDL_GetTicks() - frame_start;
    if(MS_FRAME_DELAY > frame_time) {
      SDL_Delay(frame_time);
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

