#pragma once

void init(float* lib, float* dep);
float pbc(float x);
float rbc(float y);
void move(float* lib);
float update(float* lib, float* dep, unsigned int* count, unsigned int* countAux);
void end(float* lib, float* dep, float tSim, double wall, float* pflops);
