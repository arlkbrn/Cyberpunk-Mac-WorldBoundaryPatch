#pragma once
namespace WorldBoundaryPatch 
{
using gameWorldBoundarySystemTick_t = void(*)(void*, void*, void*, void*);
void fake_Tick(void*, void*, void*, void*);

int entry(); 
}