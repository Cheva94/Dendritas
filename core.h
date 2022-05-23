#pragma once

double pbc(double coord, const double cell_length);
double rbc(double coord, const double cell_length);
void init(double* lib, double* dep);
void end(double* lib, double* dep, int count, double tSim);
void neutral(double* lib, double* dep, int* count, const int j);
void move(double* lib, double* dep, int* count);
