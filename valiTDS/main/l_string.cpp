/***************************************************************************
                          l_string.cpp  -  description
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

#include "l_string.h"
#include <iostream>

l_string::l_string(){
  //cout << "\nConstruindo string...";
  tam = 0;
  valor = NULL;
}
l_string::~l_string(){
  //cout << "\nDestruindo string...";
  //delete valor;
  desalocaCharPtr(&valor, tam, "l_string::~l_string()", "valor");
  valor = NULL;
  tam = 0;
}
/** Sobrecarga do operador de atribuição. */
l_string l_string::operator=(l_string dir){
  //cout << "\nAtribuindo string...";
  //delete valor;
  if (valor)
    desalocaCharPtr(&valor, tam, "l_string::operator=", "valor");
  tam = dir.tam;
  //valor = new char(tam);
  alocaCharPtr(&valor, tam, "l_string::operator=", "valor");
  strcpy (valor, dir.valor);
  return *this;
}
/** Sobrecarga de operador atribuição para l_string com char *. */
l_string l_string::operator=(char * dir){
  //cout << "\nAtribuindo string...";
  //delete valor;
  if (valor)
    desalocaCharPtr(&valor, tam, "l_string::operator=", "valor");
  tam = strlen(dir) + 1;
  //valor = new char(tam);
  alocaCharPtr(&valor, tam, "l_string::operator=", "valor");
  strcpy (valor, dir);
  return *this;

}
/** Sobrecarga de extrator <<. */
ostream &operator<<(ostream & canal, l_string obj){
  canal << obj.valor;
}
/** Construtor de cópia - necessário devido a classe alocar memória dinamicamente na construção do objeto. */
l_string::l_string(const l_string & obj){
  valor = NULL;
  tam = obj.tam;
  alocaCharPtr(&valor, tam, "l_string::operator=", "valor");
  strcpy(valor, obj.valor);
}
/** Método para obter char * a partir de l_string. */
char * l_string::getValor(){
  return valor;
}
/** Método para limpar caracteres em branco das extremidades de um l_string. */
int l_string::trim(){
   if (valor == NULL) return 0;
   l_string res;
   res = "";
   char * aux = valor;
   for ( ; *aux++ == ' '; );
   *aux--;
   int fimIndex = 0;
   for (fimIndex = tam-4; *(aux+fimIndex) == ' '; fimIndex --) ;;
   *(aux+fimIndex+1) = '\0';
   res = aux;
   *this = res;
   res.~l_string();
   aux = NULL;
   return true;
}
/*
void trim(char ** str)
{
/** /
   char *res;
   char *aux = *str;
   int t = strlen( * str) + 1;
   int ct; // espacos

   if (t == 0)
      return;

   for (ct = t; *aux++ == ' '; ct--)
      ;

   for (aux = *str + t; *aux-- == ' '; ct--)
      ;
   aux++;

   for (res = (*str) + ct; ct >= 0; res-- = aux--, ct--)
      ;

   return;
/* /
   int com = -1, fim = -1, tam = -1, i=0;
   int t = strlen( * str) + 1;
   char * aux = NULL;
   alocaCharPtr( &aux, t, "trim", "aux");
   memset(aux, '\0', t);
   strcpy(aux, * str);

   for(i=0; com == -1; i++){
      if (aux[i] != ' ') com = i;   // fim for
      }
   strcpy(aux, aux+com);
   tam = strlen(aux);
   for(i=tam-1;fim ==-1;i--){
      if ((aux[i] != ' ')&&(aux[i]!='\n')) fim = i+1;  //fim for
      }

  aux[fim] = '\0';
  strcpy( *str, aux);
  desalocaCharPtr( &aux, t, "trim", "aux");
  /** /
}// fim trim

*//** Método que reduz o valor do string para as dimensões passadas por argumento.
inic >= 0
fim <= tamanho do string == tam. */
int l_string::substring( int inic, int fim){
  if ( (inic <0 ) || (fim > tam) ){
    sprintf(ErrorText, "<tdsgen> l_string::substring - ERRO - inic=%d , fim=%d , tam=%d - inic ou fim fora de [0,%d)", inic, fim, tam, tam);
    erro(ErrorText, 1);
    }
  *(valor + fim) = '\0';
  l_string temp;
  temp = valor;
  *this = temp;
  temp.~l_string();
  return true;
}
/** Sobrecarga de operador de concatenação com char *. */
l_string l_string::operator+ ( char * dir ){
  char * char_temp = NULL;
  int tam_temp = tam + strlen(dir) + 1;
  alocaCharPtr(& char_temp, tam_temp , "l_string::operator+", "char_temp" );
  sprintf (char_temp, "%s%s", valor, dir);
  l_string temp;
  temp = char_temp;
  desalocaCharPtr(& char_temp, tam_temp , "l_string::operator+", "char_temp" );
  return temp;
}
/** Sobrecarga de operador de concatenação com l_string. */
l_string l_string::operator+ ( l_string dir ){
  char * char_temp = NULL;
  int tam_temp = tam + dir.tam + 1;
  alocaCharPtr(& char_temp, tam_temp , "l_string::operator+", "char_temp" );
  sprintf (char_temp, "%s%s", valor, dir.valor);
  l_string temp;
  temp = char_temp;
  desalocaCharPtr(& char_temp, tam_temp , "l_string::operator+", "char_temp" );
  return temp;

}
