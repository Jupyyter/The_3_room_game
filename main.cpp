#define SDL_MAIN_HANDLED
#include "sldlib.hpp"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

//this will need further encapsulation
bool Collide(Sprite& a, Sprite& b, Vector2& ap, Vector2& bp){
    return (ap.x + a.width >= bp.x && bp.x + b.width >= ap.x && ap.y + a.height >= bp.y && bp.y + b.height >= ap.y);
}

int main(){
    //init library
    RenderWindow::InitAll();

    //create window
    RenderWindow window("MARIOANA EROINA COCAINA CRACK", 1280, 720);
    window.setFps(60);

    // Load the sprite
    Sprite superidol("superIdol.jpg", window);
    Sound supersound("super-idol.wav");
    Player Unt("Untitled.png", window, Vector2(0,0));
    Vector2 suppos;

    //Main loop
    while (window.run())
    {
        if(window.keyPressed('a')){
            Unt.Travel(-1,0, 100);
        }
        if(window.keyPressed('d')){
            Unt.Travel(1,0, 100);
        }
        if(window.keyPressed('w')){
            Unt.Travel(0,-1, 100); 
        }
        if(window.keyPressed('s')){
            Unt.Travel(0,1, 100);
        }

        
        /*
        float distance = sqrt((Unt.pos.x - suppos.x)*(Unt.pos.x - suppos.x) + (Unt.pos.y - suppos.y)*(Unt.pos.y - suppos.y));

        if(distance <= 1000){
            supersound.SetVolume(128/1000.0f*(1000-distance));
            supersound.PlaySync();
        }
        */
        
        Unt.Move();
        
        window.clear();
        window.render(Unt, Unt.GetPos());
        //window.render(superidol, suppos.x, suppos.y);
        window.renderText("I am here", 255,255,255, 100, 200);
        window.display();
    }
    
    //Clean up
    RenderWindow::QuitAll();
    return 0;
}

