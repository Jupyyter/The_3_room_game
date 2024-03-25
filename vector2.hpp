#pragma once

struct vector2
{
	vector2()
	:x(0.0f), y(0.0f)
	{}

	vector2(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	float x, y;

	    bool operator<(const vector2& other) const
    {
        if (x < other.x)
            return true;
        else if (x > other.x)
            return false;
        else
            return y < other.y;
    }
};
vector2 add(vector2 vct0,vector2 vct1);