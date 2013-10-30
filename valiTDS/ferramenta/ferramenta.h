/***************************************************************************
                          ferramenta.h  -  description
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
#include "diversos.h"
#ifndef FERRAMENTA_H
#define FERRAMENTA_H


/**
  *@author Luciano Petinati Ferreira
  */

#define PATH_BASICO       ".:/bin:/usr/bin:/usr/local/bin:/usr/sbin:/usr/local/sbin:/usr/bin/X11:/usr/openwin/bin"



/** / //UFPR
#define PATH_PARTICULAR   "/home/pos/petinati/Scripts:/home/pos/petinati/geradorCT/geradorCT/interface:/home/pos/petinati/geradorCT/geradorCT/exe"
#define PATH_POKETOOL     "/home/especial/auri/ferramentas/poketool/bin"
#define PATH_PROTEUM      "/home/especial/auri/ferramentas/proteum1.4.1/LINUX/bin"
#define SET_POKEBIN       "export POKEBIN=/home/especial/auri/ferramentas/poketool/bin"
#define SET_POKETABS      "export POKETABS=/home/especial/auri/ferramentas/poketool/bin/poketabs"
#define SET_LITABS        "export LITABS=/home/especial/auri/ferramentas/poketool/bin/litabs"

#define SET_PROTEUM_VARS  "export PROTEUM14HOME=/home/especial/auri/ferramentas/proteum1.4.1/LINUX/bin"

/*/  //PETFER
#define PATH_PARTICULAR   "/home/petinati/scripts"

#define PATH_POKETOOL     "/home/installLnx/ferramentas/poketool/bin"
#define PATH_PROTEUM      "/home/installLnx/ferramentas/Proteum/proteum1.4.1/LINUX/bin"

#define SET_POKEBIN       "export POKEBIN=/home/installLnx/ferramentas/poketool/bin"
#define SET_POKETABS      "export POKETABS=/home/installLnx/ferramentas/poketool/bin/poketabs"
#define SET_LITABS        "export LITABS=/home/installLnx/ferramentas/poketool/bin/litabs"

#define SET_PROTEUM_VARS  "export PROTEUM14HOME=/home/installLnx/ferramentas/Proteum/proteum1.4.1/LINUX/bin"
/**/

#define SET_POKETOOL_VARS SET_POKEBIN";"SET_POKETABS";"SET_LITABS

#define SET_PATH_POKETOOL "export PATH="PATH_BASICO":"PATH_PARTICULAR":"PATH_POKETOOL
#define SET_PATH_PROTEUM "export PATH="PATH_BASICO":"PATH_PARTICULAR":"PATH_PROTEUM

#define SET_POKETOOL SET_POKETOOL_VARS";"SET_PATH_POKETOOL";"
#define SET_PROTEUM  SET_PROTEUM_VARS";"SET_PATH_PROTEUM";"

#define VALIMPI_ROOT "/home/asano/IC/ValiPAR/MPI"
#define VALIMPI_BIN VALIMPI_ROOT"/vali_exec/:"VALIMPI_ROOT"/vali_eval/:"VALIMPI_ROOT"/vali_inst/:"VALIMPI_ROOT"/vali_elem/"
#define SET_VALIMPI "export PATH=$PATH:"VALIMPI_BIN";"

//#include "diversos.h"
#include "individuo.h"
#include "central.h"
class ferramenta {
public:
  /** No descriptions */
   ferramenta(central ** parCtl);
	~ferramenta();
  /** Método usado para inicar a ferramenta adequada baseado nas informações de controle contidas em ctl. */
  int prepareTool();
  /** Método usado para obter a quantidade de elementos requeridos para
critérios suportados pela ferramenta Proteum. */
  double obtemElementosRequeridosProteum();
  /** No descriptions */
  double obtemElementosRequeridosValiMPI();
  /** Método usado para obter a quantidade de elementos requeridos pelo critério configurado. */
  double obtemElementosRequeridos();
  /** Método usado para avaliar o nro-esimo indivíduo da população.
 */
  int evaluateIndividual(int nro);
  /** Método usado para obter linha de cobertura que contém o desempenho do individuo
perante aos elementos requeridos. */
  int obtemCoberturaValiMPI(char ** linhaCobertura, int tamLinhaCobertura);
  /** Executa a proteum para um determinado caso de teste da população. */
  int evaluateIndividualProteum( int nro );
  /** Método utilizado para obter a cobertura de um determinado caso de teste.
 */
  int obtemCoberturaProteum(char ** linhaCobertura, int tamLinhaCobertura);
public: // Public attributes
  /** Ponteiro para objeto tipo central, e serve para controlar a execução do framework. */
  central ** ctl;
};

#endif
