#pragma once

void init(double* lib, double* dep);
double pbc(double coord, const double cell_length);
double rbc(double coord, const double cell_length);
void move(double* lib);
double update(double* lib, double* dep, int* count);
void end(double* lib, double* dep, double tSim, double wall, double* flopGral); //, double* flopNeu);
