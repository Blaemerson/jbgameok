#include "types.h"

class Player
{
    public:
        Player()
        {
            position = {0,0};
            velocity = {0.f};
        }
        Position getPosition()
        {
            return position;
        }
        Velocity getVelocity()
        {
            return velocity;
        }
    private:
        Position position;
        Velocity velocity;
};
