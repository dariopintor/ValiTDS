/***************************************************************************
                          tabu.h  -  description
                             -------------------
    begin                : Ter Jul 29 2003
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

#ifndef TABU_H
#define TABU_H


/**
  *@author Luciano Petinati Ferreira
  */
#include<iostream>
#include "diversos.h"
#include "central.h"
#include "populacao.h"

class tabu {
public: 
	tabu( central ** pctl );
	~tabu();
  int paraTabu(char * linhaCobertura);
  /** Método */
  int toFileTabu ( int nro, char * str, char * arquivo);
  /** Verifica se a cobertura atual melhora a cobertura global mantida pela referencia ao objeto central. */
  int melhora( char * coberturaAtual);
  /** Verifica se a cobertura recem gerada para o individuo identificado por nroIndividuo melhora a cobertura global.
Caso sim deve entrar em tabu retirando coberturas cobertas. */
  int manutencaoTabu( char * coberturaIndividuo, int nroIndividuo);
  int atualizaTabu(char * coberturaIndividuo, int pos);
public: // Public attributes
  /**  */
  central ** ctl;
};

#endif
