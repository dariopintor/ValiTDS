/***************************************************************************
                          diversos.h  -  description
                             -------------------
    begin                : Dom Jul 6 2003
    copyright            : (C) 2003 by Luciano Petinati Ferreira
    email                : petinat@inf.ufpr.br
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DIVERSOS_H
#define DIVERSOS_H 1

/**
  *@author Luciano Petinati Ferreira
  */

static char ErrorText[500];
static char Comando[500];
static long total_alocado;

#define BARRA "/"

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include"except.h"
#include "time.h"
#include"l_string.h"

//Protótipos das funções. Obs.: Todas devem ser inline's.

void  erro   (char * str, int fim );
/** Função usada para obter segundos referentes a data e hora atuais. */
long getSecs();
int toFile(char * arquivo, char * conteudo);
int appendToFile(char * arquivo, int contador, char * conteudo);
int numberOf(char * str, char busca);
int indexOf(char * str, char * busca);
int indexOf(char * str, char busca);
void trim(char ** str);
char generateChar(char * seletivo);
void desalocaCharPtr (char ** ptr, char * metodo, char * name);
void desalocaCharPtr (char ** ptr, int size, char * metodo, char * name);
void alocaCharPtr( char ** ptr, int size, char * metodo, char * name);
int nroEspacos(int tamPopulacao);
int cobre(char * cobertura1, char * cobertura2);


void initGenRand();
unsigned long genrand();
void sgenrand(unsigned long seed);

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

#endif

