#pragma once
#include <math.h>
#include <algorithm>

struct Box
{
    float position_x;
    float position_y;
    float m_width  = 1.0f;
    float m_height = 1.0f;

    /** Detects intersection (overlap) between this Box and another Box instance.
    *   \param other is a reference to another Box instance to check for collision with
    *   \return true if the two boxes overlap
    */
    bool intersect(const Box& other) const
    {
        return (position_x < other.position_x + other.m_width &&
            position_x + m_width > other.position_x &&
            position_y < other.position_y + other.m_height &&
            position_y + m_height > other.position_y);
    }

    /** Detects an intersection when this Box is "above" (smaller y values) a target box (other)
    *   and reports the adjustment offset so that the two boxes are separated.
    *   
    *   \param other is the second (target) Box to test collision on the vertical axis with.
    *   \return the offset this Box needs to move in the y axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectDown(Box &other) 
    {
        if (fabs(position_x - other.position_x) * 2.0f >= (m_width + other.m_width) || position_y > other.position_y)
            return 0.0f;
        return std::min<float>(0.0f, other.position_y - (other.m_height / 2.0f) - position_y - (m_height / 2.0f));
    }

    /** Detects a horizontal intersection this Box is beside a target box (other).
    *   and reports the adjustment offset so that the two boxes are separated.
    *  
    *   \param other is the second (target) Box to test collision on the horizontal axis with.
    *   \return the offset this Box needs to move in the x axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectSideways(Box &other)
    {
        if (fabs(position_y - other.position_y) * 2.0f >= (m_width + other.m_width))
            return 0.0f;
        if (position_x > other.position_x)
            return std::max<float>(0.0f, other.position_x + (other.m_width / 2.0f) - position_x + (m_width / 2.0f));
        else
            return std::min<float>(0.0f, other.position_x - (other.m_width / 2.0f) - position_x - (m_width / 2.0f));
    }
    
    /** Default ctor
    */
    Box() {}

    /** Basic Box ctor.
    *   \param x is the x coordinate of the box center
    *   \param y is the y coordinate of the box center
    *   \param w is the width of the box
    *   \param h is the height of the box
    */
    Box(float x, float y, float w, float h) 
        : position_x(x), position_y(y), m_width(w), m_height(h) {}
};

