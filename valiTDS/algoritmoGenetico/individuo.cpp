/***************************************************************************
                          individuo.cpp  -  description
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

#include "individuo.h"

individuo::individuo(central ** parCtl){
   //cout << "\nConstruindo individuo...";
   ctl = parCtl;

   representacao = NULL;
   alocaCharPtr( &representacao,(int) ((*ctl)->tamanhoIndividuo + 10), "individuo", "representacao");
}

individuo::~individuo(){
   //cout << "\nDestruindo individuo...";
   desalocaCharPtr( &representacao, (int) ((*ctl)->tamanhoIndividuo + 10), "~individuo", "representacao");
   //ctl = NULL;
}
//_________________________________________________________________

/** Método para criar um novo indivíduo aleatório. */
int individuo::novo(){
   char * bloco = NULL;
   int nroBloco = strlen( (*ctl)->formatoIndividuo );
   int blocoTam = (int) ((*ctl)->tamanhoIndividuo );
   memset( representacao, '\0', (int) ((*ctl)->tamanhoIndividuo + 10) );
   
   alocaCharPtr( & bloco , blocoTam +2, "novo", "bloco");
    	
   for (int i=0; i< nroBloco; i++)
   {
      memset( bloco, '\0', blocoTam + 2);

      switch( (*ctl)->formatoIndividuo[i] )
     	{
        	case 'I':
      	  {
       	    forma_block_int_random( &bloco, blocoTam);
       	    break;
      	  }
        	case 'D':
      	  {
       	    forma_block_double_random( &bloco, blocoTam);
       	    break;
      	  }
        	case 'F':
      	  {
       	    forma_block_float_random( &bloco, blocoTam);
       	    break;
      	  }
        	case 'S':
      	  {
       	    forma_block_string_random( &bloco, blocoTam);
       	    break;
      	  }
        	case 'C':
      	  {
       	    bloco[0] = generateChar( (*ctl)->tipoString );
       	    bloco[1] = '\0';
      	  }
        	default:
      	  {
       	    printf( "\nFormato : %c\nFormato de tipo invalido\n\r",(*ctl)->formatoIndividuo[i] );
      	  }
     	}// fim switch
      strcat(representacao,bloco);
   } // fim for
   desalocaCharPtr( & bloco , blocoTam +2, "novo", "bloco");
   
   return true;
}

//_________________________________________________________________

/** Método para criar um novo indivíduo baseado na linha do arquivo e na configuração fornecida ao framework. */
int individuo::novo (char * linha){
   int numArgumentos = strlen( (*ctl)->formatoIndividuo );
   int virg = -1;
   char * blocoLinha = NULL, * bloco = NULL;
   alocaCharPtr( & blocoLinha , (int) ((*ctl)->tamanhoIndividuo + 5), "novo", "blocoLinha");
   alocaCharPtr( & bloco , (int) ((*ctl)->tamanhoIndividuo + 5), "novo", "bloco");
    	
   memset( representacao, '\0', (int) ((*ctl)->tamanhoIndividuo + 10) );

   for(int cont = 0; cont < numArgumentos; cont++)
   {
      memset( blocoLinha, '\0', (int) ((*ctl)->tamanhoIndividuo + 5) );
      memset( bloco     , '\0', (int) ((*ctl)->tamanhoIndividuo + 5) );

      if( ( virg = indexOf( linha, ',' ) ) != -1 )
     	strncpy(blocoLinha, linha, virg);
      else
     	strcpy(blocoLinha, linha);
      trim ( &  blocoLinha);
      strcpy( linha, linha + virg + 1 );

      switch((*ctl)->formatoIndividuo[ cont ])
     {
        case 'I':
        {
           forma_block_int( &bloco, (*ctl)->tamanhoTipo(cont) + 1, blocoLinha);
           //printf("\nRecuperado Arg %d - Integer '%s'", cont, bloco);
           break;
        }

        case 'D': {
           forma_block_double( & bloco, (*ctl)->tamanhoTipo(cont) + 1, blocoLinha);
           //printf("\nRecuperado Arg %d - Double '%s'", cont, bloco);
           break;
        }
        	case 'F': {
         	  forma_block_float( & bloco, (*ctl)->tamanhoTipo(cont) + 1, blocoLinha);
         	  //printf("\nRecuperado Arg %d - Float '%s'", cont, bloco);
         	  break;
        	}
        	case 'S': {
         	  forma_block_string( & bloco, (*ctl)->tamanhoTipo(cont) + 1, blocoLinha);
         	  //printf("\nRecuperado Arg %d - String '%s'", cont, bloco);
         	  break;
        	}
        	case 'C':
      	  {
       	    strncpy(bloco, blocoLinha,1);
       	    break;
      	  }
     	}// fim switch
      strcat(representacao, bloco);
   }// fim for
   desalocaCharPtr( & blocoLinha , (int) ((*ctl)->tamanhoIndividuo + 5), "novo", "blocoLinha");
   desalocaCharPtr( & bloco , (int) ((*ctl)->tamanhoIndividuo + 5), "novo", "bloco");
   //sprintf(ErrorText, "individuo recuperado : %s", representacao);
   //cout << ErrorText;
   return true;

}

//_________________________________________________________________

/** Método para recuperar o pos-esimo indivíduo da população.
pos deve variar de 0 até tamanho da população - 1.
*/
int individuo::load (int pos){
   int i = 0;
   char * gene = NULL, * geneAux = NULL;
   FILE * ptrPopulation = NULL;

   ptrPopulation = fopen((*ctl)->arquivoPopulacao, "r");
   if(ptrPopulation == NULL){
      sprintf(ErrorText,"aqui nao abriu o arquivo de populacao : %s", (*ctl)->arquivoPopulacao);
      erro(ErrorText,1);
   }
   if(pos >= (*ctl)->tamanhoPopulacao){
      sprintf(ErrorText,"Pos, %d, extrapolou tamanho da populacao %f", pos, (*ctl)->tamanhoPopulacao);
      erro(ErrorText ,1);
   }

   alocaCharPtr( &gene, (int) ((*ctl)->tamanhoIndividuo + 10), "load", "gene");
   alocaCharPtr( &geneAux, (int) ((*ctl)->tamanhoIndividuo + 10), "load", "geneAux");

   for (i = 0; i <= pos; i++)
   {
     // cout << "\n ind nro " << i;
      if (pos == 14)
         pos+=0;

      memset(gene, '\0', (int) ((*ctl)->tamanhoIndividuo + 10));
      try{
         fgets(gene, (int) ((*ctl)->tamanhoIndividuo + 10), ptrPopulation);
      }
      catch(...){
         erro("Estouro de memoria ao tentar recuperar individuos do arquivo de populacao para var gene, metodo load",1);
      }

   }// fim for

   trim ( & gene);
   try{
      i = indexOf(gene, ':') + 1;
      strcpy(geneAux, gene + i );
      trim ( & geneAux);
      setRepresentacao(geneAux);
   }
   catch(...){
      erro("Estouro de memoria ao tentar recuperar individuo da linha do arquivo de populacao , metodo load",1);
   }

   desalocaCharPtr( &gene, (int) ((*ctl)->tamanhoIndividuo + 10), "load", "gene");
   desalocaCharPtr( &geneAux, (int) ((*ctl)->tamanhoIndividuo + 10), "load", "geneAux");

   fclose(ptrPopulation);
   return true;
}

//_________________________________________________________________

/** Método que atribui valor para a representação de um indivíduo. */
int individuo::setRepresentacao (char * valor){
   int tam = strlen(valor);
   if (tam < 0) erro("setRepresentacao, erro no valor passado, tam<0...", 1);
   if (tam > (*ctl)->tamanhoIndividuo) erro ("Novo valor p/representacao de indiv estrapolou a padrao...", 1);
   strcpy(representacao, valor);
   return true;
}


//_________________________________________________________________

/** Método que recupera o respectivo valor do bloco passado como argumento. */
int individuo::decode_block_int (char * bloco){
   return atoi (bloco);
}
//_________________________________________________________________

/** Método usado para formatar um bloco a partir de um valor passado por argumento. */
int individuo::forma_block_int (char ** res, int limite, char * lido){
   int tam = 0;
   char aux[20], numero[10];
   memset(aux     , '\0', 20);
   memset(numero  , '\0', 10);
   strcpy( aux, "+00000");
   trim ( & lido);
   if ( (lido[0] == '-') || (lido[0] == '+') )
   {
      aux[0] = lido[0];
      lido++;
   }
   trim ( & lido);
   strcpy (numero, lido);
   tam = strlen(numero);
   strcpy(aux + (6-tam), numero);	
   memset( * res, '\0', limite);
   if (limite > (int) strlen(aux))
   strcpy( * res, aux);
   else erro("Estouro de tamanho gerando inteiro randomicamente",1);
   return true;
}

//_________________________________________________________________

/** Método usado para formatar um bloco aleatoriamente. */
int individuo::forma_block_int_random(char ** res, int limite)
{
  int tam = 0;
   char * aux = NULL, * numero = NULL;
   alocaCharPtr( & numero  , 20, "forma_block_int_random", "numero");
   alocaCharPtr( & aux, 10, "forma_block_int_random", "aux");
	
  strcpy( aux, "+00000");
  int num = 0;
  if ((*ctl)->tamanhoMinimoInteiro < 0)
  {
     int sinal = genrand()%2;                    //[0+,1-]
     if(sinal == 1) // -
    	{
     	  num = ( genrand() % ( ( -1 * (*ctl)->tamanhoMinimoInteiro ) +1 ) );
     	  aux[0] = '-';
    	}
     else //+
    	num = ( genrand() % ( (*ctl)->tamanhoMaximoInteiro + 1 ) );
  }
  else
  num = ( genrand() % (int)((*ctl)->variacaoInteiro) ) + (*ctl)->tamanhoMinimoInteiro;
  //printf("dados - %d %d %d %d\n",num,(*ctl)->tamanhoMinimoInteiro,(*ctl)->tamanhoMaximoInteiro,(*ctl)->variacaoInteiro);
  sprintf(numero, "%d", num);
  trim ( & numero);
  tam = strlen(numero);
  strcpy(aux + (6-tam), numero);
  memset( * res, '\0', limite);
  if (limite >= (int) strlen(aux))
  strcpy( * res, aux);
  else erro("Estouro de tamanho gerando inteiro randomicamente",1);
    
   desalocaCharPtr( & numero  , 20, "forma_block_int_random", "numero");
   desalocaCharPtr( & aux, 10, "forma_block_int_random", "aux");
   
  return 1;
}// fim forma_block_int_random


//_________________________________________________________________

/** Método que recupera o respectivo valor do bloco passado como argumento. */
double individuo::decode_block_double (char * bloco){
   double res = 0;
   int pos_E  = -1, mant = 1;
   char * mantissa = NULL, * numero = NULL;
   alocaCharPtr( & numero  , 20, "decode_block_double", "numero");
   alocaCharPtr( & mantissa, 10, "decode_block_double", "mantissa");


   trim ( & bloco);
   pos_E = indexOf(bloco, 'E');
   strcpy( numero, bloco );
   if(pos_E != -1)
   {
      strncpy(numero, bloco, pos_E);
      strcpy(mantissa, bloco + pos_E + 1);
      mant = atoi(mantissa);

   }// fim pos_E

   res = atoi(numero);
   res *= pow(10, mant );

   alocaCharPtr( & numero  , 20, "decode_block_double", "numero");
   alocaCharPtr( & mantissa, 10, "decode_block_double", "mantissa");
   return res;
}

//_________________________________________________________________

/** Método usado para formatar um bloco a partir de um valor passado por argumento. */
int individuo::forma_block_double (char ** res, int limite, char * lido){
   int tam = 0;
   int pos_E = -1;
   char aux[20], mantissa[10], aux_mant[10], numero[10];
   memset(aux     , '\0', 20);
   memset(mantissa, '\0', 10);
   memset(aux_mant, '\0', 10);
   memset(numero  , '\0', 10);
   strcpy( aux, "+00000");
   strcpy( aux_mant, "+000");
   strcpy( mantissa, "000");
    	
   trim ( & lido);
   if ( (lido[0] == '-') || (lido[0] == '+') )
   {
      aux[0] = lido[0];
      lido++;
   }
   trim ( & lido);
   pos_E = indexOf(lido, 'E');
   if( pos_E != -1)
   {                                            //existe mantissa
   strncpy(numero  , lido,  pos_E);
   lido += pos_E;
   if ( (lido[0] == '-') || (lido[0] == '+') )
  	{
   	  aux_mant[0] = lido[0];
   	  lido++;
  	}
   trim ( & lido);
   strcpy (mantissa, lido);
    }// fim if tem E
    else strcpy (numero, lido);
    tam = strlen(numero);
    strcpy(aux      + (6-tam), numero);
    tam = strlen(mantissa);
    strcpy(aux_mant + (4-tam), mantissa);
     	
    strcat(aux, aux_mant);
    memset( * res, '\0', limite);
    if (limite > (int) strlen(aux))
    strcpy( * res, aux);
    else
    erro("Estouro de tamanho recuperando double",1);
    return true;
 }// fim forma_block_double
//_________________________________________________________________

/** Método usado para formatar um bloco double aleatoriamente. */

int individuo::forma_block_double_random(char ** res, int limite)
{
  int tam = 0, num = 0, mant = 0, sinal = genrand()%4;         //[0++,1+-,2-+,3--]
  char aux[20], mantissa[10], aux_mant[10], numero[10];
  memset(aux     , '\0', 20);
  memset(mantissa, '\0', 10);
  memset(aux_mant, '\0', 10);
  memset(numero  , '\0', 10);
	
  switch (sinal)//obtendo sinais
    {
    case 0: { strcpy( aux, "+00000"); strcpy( aux_mant, "+000"); break; }
    case 1: { strcpy( aux, "+00000"); strcpy( aux_mant, "-000"); break; }
    case 2: { strcpy( aux, "-00000"); strcpy( aux_mant, "+000"); break; }
    case 3: { strcpy( aux, "-00000"); strcpy( aux_mant, "-000"); break; }
    } // fim switch sinal
	
  num  = genrand() % 32768;        //obtendo string numero
  sprintf(numero   , "%d",num);
  mant = genrand() % 309;          //obtendo string mantissa
  sprintf(mantissa , "%d", mant);
	
  tam = strlen(numero);
  strcpy(aux      + (6-tam), numero);
  tam = strlen(mantissa);
  strcpy(aux_mant + (4-tam), mantissa);
	
  strcat(aux, aux_mant);
	
  memset( * res, '\0', limite);
  if (limite > (int) strlen(aux))
    strcpy( * res, aux);
  else erro("Estouro de tamanho gerando double randomicamente",1);
  return 1;

} // fim forma_block_double_random



//_________________________________________________________________

/** Método que recupera o respectivo valor do bloco passado como argumento.  */
double individuo::decode_block_float ( char * bloco ){
   double res = 0;
   int pos_E  = -1, mant = 1;
   char * mantissa = NULL, * numero = NULL;
   alocaCharPtr( & numero  , 20, "decode_block_float", "numero");
   alocaCharPtr( & mantissa, 10, "decode_block_float", "mantissa");
   trim ( & bloco);
   pos_E = indexOf(bloco, 'E');
   strcpy( numero, bloco );
   if(pos_E != -1)
   {
      strncpy(numero, bloco, pos_E);
      strcpy(mantissa, bloco + pos_E + 1);
      mant = atoi(mantissa);

   }// fim pos_E
   res = atoi(numero);
   res *= pow(10, mant );

   alocaCharPtr( & numero  , 20, "decode_block_float", "numero");
   alocaCharPtr( & mantissa, 10, "decode_block_float", "mantissa");
   return res;
}

//_________________________________________________________________

/** Método usado para formatar um bloco a partir de um valor passado por argumento. */
int individuo::forma_block_float (char ** res, int limite, char * lido){
   int tam = 0;
   int pos_E = -1;
   char aux[20], mantissa[10], aux_mant[10], numero[10];
   memset(aux     , '\0', 20);
   memset(mantissa, '\0', 10);
   memset(aux_mant, '\0', 10);
   memset(numero  , '\0', 10);
   strcpy( aux, "+00000");
   strcpy( aux_mant, "+00");
   strcpy( mantissa, "00");
    	
   trim ( & lido);
   if ( (lido[0] == '-') || (lido[0] == '+') )
   {
      aux[0] = lido[0];
      lido++;
   }
   trim ( & lido);
   pos_E = indexOf(lido, 'E');
   if( pos_E != -1)
   {                                            //existe mantissa
   strncpy(numero  , lido,  pos_E);
   lido += pos_E;
   if ( (lido[0] == '-') || (lido[0] == '+') )
  	{
   	  aux_mant[0] = lido[0];
   	  lido++;
  	}
   trim ( & lido);
   strcpy (mantissa, lido);
    }// fim if tem E
    else strcpy (numero, lido);
    tam = strlen(numero);
    strcpy(aux      + (6-tam), numero);
    tam = strlen(mantissa);
    strcpy(aux_mant + (3-tam), mantissa);
     	
    strcat(aux, aux_mant);
    memset(*res, '\0', limite);
    if (limite > (int) strlen(aux))
    strcpy(*res, aux);
    else
    erro("Estouro de tamanho recuperando float",1);
    return true;
 }

//_________________________________________________________________
/** Método usado para formatar um bloco float aleatoriamente. */
int individuo::forma_block_float_random(char ** res, int limite)
{
  int tam = 0, num = 0, mant = 0, sinal = genrand()%4;         //[0++,1+-,2-+,3--]
	
  char aux[20], mantissa[10], aux_mant[10], numero[10];
  memset(aux     , '\0', 20);
  memset(mantissa, '\0', 10);
  memset(aux_mant, '\0', 10);
  memset(numero  , '\0', 10);
	
  switch (sinal)//obtendo sinais
    {
    case 0: { strcpy( aux, "+00000"); strcpy( aux_mant, "+00"); break; }
    case 1: { strcpy( aux, "+00000"); strcpy( aux_mant, "-00"); break; }
    case 2: { strcpy( aux, "-00000"); strcpy( aux_mant, "+00"); break; }
    case 3: { strcpy( aux, "-00000"); strcpy( aux_mant, "-00"); break; }
    } // fim switch sinal

  num  = genrand() % 32768;        //obtendo string numero
  sprintf(numero   , "%d",num);
  mant = genrand() % 39;          //obtendo string mantissa
  sprintf(mantissa , "%d", mant);
  tam = strlen(numero);
  strcpy(aux      + (6-tam), numero);
  tam = strlen(mantissa);
  strcpy(aux_mant + (3-tam), mantissa);
	
  strcat(aux, aux_mant);
	
  memset( *res, '\0', limite);
  if (limite > (int) strlen(aux))
    strcpy( *res, aux);
  else erro("Estouro de tamanho gerando float randomicamente",1);
  return 1;

} // fim forma_block_float_random

//_________________________________________________________________
/** Método usado para formatar um bloco string a partir de um valor passado por argumento. */
int individuo::forma_block_string(char ** res, int limite, char * lido)
{
  int blocoTam = strlen(lido);
  char * aux = NULL;
  alocaCharPtr( & aux , limite, "forma_block_string", "aux");
  strcpy(aux, lido);
  //   for (int j = blocoTam; j < limite - 1; j++) aux[j] = '#';
  for (int j = blocoTam; j < limite - 1; j++) aux[j] = 216;
  aux[limite - 1] = '\0';
  memset( * res, '\0', limite);
  if (limite > (int) strlen(aux))
     strcpy( * res, aux);
  else erro("Estouro de tamanho recuperando string",1);
  desalocaCharPtr( & aux , limite, "forma_block_string", "aux");
  return true;
} // fim forma_block_string

//_________________________________________________________________
/** Método usado para formatar um bloco string aleatoriamente. */
int individuo::forma_block_string_random(char ** res, int limite)
{
//  int carac = 0, tam_alfanumerico = strlen(alfanumerico);
  int blocoTam = (genrand() % (int) ( (*ctl)->tamanhoMaximoString - (*ctl)->tamanhoMinimoString + 1 ) ) + (int)(*ctl)->tamanhoMinimoString;
  char * aux = NULL;
  alocaCharPtr( & aux , limite + 1, "individuo::forma_block_string", "aux");

  for (int i=0; i<blocoTam;i++){
    *(aux+i) = generateChar( (*ctl)->tipoString );
  }
  for (int j = blocoTam; j < (*ctl)->tamanhoMaximoString ; j++)
    *(aux+j) = 216;
  //for (int j = blocoTam; j < (*ctl)->tamanhoMaximoString ; j++) aux[j] ='#';
  *(aux + (int) (*ctl)->tamanhoMaximoString) = '\0';

  //memset( * res, '\0', limite);
  //cout << "\nValor de limite= " << limite;
  //cout << "\nValor de blocoTam= " << blocoTam;
  //cout << "\nValor de aux= " << aux;
  //cout << "\nValor strlen(aux)= " << strlen(aux);

  if (limite >= (int) strlen(aux))
     strcpy( * res, aux);
  else erro("Estouro de tamanho gerando string randomicamente",1);
  desalocaCharPtr( & aux , limite + 1, "forma_block_string", "aux");
  return true;
} // fim forma_block_string_random

