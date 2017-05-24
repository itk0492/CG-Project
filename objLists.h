//
// Created by iroas on 17/05/2017.
//

#ifndef FINAL2_OBJLISTS_H
#define FINAL2_OBJLISTS_H

// Estructura para almacenar los vértices.
typedef struct vertex{
    double x;
    double y;
    double z;
}vertexes;

// Estructura para almacenar las caras a través de aristas.
typedef struct face{
    int v1;
    int v2;
    int v3;
}faces;

typedef struct vertexP{
    double x;
    double y;
}vertexesProj;

int vListCreator(vertexes** vList, char* fileName, int* size);
int fListCreator(faces** fList, char* fileName, int vListSize, vertexes* vList, int* size);
int vListProjCreator(vertexesProj** vListProj, int vListSize);

int addPoint(vertexes** vList, vertexes point, int* size);
int addFace(faces** fList, vertexes* aux, vertexes* vList, int vListSize, int* size);

int searchPoint(vertexes* vList, vertexes point, int size);

void sortVList(vertexes* vList, int vListSize);
void mergeSort(vertexes *vList, int size1, int size2);

int vListProjection(vertexes* vList, int vListSize, vertexesProj** vListProj, double Ez, double Ex, double Ey);

void getMiddle(double** mid, vertexes* vList, int vListSize);

#endif //FINAL2_OBJLISTS_H
