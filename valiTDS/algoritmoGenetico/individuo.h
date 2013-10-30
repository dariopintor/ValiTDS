/***************************************************************************
                          individuo.h  -  description
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
#ifndef INDIVIDUO_H
#define INDIVIDUO_H


/**
  *@author Luciano Petinati Ferreira
  */
//#include "diversos.h"
#include "central.h"
#include <math.h>


class individuo {
public:
	individuo(central ** parCtl);
	~individuo();
  /** Método que atribui valor para a representação de um indivíduo. */
  int setRepresentacao (char * valor);
  /** Método para recuperar o pos-esimo indivíduo da população. */
  int load (int pos);
  /** Método para criar um novo indivíduo baseado na linha do arquivo e na configuração fornecida ao framework. */
  int novo (char * linha);
  /** Método para criar um novo indivíduo aleatório. */
  int novo();

  /** Método que recupera o respectivo valor do bloco passado como argumento.  */
  double decode_block_float ( char * bloco );
  /** Método usado para formatar um bloco a partir de um valor passado por argumento. */
  int forma_block_float (char ** res, int limite, char * lido);
  /** Método usado para formatar um bloco float aleatoriamente. */
  int forma_block_float_random(char ** res, int limite);

  /** Método que recupera o respectivo valor do bloco passado como argumento. */
  double decode_block_double (char * bloco);
  /** Método usado para formatar um bloco a partir de um valor passado por argumento. */
  int forma_block_double (char ** res, int limite, char * lido);
  /** Método usado para formatar um bloco double aleatoriamente. */
  int forma_block_double_random(char ** res, int limite);

  /** Método que recupera o respectivo valor do bloco passado como argumento. */
  int decode_block_int (char * bloco);
  /** Método usado para formatar um bloco a partir de um valor passado por argumento. */
  int forma_block_int (char ** res, int limite, char * lido);
  /** Método usado para formatar um bloco aleatoriamente. */
  int forma_block_int_random(char ** res, int limite);

  /** Método usado para formatar um bloco string a partir de um valor passado por argumento. */
  int forma_block_string(char ** res, int limite, char * lido);
  /** Método usado para formatar um bloco string aleatoriamente. */
  int forma_block_string_random(char ** res, int limite);


public: // Public attributes
  /** Ponteiro para objeto tipo central, e serve para controlar a execução do framework. */
  central ** ctl;
  /** Atributo que contem a representação dos indivíduos. */
  char * representacao;
};

#endif
