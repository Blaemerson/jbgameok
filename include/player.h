#include "types.h"

class Player
{
    public:
        Player();
        PositionType GetPosition();
        VelocityType GetVelocity();
        ScaleType GetScale();
    private:
        PositionType Position;
        VelocityType Velocity;
        ScaleType Scale;
};
