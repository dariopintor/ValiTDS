/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Dom Jul  6 01:09:30 BRT 2003
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "diversos.h"
#include "central.h"
#include "ferramenta.h"
#include "populacao.h"
#include <time.h>

int main(int argc, char *argv[]){

  total_alocado = 0;
  central * ctl = NULL;
  ctl = new central();
  system( ctl->comandPath );
  time_t inic = 0, fim = 0;
  inic = getSecs();
  initGenRand();
  cout << "\nTDSGen - rc 1.0 - 07/10/2003" << endl;
  cout << "\nAutor: Luciano Petinati Ferreira" << endl;
//  if (argc > 2) {
//    if (strcmp (argv[1], "-v") == 0 ){
//      cout<< "\nData 01/09/2003";
//      cout<< "\nVersão 1 L";
//    }
//    return EXIT_SUCCESS;
//  }
//   return EXIT_SUCCESS;
//  código pra valer.
  ctl->interpretaArquivoConfiguracao();
  ctl->prepareExecution();

  ferramenta * fr = NULL;
  fr = new ferramenta(& ctl);

  fr->prepareTool();
  ctl->setQuantidadeElemento( fr->obtemElementosRequeridos() );
  fr->~ferramenta();
  populacao * pop = NULL;
  pop = new populacao(& ctl);
  pop->geraPopulacaoInicial();
  pop->avaliaPopulacao();
  ctl->backup();
  ctl->status();
  ctl->setFimPrimeiraExecucao();

  for ( ctl->geracaoAtual = 1; ! ctl->paraTeste(); ctl->geracaoAtual ++){
    pop->evoluiPopulacao();
    pop->avaliaPopulacao();
    ctl->backup();
    ctl->manutencaoMelhorGeracao();

    ctl->status();
  }// fim for
  fim = getSecs();
  cout << "\nFim do processo de evolução..." << endl;
  ctl->resultado();
  if (ctl->geracaoAtual > 1) pop->decodificaPopulacao(ctl->arquivoMelhorPopulacao, "Populacao.res");
  if (ctl->ativaTabu) pop->decodificaPopulacao(ctl->arquivoTabu, "Tabu.res");

  if (ctl == NULL) cout << "<TDSGen> ERRO - ctl == NULL inesperado...";
  delete (ctl);

  cout << "\nFim de execução...\n";

/*
  central * ctl = NULL;
  ctl = new central();
  ctl->interpretaArquivoConfiguracao();
  individuo * indiv = NULL;
  indiv = new individuo(& ctl);
  ferramenta * fr = NULL;
  fr = new ferramenta(& ctl);
  fr->prepareTool();
  fr->~ferramenta();


  tabu * listaTabu = NULL;

  listaTabu = new tabu( & ctl );


  populacao * pop = NULL;
  pop = new populacao(& ctl);

  pop->geraPopulacaoInicial();

  char * linhaCobertura = NULL;
  alocaCharPtr( &linhaCobertura, 10000 ,"geraCoberturaIndividuoPoketool", "linhaCobertura" );

  for (int contador = 0; contador < ctl->tamanhoPopulacao; contador ++){
      indiv->load(contador);
      if (! ctl->inRepositorio(indiv->representacao, & linhaCobertura)){
         cout<< "O individuo " << contador << " nao esta no repositorio";
      }
      ctl->setQuantidadeElemento( strlen(linhaCobertura) );
      listaTabu->manutencaoTabu( linhaCobertura, contador);
  }
  desalocaCharPtr( &linhaCobertura, 10000 ,"geraCoberturaIndividuoPoketool", "linhaCobertura" );

  delete (ctl);

  cout << "\nFim de execução...\n";
*/
  return EXIT_SUCCESS;

}
