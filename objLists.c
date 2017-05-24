//
// Created by iroas on 17/05/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "objLists.h"

// Esta función se encarga de cargar los datos del archivo RAW a la lista de vértices
int vListCreator(vertexes** vList, char* fileName, int* size) {
    FILE * f;
    *vList = NULL;
    vertexes aux[3];
    if(!(f=fopen(fileName, "r"))){
        printf("Error while opening file.\n");
        return -1;
    }
    while(!feof(f)){
        fscanf(f, "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &aux[0].x, &aux[0].y, &aux[0].z, &aux[1].x, &aux[1].y, &aux[1].z, &aux[2].x, &aux[2].y, &aux[2].z);
        addPoint(vList, aux[0], size);
        addPoint(vList, aux[1], size);
        addPoint(vList, aux[2], size);
        sortVList(*vList, *size);
    }
    fclose(f);
    return 0;
}

// Esta función se encarga de cargar los datos de caras en la lista de caras
int fListCreator(faces** fList, char* fileName, int vListSize, vertexes* vList, int* size){
    FILE * f;
    *fList=NULL;
    vertexes aux[3];
    if(!(f=fopen(fileName, "r"))){
        printf("Error while opening file.\n");
        return -1;
    }
    while(!feof(f)){
        fscanf(f, "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &aux[0].x, &aux[0].y, &aux[0].z, &aux[1].x, &aux[1].y, &aux[1].z, &aux[2].x, &aux[2].y, &aux[2].z);
        addFace(fList, aux, vList, vListSize, size);
    }
    fclose(f);
    return 0;
}

// Esta función se encarga de alojar memoria para la lista de vertices proyectada
int vListProjCreator(vertexesProj** vListProj, int vListSize){
    vertexesProj* aux=NULL;
    aux=(vertexesProj*)malloc(sizeof(vertexesProj)*vListSize);
    *vListProj=aux;
    return 0;
}

// Esta función se encarga de agregar puntos a la lista de vértices
int addPoint(vertexes** vList, vertexes point, int* size) {
    vertexes* vListAux;
    if((*size)==0){
        ++(*size);
        vListAux=realloc(*vList, ((*size)+1)* sizeof(vertexes));
        *vList=vListAux;
        vList[0][(*size)-1].x=point.x;
        vList[0][(*size)-1].y=point.y;
        vList[0][(*size)-1].z=point.z;
        return 2; //Retorna 2 que significa que se inicializó la lista
    } else if(searchPoint(*vList, point, (*size)) == -1){
        ++(*size);
        vListAux=realloc(*vList, ((*size)+1)* sizeof(vertexes));
        *vList=vListAux;
        vList[0][(*size)-1].x=point.x;
        vList[0][(*size)-1].y=point.y;
        vList[0][(*size)-1].z=point.z;
        return 1; //Retorna 1 que significa que el punto se agregó
    }
    return 0; //Retorna 0 que significa que el punto no fue agregado
}

// Esta función se encarga de agregar los vertices correspondientes a la cara
int addFace(faces** fList, vertexes* aux, vertexes* vList, int vListSize, int* size){
    faces* fListAux;
    ++(*size);
    fListAux=realloc(*fList, ((*size)+1)* sizeof(faces));
    *fList=fListAux;
    fList[0][(*size)-1].v1=searchPoint(vList, aux[0], vListSize);
    fList[0][(*size)-1].v2=searchPoint(vList, aux[1], vListSize);
    fList[0][(*size)-1].v3=searchPoint(vList, aux[2], vListSize);
    return 0;
}

// Esta función se encarga de encontrar un punto en la lista de vértices (Implementa el algoritmo Binary Search)
// Requiere que la lista esté ordenada de mayor a menor, tanto en 'x', como en 'y' y en 'z'
int searchPoint(vertexes* vList, vertexes point, int size) {
    int first, middle, last;
    first=0;
    last=size-1;
    middle=(first+last)/2;
    while(first<=last){
        if(vList[middle].x==point.x){
            if(vList[middle].y==point.y){
                if(vList[middle].z==point.z){
                    return middle;
                } else if (vList[middle].z<point.z){
                    first=middle+1;
                } else if (vList[middle].z>point.z){
                    last=middle-1;
                }
            } else if (vList[middle].y<point.y){
                first=middle+1;
            } else if (vList[middle].y>point.y){
                last=middle-1;
            }
        } else if (vList[middle].x<point.x){
            first=middle+1;
        } else if (vList[middle].x>point.x){
            last=middle-1;
        }
        middle = (first + last)/2;
    }
    return -1;

}

// Esta función ordena la lista de vértices usando mergeSort
void sortVList(vertexes* vList, int vListSize){
    if(vListSize == 1)
        return;

    int size1=vListSize/2, size2=vListSize-size1;
    sortVList(vList, size1);
    sortVList(vList+size1, size2);
    mergeSort(vList, size1, size2);
    return;
}

// El criterio para el orden es de menor a mayor dado el punto X
void mergeSort(vertexes *vList, int size1, int size2) {
    vertexes temp[size1+size2];
    int ptr1=0, ptr2=0;

    while (ptr1+ptr2 < size1+size2) {
        if (ptr1 < size1 && vList[ptr1].x <= vList[size1+ptr2].x || ptr1 < size1 && ptr2 >= size2) {
            if(vList[ptr1].x==vList[size1+ptr2].x){
                if(vList[ptr1].y<=vList[size1+ptr2].y){
                    if (vList[ptr1].y==vList[size1+ptr2].y){
                        if (vList[ptr1].z<=vList[size1+ptr2].z){
                            temp[ptr1 + ptr2] = vList[ptr1++];
                        } else{
                            temp[ptr1+ptr2] = vList[size1+ptr2++];
                        }
                    } else{
                        temp[ptr1 + ptr2] = vList[ptr1++];
                    }
                } else {
                    temp[ptr1+ptr2] = vList[size1+ptr2++];
                }
            } else {
                temp[ptr1 + ptr2] = vList[ptr1++];
            }
        }
        if (ptr2 < size2 && vList[size1+ptr2].x < vList[ptr1].x || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1+ptr2] = vList[size1+ptr2++];
    }

    for (int i=0; i < size1+size2; i++)
        vList[i] = temp[i];
}

// Esta función se encarga de hacer la proyección de perspectiva
// Aquí se presenta el problema, con la v3 el objeto se vuelve una línea al rotarlo 90°
// Con la v2 el objeto se alarga
// Con la v1 el objeto se aprecia desde una perspectiva extraña y no se aprecian con exactitud las traslaciones y escalas
int vListProjection(vertexes* vList, int vListSize, vertexesProj** vListProj, double Ez, double Ex, double Ey){
    for (int i = 0; i < vListSize; ++i) {
        /*
        // v1
        vListProj[0][i].x=((Ez*(vList[i].x-Ex))/(Ez+vList[i].z))+Ex;
        vListProj[0][i].y=((Ez*(vList[i].y-Ey))/(Ez+vList[i].z))+Ey;
         */
        /*
        // v2
        vListProj[0][i].x=(vList[i].x)/(1-(vList[i].z/Ez));
        vListProj[0][i].y=(vList[i].y)/(1-(vList[i].z/Ez));
         */
        // v3
        vListProj[0][i].x=(vList[i].x*Ez)/10;
        vListProj[0][i].y=(vList[i].y*Ez)/10;
    }
}

// Esta función se encarga de obtener el centro de la figura dados los puntos 'x', 'y' y 'z'
void getMiddle(double** mid, vertexes* vList, int vListSize){
    double* aux;
    aux=realloc(*mid, 3* sizeof(double));
    *mid=aux;
    double minz, miny, maxz, maxy;
    miny=vList[0].y;
    maxy=vList[0].y;
    minz=vList[0].z;
    maxz=vList[0].z;
    for (int i = 0; i < vListSize; ++i) {
        if(maxy<vList[i].y)
            maxy=vList[i].y;
        if(miny>vList[i].y)
            miny=vList[i].y;
        if(maxz<vList[i].z)
            maxz=vList[i].z;
        if(minz>vList[i].z)
            minz=vList[i].z;
    }
    mid[0][0]=vList[0].x+((vList[vListSize-1].x-vList[0].x)/2);
    mid[0][1]=miny+((maxy-miny)/2);
    mid[0][2]=minz+((maxz-minz)/2);
    return;
}
