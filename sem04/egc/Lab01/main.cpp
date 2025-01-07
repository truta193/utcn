#include <iostream>
#include <SDL2/SDL.h>

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;
SDL_Renderer *renderer = NULL;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};
Uint32 rectagleColor;

Uint32 brushColor;
Uint32 lineThickness = 1;

bool quit = false;

int mouseX, mouseY;
int prevMouseX = 0, prevMouseY = 0;

bool initWindow() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == NULL) {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            windowSurface = SDL_GetWindowSurface(window);

            if (windowSurface == NULL) {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

                SDL_UpdateWindowSurface(window);
            }

        }
    }

    return success;
}

void destroyWindow() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void onClearScreen() {
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
}

void putpixel(SDL_Surface *theScreen, int x, int y, Uint32 pixel) {
    int byteperpixel = theScreen->format->BytesPerPixel;

    Uint8 *p = (Uint8*)theScreen->pixels + y * theScreen->pitch + x * byteperpixel;

    *(Uint32 *)p = pixel;
}

//Bresenham's line algorithm
void drawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel, int thickness) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    int xStep = (dx > dy) ? 0 : sx;
    int yStep = (dx > dy) ? sy : 0;

    int x = x0;
    int y = y0;

    thickness = (thickness % 2 == 0) ? thickness + 1 : thickness;

    while (true) {
        putpixel(Screen, x, y, pixel);

        for (int i = 1; i <= thickness / 2; i++) {
            putpixel(Screen, x + i * xStep, y + i * yStep, pixel);
            putpixel(Screen, x - i * xStep, y - i * yStep, pixel);
        }

        if (x == x1 && y == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

int main(int argc, char *argv[]) {
    if (!initWindow()) {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
    brushColor = SDL_MapRGB(windowSurface->format, 0, 0, 0);

    while (!quit) {
        if (SDL_WaitEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                quit = true;
            }

            if (currentEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                }
            }

            if (currentEvent.type == SDL_MOUSEWHEEL) {
                if(currentEvent.wheel.y > 0) // scroll up
                {
                    if (lineThickness < 10)
                        lineThickness++;
                }
                else if(currentEvent.wheel.y < 0) // scroll down
                {
                    if (lineThickness > 1)
                        lineThickness--;
                }
            }

            if (currentEvent.type == SDL_MOUSEMOTION) {
                prevMouseX = mouseX;
                prevMouseY = mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    drawLine(windowSurface, prevMouseX, prevMouseY, mouseX, mouseY, brushColor, lineThickness);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }

            if (currentEvent.type == SDL_KEYDOWN) {
                switch (currentEvent.key.keysym.sym) {
                    case SDLK_r:
                        brushColor = SDL_MapRGB(windowSurface->format, 255, 0, 0);
                        break;
                    case SDLK_g:
                        brushColor = SDL_MapRGB(windowSurface->format, 0, 255, 0);
                        break;
                    case SDLK_b:
                        brushColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
                        break;
                    case SDLK_q:
                        brushColor = SDL_MapRGB(windowSurface->format, 0, 0, 0);
                        break;
                    case SDLK_ESCAPE:
                        onClearScreen();
                        break;

                    default:
                        rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 0);
                        break;
                }
            }

            SDL_Rect brushColorRect = {0,0,30,30};
            SDL_FillRect(windowSurface, &brushColorRect, brushColor);

            SDL_UpdateWindowSurface(window);
        }
    }

    destroyWindow();
    return 0;
}