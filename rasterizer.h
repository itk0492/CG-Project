//
// Created by iroas on 17/05/2017.
//

#ifndef FINAL2_RASTERIZER_H
#define FINAL2_RASTERIZER_H

#include "objLists.h"

int*** createRasterX(int rows, int columns, int pixels);
int** createRasterY(int columns, int pixels);
int* createRasterP(int pixels);

void printRasterRGB(int*** raster, int columns, int rows);
void printRaster2FileRGB(char* fileName, int*** raster, int columns, int rows);
void cleanRasterRGB(int*** raster, int columns, int rows);

void bresenham(int*** raster, int x1, int y1, int x2, int y2, int c1, int c2, int c3);
void drawFace2Raster(int*** raster, faces* fList, int fListSize, vertexesProj* vListProj);

#endif //FINAL2_RASTERIZER_H
