#include "sdlLib.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL), deltatime(1000/60)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_FULLSCREEN);

    if (window == NULL)
    {
        std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load fonts
    font = TTF_OpenFont("font.ttf", 24);
}

RenderWindow::~RenderWindow()
{
    //SDL_DestroyWindow(this->window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(const Sprite& sprite, int x, int y)
{
    SDL_Rect destrect;
    destrect.x = x;
    destrect.y = y;
    destrect.h = sprite.height;
    destrect.w = sprite.width;
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destrect);
}

void RenderWindow::render(const Sprite& sprite, vector2 pos)
{
    SDL_Rect destrect;
    destrect.x = pos.x;
    destrect.y = pos.y;
    destrect.h = sprite.height;
    destrect.w = sprite.width;
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destrect);
}

void RenderWindow::render(const Sprite& sprite, SDL_Rect srcrect, SDL_Rect destrect){
    SDL_RenderCopy(renderer, sprite.texture, &srcrect, &destrect);
}

void RenderWindow::renderText(std::string text, unsigned char r, unsigned char g, unsigned char b, int x, int y){
    //create a surface using the font, the color and the text in order to create a texture
    SDL_Color color = {r, g, b};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //free the surface
    SDL_FreeSurface(surface);

    // Render the texture onto the screen
    SDL_Rect destRect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    //free the texture
    SDL_DestroyTexture(texture);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);

    Uint32 timepassed = SDL_GetTicks() - timer;
    if(deltatime > timepassed){
        SDL_Delay(deltatime - timepassed);
    }
}

bool RenderWindow::run()
{
    timer = SDL_GetTicks();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            return false;
            break;
        }
        case SDL_KEYUP:
        {
            char keypressed = event.key.keysym.sym;
            keyboard[keypressed] = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            char keypressed = event.key.keysym.sym;
            keyboard[keypressed] = true;
            break;
        }
        }
    }
    return true;
}

bool RenderWindow::keyPressed(char key){
    return this->keyboard[key];
}
bool RenderWindow::keyPressedDown(SDL_Scancode key)
{
    static const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    static std::map<SDL_Scancode, bool> key_states;

    bool& state = key_states[key];
    bool pressed = keyboard_state[key];

    if (pressed && !state) {
        state = true;
        return true;
    } else if (!pressed && state) {
        // key has just been released
        state = false;
    }

    return false;
}

void RenderWindow::setFps(int fps){
    this->deltatime = 1000.0f/fps;
}

void RenderWindow::InitAll(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error SDL: ", SDL_GetError();
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	    std::cout << "Error SDL2_image: " << IMG_GetError();
    }

    if(TTF_Init() < 0){
        std::cout << "Error SDL_TTF: " << TTF_GetError();
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "Error SDL audio: " << TTF_GetError();
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::cout << "Error SDL_Mixer: " << Mix_GetError();
    }

}

int RenderWindow::getFontWidth(){
    // Get the size of an individual letter in the rendered text surface
    int letterWidth, letterHeight;
    TTF_SizeText(font, "A", &letterWidth, &letterHeight);
    return letterWidth;
}

void RenderWindow::QuitAll(){
    // Shut down SDL2_ttf
    TTF_Quit();

    // Shut down SDL2_image
    IMG_Quit();

    // Shut down SDL2
    SDL_Quit();

    // Shut down mixel
    Mix_CloseAudio();
}