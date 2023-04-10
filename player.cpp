#include "sldlib.hpp"

Player::Player(std::string name, RenderWindow window, Vector2 pos) : Sprite(name, window), pos(pos), moving(false), shouldmove(false){
    
}

Vector2 Player::GetPos(){
    return this->pos;
}

void Player::Move(){
    if(shouldmove){
        if(!moving){
            this->Timep = std::chrono::steady_clock::now();
            this->lx = int(this->pos.x);
            this->ly = int(this->pos.y);
            moving = true;
        }
        else{
            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - this->Timep).count();
            float ratio = float(duration)/milliseconds;
            if(ratio <= 1.0f){
                this->pos.x = lx + nx*32*ratio;
                this->pos.y = ly + ny*32*ratio;
            }
            else{
                this->pos.x = lx + nx*32;
                this->pos.y = ly + ny*32;
                this->moving = false;
                this->shouldmove = false;
            }
        }
    }
}

void Player::Travel(int x, int y, uint32_t m){
    if(!moving){
        this->shouldmove = true;
        this->nx = x;
        this->ny = y;
        this->milliseconds = m;
    }
}