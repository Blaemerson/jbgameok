#include "types.h"

class Player
{
    public:
        Player();
        PositionType GetPosition();
        VelocityType GetVelocity();
    private:
        PositionType Position;
        VelocityType Velocity;
};
