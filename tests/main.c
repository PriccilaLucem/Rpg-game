#include <SDL.h>
#include <SDL_ttf.h>

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif

#if defined(_WIN32) || defined(WIN32)
    int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow){
#else
    int main(int argc, char **argv){
#endif

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL Test", 
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640,
                                        480,
                                        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Fill surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait 5 seconds
    SDL_Delay(5000);

    // Destroy window    
    return 0;
}