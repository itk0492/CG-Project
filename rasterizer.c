//
// Created by iroas on 17/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "rasterizer.h"

// Esta función se encarga de alojar memoria dependiendo del tamaño filas del raster.
int*** createRasterX(int rows, int columns, int pixels){
    int ***ras=(int***)malloc(sizeof(int**)*rows);
    int i;
    for(i=0;i<rows;i++){
        ras[i]= createRasterY(columns, pixels);
    }
    return ras;
}

// Esta función se encarga de alojar memoria dependiendo del tamaño de columnas del raster.
int** createRasterY(int columns, int pixels){
    int **ras=(int**)malloc(sizeof(int*)*columns);
    int i;
    for(i=0;i<columns;i++){
        ras[i]= createRasterP(pixels);
    }
    return ras;
}

// Esta función se encarga de alojar memoria para el formato de color de cada pixel.
int* createRasterP(int pixels){
    int *ras=(int*)malloc(sizeof(int)*pixels);
    int i;
    for(i=0;i<pixels;i++){
        ras[i]=0;
    }
    return ras;
}

//Esta función se encarga de imprimir los colores de los pixeles del raster en la terminal en formato RGB.
void printRasterRGB(int ***raster, int columns, int rows){
    printf("P3\n1920 1080\n255\n\n");
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            printf("%i %i %i\n", raster[i][j][0], raster[i][j][1], raster[i][j][2]);
        }
    }
    return;
}

// Esta función se encarga de imprimir el raster directamente a un archivo con pixeles en formato RGB.
void printRaster2FileRGB(char* fileName, int ***raster, int columns, int rows){
    FILE* f;
    f=fopen(fileName, "w+");
    fprintf(f, "P3\n1920 1080\n255\n\n");
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            fprintf(f, "%i %i %i\n", raster[i][j][0], raster[i][j][1], raster[i][j][2]);
        }
    }
    fclose(f);
    return;
}

// Esta función se encarga de limpiar el raster (cambiando los pixeles a color negro en formato RGB).
void cleanRasterRGB(int ***raster, int columns, int rows){
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            raster[i][j][0]=0;
            raster[i][j][1]=0;
            raster[i][j][2]=0;
        }
    }
    return;
}

// Esta función se encarga de hacer el cálculo de las líneas a dibujar
void bresenham(int ***raster, int x1, int y1, int x2, int y2, int c1, int c2, int c3){
    if(x1<0 || x2<0 || y1<0 || y2<0)
        return;
    if(x1>=1920 || x2>=1920 || y1>=1080 || y2 >=1080)
        return;
    int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
    int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    for(;;) {
        raster[y1][x1][0] = c1;
        raster[y1][x1][1] = c2;
        raster[y1][x1][2] = c3;
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawFace2Raster(int*** raster, faces* fList, int fListSize, vertexesProj* vListProj){
    for (int i = 0; i < fListSize; ++i) {
        bresenham(raster, (int)vListProj[fList[i].v1].x, (int)vListProj[fList[i].v1].y, (int)vListProj[fList[i].v2].x, (int)vListProj[fList[i].v2].y, 255, 255, 255);
        bresenham(raster, (int)vListProj[fList[i].v2].x, (int)vListProj[fList[i].v2].y, (int)vListProj[fList[i].v3].x, (int)vListProj[fList[i].v3].y, 255, 255, 255);
        bresenham(raster, (int)vListProj[fList[i].v3].x, (int)vListProj[fList[i].v3].y, (int)vListProj[fList[i].v1].x, (int)vListProj[fList[i].v1].y, 255, 255, 255);
    }
}