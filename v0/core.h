#pragma once

double pbc(double coord, const double cell_length);
double rbc(double coord, const double cell_length);
void init(double* lib, double* dep);
void end(double* lib, double* dep, double tSim, double wall, double gFlopNeu, double gFlopGral);
double neutral(double* lib, double* dep, int* count, const int j);
void move(double* lib, double* dep, int* count, double* flopGral, double* flopNeu);
