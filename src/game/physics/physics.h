#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "../../structs/charater/charater.h"


void ApplyFloorPhysics(MainCharater* character);

#endif