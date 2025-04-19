#pragma once
#include "managers/collisionManager.hpp"

/// @brief sprawdza kolizje pomiedzy pociskami, asteroidam i graczami
class HitChecker : private CollisionManager
{
public:
    /// @brief sprawdzenie kolizji
    static void check();
};