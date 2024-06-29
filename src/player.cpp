#include "player.h"

Player::Player()
{
    Position = {0, 0};
    Velocity = {0.f};
}

VelocityType Player::GetVelocity()
{
    return Velocity;
}

PositionType Player::GetPosition()
{
    return Position;
}