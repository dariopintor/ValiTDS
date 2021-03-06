/***************************************************************************
                          diversos.cpp  -  description
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
/** Fun��o usada para apresentar mensagem de erro e finalizar o programa caso necess�rio. */
 void erro (char * str, int fim ){
  cout <<"\n\n######################################################\n\nERRO - " << str << "\nFinalizando programa.\n";
  if(fim) exit(0);
  else getchar();
}

//_________________________________________________________________

/** Fun��o usada para enviar conteudo no final de um arquivo com informa��o da hora. */
int toFile(char * arquivo, char * conteudo)
{
  time_t hora;
  tm * ptm;
  time(&hora);
  ptm = gmtime(&hora);
  FILE * ptrFile;
  ptrFile = fopen(arquivo, "a");
  fprintf( ptrFile,"\n%s       , %02d:%02d:%02d h", conteudo, ptm->tm_hour - 2, ptm->tm_min, ptm->tm_sec );
  fflush(ptrFile);
  fclose(ptrFile);
  return true;
}//fim toFile
//_________________________________________________________________

/** Fun��o usada para obter segundos referentes a data e hora atuais. */
long getSecs()
{
  time_t secs;
  secs = time(NULL);
  return secs;
}//fim toFile
//_________________________________________________________________

/** Fun��o usada para enviar conteudo no final de um arquivo com informa��o da hora. */
int appendToFile(char * arquivo, int contador, char * conteudo)
{
  FILE * ptrFile;
  ptrFile = fopen(arquivo, "a");
  fprintf(ptrFile,"%5d : %s\n", contador, conteudo);
  fflush(ptrFile);
  fclose(ptrFile);
  return true;
}//fim toFile

//_________________________________________________________________

/** Fun��o usada para retornar o n�mero de ocorrencias de um caracter em um string. */
int numberOf(char * str, char busca)
{
  int tam = strlen(str), res = 0;
  for(int i=0; i < tam; i++){
    if(str[i] == busca) res++;
  }// fim for
  return res;
};// fim indexOf

//_________________________________________________________________

/** Fun��o usada para retornar a posi��o de um caracter em um string. */
int indexOf(char * str, char busca)
{
  int tam = strlen(str);
  for(int i=0; i < tam; i++){
    if(str[i] == busca) return i;
  }// fim for
  return -1;
};// fim indexOf

//_________________________________________________________________

/** Fun��o usada para retornar a posi��o de um substring em um string. */
int indexOf(char * str, char * busca)
{
  int tamStr   = strlen(str), tamBusca = strlen(busca), res = -1;
  if (tamBusca > tamStr) return -1;
  for(int i=0; i <= tamStr - tamBusca; i++){
    if(str[i] == busca[0]) {
      res = i;
      for (int j=1; j < tamBusca; j++){
         if( str[i+j] != busca[j]) res = -1;
      }// fim for
      if (res != -1) return res;
    } //fim if
  }// fim for
  return -1;

};// fim indexOf

//_________________________________________________________________

/** Fun��o usada para retirar espa�oes em branco do in�cio e fim de um string. */

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
/*/
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
  /**/
}// fim trim

/** Fun��o usada para gerar um caracter aleatoriamente, com base no string seletivo. */
char generateChar(char * seletivo)
{
  int somatoria = 0, sorteio = 0;
  int entraEspaco = 0, entraLETRA = 0, entraLetra = 0, entraNumero = 0;
  for (int i = 0; i < (int)strlen(seletivo); i ++){
      switch( *(seletivo+i) ){
         case 's':
            somatoria ++;
            entraEspaco = 1;
            break;
         case 'L':
            somatoria += 26;
            entraLETRA = 1;
            break;
         case 'l':
            somatoria += 26;
            entraLetra = 1;
            break;
         case 'n':
            somatoria += 10;
            entraNumero = 1;
            break;
      } // fim switch
      //if (seletivo[i] == 's') somatoria += 1;    //espa�o
      //if (seletivo[i] == 'L') somatoria += 26;   //letras maisculas
      //if (seletivo[i] == 'l') somatoria += 26;   //letras minusculas
      //if (seletivo[i] == 'n') somatoria += 10;   //numeros
    }
  //Obtive quantos podem ser os numeros a serem sorteados.
  sorteio = ( genrand() % somatoria );
  //Tirar caracteres invalidos, joga para espa�o
  sorteio += 32;
  //Se espa�o fora soma 1
  if (! entraEspaco) sorteio += 1;
  //Tira espa�os invalidos entre espa�o e numeros, joga para numeros
  if (sorteio > 32) sorteio += 15;
  //Se numeros fora soma 10
  if ( (! entraNumero) && (sorteio >= 48) ) sorteio += 10;
  //Tira espa�os invalidos entre espa�o e numeros, joga para LETRAS
  if (sorteio > 57) sorteio += 7;
  //Se LETRAS fora soma 26
  if ( (! entraLETRA) && (sorteio >= 65) ) sorteio += 26;
  //Tira espa�os invalidos entre LETRAS e letras, joga para letras
  if (sorteio > 90) sorteio +=  6;
  //Se letras fora soma 26
  if ( (! entraLetra) && (sorteio >= 97) ) sorteio += 26;

  return (char) sorteio;
} // fim generateChar

/** Fun��o usada para alocar char * com log e incremento de total_alocado. */
/** /
void alocaCharPtr( char ** ptr, int size, char * metodo, char * name){
   if (size == 0) size = 1;
   if (*ptr != NULL){
      sprintf(ErrorText,"%s::%s nao era NULL, nao poderia alocar pois perco a memoria anterior,", metodo, name);
      erro(ErrorText,1);
      }
   *ptr = (char *)malloc (sizeof(char) * size);
   //*ptr = new char [sizeof(char) * size ];
   if (!*ptr){
      cout << "\nerro, nao alocou";
      erro ("Nao foi alocado.",1);
   }
   else {
      //total_alocado += size;
      memset (*ptr, '\0', size);
      sprintf(ErrorText, "1, 0, %s , %d , , alocado pelo metodo %s", name, size, metodo);
      toFile ("log_alocacoes.tst", ErrorText);

   }
}

/*/
void alocaCharPtr( char ** ptr, int size, char * metodo, char * name){
   if (size == 0) size = 1;
   if (*ptr != NULL){
      sprintf(ErrorText,"%s::%s nao era NULL, nao poderia alocar pois perco a memoria anterior,", metodo, name);
      erro(ErrorText,1);
      }
   *ptr = new char [sizeof(char) * size ];
   if (!*ptr){
      cout << "\nerro, nao alocou";
      erro ("Nao foi alocado.",1);
   }
   else {
      total_alocado += size;
      memset (*ptr, '\0', size);
        }
}


void desalocaCharPtr (char ** ptr, char * metodo, char * name){
   if (*ptr){
      delete [](*ptr);
      //sprintf(ErrorText, "0, 1, %s , , %d , desalocado pelo metodo %s", name, 0, metodo);
      //toFile ("log_alocacoes.tst", ErrorText);

   }
   *ptr = NULL;
}
/**/
/** Fun��o usada para desalocar char * com log e decremento de total_alocado. */
void desalocaCharPtr (char ** ptr, int size, char * metodo, char * name){
   if (*ptr){
      try{
         free (*ptr);
         total_alocado -= size;
         //sprintf(ErrorText, "0, 1, %s , , %d , desalocado pelo metodo %s", name, size, metodo);
         //toFile ("log_alocacoes.tst", ErrorText);
      }
      catch(...){
         toFile("log.log", "provavelmente ptr nao era NULL nem foi alocado, continha lixo");
         erro("provavelmente ptr nao era NULL nem foi alocado, continha lixo", 1);
      }
   }
   *ptr = NULL;
}

/** Fun��o usada para calcular tamanho usado pelos numeros  na linha do arquivo */
int nroEspacos(int tamPopulacao){
  int nroEspacos = 0;
  for ( int base = 10; tamPopulacao >= base; base*= 10, nroEspacos++);
  return nroEspacos + 10;
}

int cobre(char * cobertura1, char * cobertura2)
{
  int tam = strlen(cobertura2);
  for (int i = 0; i < tam; i ++){
    if ( (cobertura2[i] == 'X') && (cobertura1[i] != 'X') )
      return false;
  }// fim for
  return true;
}



/* A C-program for MT19937: Integer     version                   */
/*  genrand() generates one pseudorandom unsigned integer (32bit) */
/* which is uniformly distributed among 0 to 2^32-1  for each     */
/* call. sgenrand(seed) set initial values to the working area    */
/* of 624 words. Before genrand(), sgenrand(seed) must be         */
/* called once. (seed is any 32-bit integer except for 0).        */
/*   Coded by Takuji Nishimura, considering the suggestions by    */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.              */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
/* Any feedback is very welcome. For any question, comments,       */
/* see http://www.math.keio.ac.jp/matumoto/emt.html or email       */
/* matumoto@math.keio.ac.jp                                        */



/* initializing the array with a NONZERO seed */

void sgenrand(unsigned long seed)
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0]= seed & 0xffffffff;
    for (mti=1; mti<N; mti++)
        mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}

unsigned long genrand()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if sgenrand() has not been called, */
            sgenrand(4357); /* a default initial seed is used   */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }

    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    //sprintf(ErrorText, "Gerou %f", y);
    //tofile("ctlGerNumAleat.tst", ErrorText);
    return y;
}

/* this main() outputs first 1000 generated numbers  */
void initGenRand()
{
    time_t hora;
    tm * ptm;
    time(&hora);
    ptm = gmtime(&hora);
    sgenrand( (ptm->tm_hour - 2) * (ptm->tm_min + 1) * (ptm->tm_sec + 1) );
    /*
    for (j=0; j<1000; j++) {
        printf("%12u ", genrand());
        if (j%8==7) printf("\n");
    }
    printf("\n");
    */
}
