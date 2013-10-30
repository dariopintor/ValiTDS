/***************************************************************************
                          l_string.h  -  description
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

#ifndef L_STRING_H
#define L_STRING_H


/**Tipo String próprio.
  *@author Luciano Petinati Ferreira
  */
#include<iostream>
#include<ostream>
#include"diversos.h"

using namespace std;

class l_string {

public:
	l_string();
	~l_string();
  /** Sobrecarga do operador de atribuição. */
  l_string operator=(l_string dir);
  /** Sobrecarga de operador atribuição para l_string com char *. */
  l_string operator=(char * dir);
  /** Sobrecarga de extrator <<. */
  friend ostream &operator<<(ostream & canal, l_string obj);
  /** Construtor de cópia - necessário devido a classe alocar memória dinamicamente na construção do objeto. */
   l_string(const l_string & obj);
  /** Método para obter char * a partir de l_string. */
  char * getValor();
  /** Método para limpar caracteres em branco das extremidades de um l_string. */
  int trim();
  /** Método que reduz o valor do string para as dimensões passadas por argumento.
inic >= 0
fim <= tamanho do string == tam. */
  int substring( int inic, int fim);
  /** Sobrecarga de operador de concatenação com l_string. */
  l_string operator+ ( l_string dir );
  /** Sobrecarga de operador de concatenação com char *. */
  l_string operator+ ( char * dir );
//private: // Private attributes
  /** tam armazena o tamanho para valor */
  long tam;
  /** valor possui o conteúdo do string */
  char * valor;

};

#endif
