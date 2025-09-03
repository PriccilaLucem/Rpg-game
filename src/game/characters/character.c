#include "./character.h"

void input(SDL_Event* event){
    switch (event->key.keysym.sym) {
                    case SDLK_UP:
                        OBJ_Translate(obj_model, 0, -0.5f, 0);
                        break;
                    case SDLK_DOWN:
                        OBJ_Translate(obj_model, 0, 0.5f, 0);
                        break;
                    case SDLK_LEFT:
                        OBJ_Translate(obj_model, -0.5f, 0, 0);
                        break;
                    case SDLK_RIGHT:
                        OBJ_Translate(obj_model, 0.5f, 0, 0);
                        break;
                    case SDLK_w:
                        OBJ_Translate(obj_model, 0, 0, 0.5f);
                        break;
                    case SDLK_s:
                        OBJ_Translate(obj_model, 0, 0, -0.5f);
                        break;
                    case SDLK_q:
                        OBJ_Rotate(obj_model, 0, 0.1f, 0);
                        break;
                    case SDLK_e:
                        OBJ_Rotate(obj_model, 0, -0.1f, 0);
                        break;
                    case SDLK_a:
                        OBJ_Scale(obj_model, 1.1f);
                        break;
                    case SDLK_z:
                        OBJ_Scale(obj_model, 0.9f);
                        break;
    }
}

MainCharacter* input_of_main_char(SDL_Renderer* renderer){
    
}