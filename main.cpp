#define SDL_MAIN_HANDLED
#include "sldlib.hpp"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

//this will need further encapsulation
bool Collide(Sprite& a, Sprite& b, Vector2& ap, Vector2& bp){
    return (ap.x + a.width >= bp.x && bp.x + b.width >= ap.x && ap.y + a.height >= bp.y && bp.y + b.height >= ap.y);
}

//to do list:
//encapsulate SDL_Rect better
//draw the level using a function that is part of the window class
//maybe remove texture (seems unnecessary)

int main(){
    //init library
    RenderWindow::InitAll();

    //create window
    RenderWindow window("MARIOANA EROINA COCAINA CRACK", 1280, 720);
    window.setFps(60);

    // Load the sprite
    Sprite superidol("superIdol.jpg", window);
    Sound supersound("super-idol.wav");
    Player Unt("hehim.png", window, Vector2(0,0), 2.3f);
    level a("untitled.json", window, 2.3f);
    Vector2 suppos;

    //Main loop
    while (window.run())
    {
        if(window.keyPressed('a')){
            Unt.Travel(-1,0, 750);
        }
        if(window.keyPressed('d')){
            Unt.Travel(1,0, 750);
        }
        if(window.keyPressed('w')){
            Unt.Travel(0,-1, 750); 
        }
        if(window.keyPressed('s')){
            Unt.Travel(0,1, 750);
        }

        
        Vector2 ppos = Unt.GetPos();
        float distance = sqrt((ppos.x - suppos.x)*(ppos.x - suppos.x) + (ppos.y - suppos.y)*(ppos.y - suppos.y));

        if(distance <= 1000){
            supersound.SetVolume(128/1000.0f*(1000-distance));
            supersound.PlaySync();
        }
        
        
        Unt.Move(a.mapBounds);
        
        window.clear();
        a.renderLVL(window);
        Unt.Draw(window);
        window.render(superidol, suppos.x, suppos.y);
        window.renderText("I am here", 255,255,255, 100, 200);
        window.display();
    }
    
    //Clean up
    RenderWindow::QuitAll();
    return 0;
}

