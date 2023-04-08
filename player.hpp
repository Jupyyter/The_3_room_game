#pragma once

class Player : public Sprite{
    public:
    Player(std::string name, RenderWindow window, Vector2 pos);
    void Travel(int x, int y, uint32_t m);
    void Move();//moving to a tile
    Vector2 GetPos();

    private:
    Vector2 pos;
    bool moving, shouldmove;
    std::chrono::steady_clock::time_point Timep;
    int lx,ly,nx,ny;
    uint32_t milliseconds;
};