#include "../include/CellularUnit.hpp"

CellularUnit::CellularUnit(float x, float y, size_t id)
    : coords_(std::pair<float, float>(x, y)), velocity_(std::pair<float, float>(0.0 , 0.0)), 
    neighbors_(std::list<const CellularUnit *>()), id_(id), behavior_(CellBehavior::PERIPHERICAL_VIEW)
{
    std::cout << " CellularUnit created : " << id << " (" << coords_.first << ", " << coords_.second << ")" << std::endl;
    // velocity_.first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10.0)));
    velocity_.first = 1.0;

    // Angle between 0 and 2*PI
    velocity_.second  = static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(2*M_PI))) - M_PIf);
}

CellularUnit::~CellularUnit()
{
    //std::cout << " CellularUnit destroyed : " << coords_.first << " " << coords_.second << std::endl;
}

float CellularUnit::getAngleToNeighbor(const CellularUnit * cellNeighbor){
    return atan2f(cellNeighbor->getY() - coords_.second, cellNeighbor->getX() - coords_.first);
}

float CellularUnit::getDistanceToNeighbor(const CellularUnit * cellNeighbor){
    return (sqrt(pow(cellNeighbor->getX() - this->getX(), 2) + pow(cellNeighbor->getY() - this->getY(), 2)));
}

void CellularUnit::move()
{
    updateVelocity();
    coords_.first += velocity_.first * cos(velocity_.second);
    coords_.second += velocity_.first * sin(velocity_.second);

    if (coords_.first < 0)
    {
        coords_.first = (SCREEN_X) - coords_.first;
    }
    else if (coords_.first > (SCREEN_X))
    {
        coords_.first = coords_.first - (SCREEN_X);
    }

    if (coords_.second < 0)
    {
        coords_.second = (SCREEN_Y) - coords_.second;
    }
    else if (coords_.second > (SCREEN_Y))
    {
        coords_.second = coords_.second - (SCREEN_Y);
    }
}

void CellularUnit::updateVelocityPeriphericalView(){
    for (std::list<const CellularUnit *>::iterator it = neighbors_.begin(); it != neighbors_.end(); ++it){

        float angleToNeighbor = getAngleToNeighbor(*it);
        float diffAngle = fmodf(velocity_.second - angleToNeighbor, 2*M_PI);
        // Is the neighbor visible ?
        if(fabsf(diffAngle) <= ANGLE_VIEW / 2 ){
            float proximityFactor = (getDistanceToNeighbor(*it) / DISTANCE_VIEW);
            velocity_.second += (proximityFactor) * (diffAngle/10); 
        }      
    }
}

void CellularUnit::updateVelocity()
{
    switch(behavior_)
    {
        case CellBehavior::NONE:
            break;
        case CellBehavior::ACCELERATE:
            velocity_.first += 0.1;
            break;
        case CellBehavior::DECELERATE:
            velocity_.first -= 0.1;
            break;
        case CellBehavior::PERIPHERICAL_VIEW:
            updateVelocityPeriphericalView();
            break;
        default:
            break;
    }
}