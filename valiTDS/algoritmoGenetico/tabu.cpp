/***************************************************************************
                          tabu.cpp  -  description
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

#include "tabu.h"

using namespace std;

tabu::tabu( central ** pctl ){
   ctl = pctl;
   if ( (*ctl)->geracaoAtual == 0){
      FILE * ptrArquivoTabu = fopen( (*ctl)->arquivoTabu, "w");
      fclose( ptrArquivoTabu);
   }

}
tabu::~tabu(){
}

int tabu::paraTabu( char * linhaCobertura){
  FILE   * ptrTabu;
  char * gene = NULL, * linhaCoberturaAux = NULL;
  int tamGene = nroEspacos( (int) (*ctl)->tamanhoPopulacao ) + (int) (*ctl)->tamanhoIndividuo + 5;
  int tamLinhaCob = (int) (*ctl)->quantidadeElemento + 5;
  alocaCharPtr( &gene , tamGene, "tabu::paraTabu", "gene" );
  alocaCharPtr( &linhaCoberturaAux , tamLinhaCob, "tabu::paraTabu", "linhaCoberturaAux" );

  ptrTabu = fopen( (*ctl)->arquivoTabu, "r+");
  int contx = 0;
  if(ptrTabu == NULL){
    sprintf( ErrorText,"nao abriu o arquivo da lista Tabu : %s", (*ctl)->arquivoTabu );
    erro( ErrorText, 1 );
  }

  for (contx = 0;! feof(ptrTabu); ){
    memset(gene, '\0', tamGene);
    fgets(gene, tamGene, ptrTabu);
    trim( & gene);
    strcpy(gene, gene + indexOf(gene, ':')+1);
    trim( & gene);
    printf("\nGene : %s", gene);
    printf("PTO1001");
    if (! strcmp(gene, "") == 0){
      //rastro("PTO1002");
      (*ctl)->inRepositorio(gene, & linhaCoberturaAux);
      printf("PTO1002.2");
      printf("Comparando com %s de Tabu cujo a cobertura: \n%s", gene, linhaCoberturaAux);
      printf("PTO1003");
      if ( ! cobre(linhaCobertura, linhaCoberturaAux) ){
        printf("PTO1005");
        toFileTabu(contx ++, gene, (*ctl)->arquivoTabuAux);
        /*pprova * /
        printf("Nao substituiu");
        printf("PTO1006");
        /**/
      }
      else cout << "susbstituiu";
      /*pprova * /
      printf("PTO1007");
      printf("Analise se substitui");
      /**/
    } // fim if strcmp
    printf("PTO1010");
  } // fim if for
  fclose(ptrTabu);
  desalocaCharPtr( &gene , tamGene, "tabu::paraTabu", "gene" );
  desalocaCharPtr( &linhaCoberturaAux , tamLinhaCob, "tabu::paraTabu", "linhaCoberturaAux" );
  return true;
}


/** Método */
int tabu::toFileTabu ( int nro, char * str, char * arquivo){
  populacao * pop = new populacao (&(*ctl) );
  pop->toPopulacao(nro, str, arquivo);
  delete (pop);
  return true;
/*   if ( nro != 0 ){
     if (populacao.inPopulacao(str, arquivo) ){
       return false;
     }
   }
   FILE * pop;
   pop = fopen( arquivo,"a" );
   fprintf( pop,"%5d : %s\n", nro, str );
   fflush(pop);
   fclose( pop );
   return true;
*/
}
/** Verifica se a cobertura recem gerada para o individuo identificado por nroIndividuo melhora a cobertura global.
Caso sim deve entrar em tabu retirando coberturas cobertas. */
int tabu::manutencaoTabu( char * coberturaIndividuo, int nroIndividuo){
   if ( melhora(coberturaIndividuo) ){
      (*ctl)->atualizaCoberturaGlobal( coberturaIndividuo );
      //guarda no repositorio.
      atualizaTabu(coberturaIndividuo, nroIndividuo);

   }
   return true;

}
/** Verifica se a cobertura atual melhora a cobertura global mantida pela referencia ao objeto central. */
int tabu::melhora( char * coberturaAtual){
  int i=0, tam = (int) (*ctl)->quantidadeElemento;
  if ( strlen(coberturaAtual) != tam ) {
    sprintf( ErrorText, "tabu:melhora - Tamanho da coberturaAtual ( %d) incorreto", strlen(coberturaAtual) );
    erro(ErrorText, 1);
  }
  if ( strlen( (*ctl)->coberturaGlobal ) != tam ) {
    sprintf( ErrorText, "tabu:melhora - Tamanho da coberturaAtual ( %d) incorreto", strlen(coberturaAtual) );
    erro(ErrorText, 1);
  }

  for (i=0; i<tam; i++)
    if( (*(coberturaAtual+i) == 'X') && ( *((*ctl)->coberturaGlobal+i ) == '-') ) return true;
  return false;
}
//Nao compensa este metodo separado apenas para carregar de tabu e nao avaliar ja.
int tabu::atualizaTabu(char * coberturaIndividuo, int pos){
  FILE * ptrTabu = NULL;
  char * gene = NULL, * geneAux = NULL;
  char * coberturaIndTabu = NULL;
  int pos2 = 0, contador = 0;
  int tamGene = nroEspacos( (int) (*ctl)->tamanhoPopulacao ) + (int) (*ctl)->tamanhoIndividuo + 5;

  sprintf( Comando, TDS_PATH"removeFile.sh %s -rf", (*ctl)->arquivoTabuAux );
  (*ctl)->setComandPath(Comando);
  system ( (*ctl)->comandPath );


  individuo * indiv = new individuo ( &(*ctl) );
  if( pos >= (*ctl)->tamanhoPopulacao)
    erro("extrapolou tamanho da populacao",1);
  indiv->load(pos);

  if(pos >= (*ctl)->tamanhoPopulacao){
      sprintf(ErrorText,"tabu:loadFromTabu - pos, %d, extrapolou tamanho da populacao %f", pos, (*ctl)->tamanhoPopulacao);
      erro(ErrorText ,1);
  }

  alocaCharPtr( &gene , tamGene, "tabu::loadFromTabu", "gene" );
  alocaCharPtr( &geneAux , tamGene, "tabu::loadFromTabu", "geneAux" );
  alocaCharPtr( &coberturaIndTabu , (int) ( (*ctl)->quantidadeElemento + 20), "tabu::loadFromTabu", "coberturaIndTabu" );

  ptrTabu = fopen( (*ctl)->arquivoTabu, "r");

  if(ptrTabu == NULL){
    sprintf( ErrorText,"nao abriu o arquivo da lista Tabu : %s", (*ctl)->arquivoTabu );
    erro( ErrorText, 1 );
  }

  for (contador=0; !feof(ptrTabu); ){
    try{
      fgets(gene, (int) tamGene , ptrTabu);
      trim ( & gene);

      pos2 = indexOf(gene, ':') + 1;
      strcpy(geneAux, gene + pos2 );
      trim ( & geneAux );
      if(strcmp (geneAux , "" ) == 0 )
         continue;
    }
    catch(...){
      erro("tabu::atualizaTabu - Estouro de memoria ao tentar recuperar individuo da linha do arquivo de populacao , metodo load",1);
    }
    //Recuperando cobertura dos individuos da lista tabu e armazenando em coberturaindTabu
    if ( (*ctl)->inRepositorio(geneAux, &coberturaIndTabu ) == false )
      erro("tabu::atualizaTabu - Nao recuperou o desempenho do Individuo, Executa de novo ou força armazenar no repositorio...",1);
    //Se cobertura em avaliação cobre cobertura de algum individuo que ja esta na
    //lista tabu, este nao sera inserido em (*ctl)->arquivoTabuAux
    if ( ! cobre(coberturaIndividuo, coberturaIndTabu) )
      toFileTabu(contador ++, geneAux, (*ctl)->arquivoTabuAux);
   }// fim for
   toFileTabu(contador ++, indiv->representacao, (*ctl)->arquivoTabuAux);
   fclose(ptrTabu);
   sprintf( Comando, "mv %s %s", (*ctl)->arquivoTabuAux, (*ctl)->arquivoTabu );
   (*ctl)->setComandPath( Comando );
   system ( (*ctl)->comandPath );


   desalocaCharPtr( &gene , tamGene, "tabu::loadFromTabu", "gene" );
   desalocaCharPtr( &geneAux , tamGene, "tabu::loadFromTabu", "geneAux" );
   desalocaCharPtr( &coberturaIndTabu , ( (*ctl)->quantidadeElemento + 20), "tabu::loadFromTabu", "coberturaIndTabu" );
}


