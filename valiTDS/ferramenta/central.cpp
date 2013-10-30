/***************************************************************************
                          central.cpp  -  description
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

#include "central.h"

central::central(){
  //cout << "\nConstruindo central...";
  inicioExecucao = getSecs();
  fimExecucao                 = 0;
  fimPrimeiraExecucao         = 0;
  pausaGeracao                = 0;
  ativaTabu                   = 0;
  geraLog                     = 0;
  numeroArgumentos            = 0;
  tamanhoMinimoString         = 1;
  tamanhoMaximoString         = 30;
  tamanhoMinimoInteiro        = 0;
  tamanhoMaximoInteiro        = 10000;
  tamanhoMaximoArgumento      = 30;
  variacaoInteiro             = 10000;
  quantidadeElemento          = 0;
  coberturaAtual              = 0;
  somatoriaFitness            = 0;
  //   criterioTeste             = NULL;
  //   funcaoATestar             = NULL;
  //   criterioTestePoketool     = NULL;
  //   diretorio                 = NULL;
  //   diretorioPool             = NULL;
  maximoGeracoes              = 0;
  geracaoAtual                = 0;
  indiceMelhorGeracao         = 0;
  tamanhoIndividuo            = 0;
  tamanhoPopulacao            = 0;
  coberturaCriterio           = 0;     //novo nome coberturaDesejada
  coberturaInicial            = 0;
  melhorCobertura             = 0;
  taxaMutacao                 = 0;
  taxaCrossover               = 0;
  quantidadeElitismo          = 0;
  quantidadeIneditismo        = 0;
  quantidadeFitness           = 0;        //novo nome quantidadeSelecao
  geracoesComRepositorio      = 50;

  formatoIndividuo            = NULL;
  linhaPerda                  = NULL;
  linhaCoberturaAtual         = NULL;
  linhaCoberturaAnterior      = NULL;
  coberturaGlobal             = NULL;
  arquivoTabu                 = NULL;
  arquivoTabuAux              = NULL;
  arquivoFonte                = NULL;
  arquivoPopulacaoInicial     = NULL;
  arquivoPopulacao            = NULL;
  arquivoMelhorPopulacao      = NULL;
  arquivoPopulacaoTemporario  = NULL;
  arquivoFitness              = NULL;
  arquivoVariacaoFitness      = NULL;
  arquivoCoberturaIndividuo   = NULL;
  arquivoCoberturaElemento    = NULL;
  arquivoAvalCobIndividuos    = NULL;
  arquivoSemelhancaIndividuos = NULL;
  arquivoObsCobertura         = NULL;
  arquivoRepositorio          = NULL;
  arquivoBonusIneditismo      = NULL;
  arquivoIneditismo           = NULL;
  criterioTeste               = NULL;
  funcaoATestar               = NULL;
  criterioTesteValiMPI       = NULL;
  diretorio                   = NULL;
  diretorioPool               = NULL;
  tipoString                  = NULL;
  comandPath                  = NULL;
  enviroment                  = "";
  arquivoPopulacaoTemporario2  = "";

	funcoes = NULL;
	ccargs = NULL;
	nProcess = 0;

  alocaCharPtr( &formatoIndividuo            ,10, "central", "formatoIndividuo" );
  alocaCharPtr( &linhaPerda                  ,10, "central", "linhaPerda");
  alocaCharPtr( &linhaCoberturaAtual         ,10, "central", "linhaCoberturaAtual");
  alocaCharPtr( &linhaCoberturaAnterior      ,10, "central", "linhaCoberturaAnterior");
  alocaCharPtr( &coberturaGlobal             ,10, "central", "coberturaGlobal");
  alocaCharPtr( &arquivoTabu                 ,10, "central", "arquivoTabu");
  alocaCharPtr( &arquivoTabuAux              ,10, "central", "arquivoTabuAux");
  alocaCharPtr( &arquivoFonte                ,10, "central", "arquivoFonte");
  alocaCharPtr( &arquivoPopulacaoInicial     ,10, "central", "arquivoPopulacaoInicial");
  alocaCharPtr( &arquivoPopulacao            ,10, "central", "arquivoPopulacao");
  alocaCharPtr( &arquivoMelhorPopulacao      ,10, "central", "arquivoMelhorPopulacao");
  alocaCharPtr( &arquivoPopulacaoTemporario  ,10, "central", "arquivoPopulacaoTemporario");
  alocaCharPtr( &arquivoFitness              ,10, "central", "arquivoFitness");
  alocaCharPtr( &arquivoVariacaoFitness      ,10, "central", "arquivoVariacaoFitness");
  alocaCharPtr( &arquivoCoberturaIndividuo   ,10, "central", "arquivoCoberturaIndividuo");
  alocaCharPtr( &arquivoCoberturaElemento    ,10, "central", "arquivoCoberturaElemento");
  alocaCharPtr( &arquivoAvalCobIndividuos    ,10, "central", "arquivoAvalCobIndividuos");
  alocaCharPtr( &arquivoSemelhancaIndividuos ,10, "central", "arquivoSemelhancaIndividuos");
  alocaCharPtr( &arquivoObsCobertura         ,10, "central", "arquivoObsCobertura");
  alocaCharPtr( &arquivoRepositorio          ,10, "central", "arquivoRepositorio");
  alocaCharPtr( &arquivoBonusIneditismo      ,10, "central", "arquivoBonusIneditismo");
  alocaCharPtr( &arquivoIneditismo           ,10, "central", "arquivoIneditismo");
  alocaCharPtr( &criterioTeste               ,10, "central", "criterioTeste");
  alocaCharPtr( &funcaoATestar               ,10, "central", "funcaoATestar");
  alocaCharPtr( &criterioTesteValiMPI       ,10, "central", "criterioTesteValiMPI");
  alocaCharPtr( &diretorio                   ,10, "central", "diretorio");
  alocaCharPtr( &diretorioPool               ,10, "central", "diretorioPool");
  alocaCharPtr( &tipoString                  ,10, "central", "tipoString");
  setTipoString("sLln");

  tamEnviroment               = 480;
  tamComandPath               = 600;
  alocaCharPtr( &comandPath                  ,tamComandPath, "central", "comandPath");
//  alocaCharPtr( &enviroment                  ,tamEnviroment, "central", "enviroment");

}

//_________________________________________________________________

central::~central(){
  //cout << "\nDestruindo central...";
  desalocaCharPtr( &formatoIndividuo            , "central", "formatoIndividuo" );
  desalocaCharPtr( &linhaPerda                  , "central", "linhaPerda");
  desalocaCharPtr( &linhaCoberturaAtual         , "central", "linhaCoberturaAtual");
  desalocaCharPtr( &linhaCoberturaAnterior      , "central", "linhaCoberturaAnterior");
  desalocaCharPtr( &coberturaGlobal             , "central", "coberturaGlobal");
  desalocaCharPtr( &arquivoTabu                 , "central", "arquivoTabu");
  desalocaCharPtr( &arquivoTabuAux              , "central", "arquivoTabuAux");
  desalocaCharPtr( &arquivoFonte                , "central", "arquivoFonte");
  desalocaCharPtr( &arquivoPopulacaoInicial     , "central", "arquivoPopulacaoInicial");
  desalocaCharPtr( &arquivoPopulacao            , "central", "arquivoPopulacao");
  desalocaCharPtr( &arquivoMelhorPopulacao      , "central", "arquivoMelhorPopulacao");
  desalocaCharPtr( &arquivoPopulacaoTemporario  , "central", "arquivoPopulacaoTemporario");
  desalocaCharPtr( &arquivoFitness              , "central", "arquivoFitness");
  desalocaCharPtr( &arquivoVariacaoFitness      , "central", "arquivoVariacaoFitness");
  desalocaCharPtr( &arquivoCoberturaIndividuo   , "central", "arquivoCoberturaIndividuo");
  desalocaCharPtr( &arquivoCoberturaElemento    , "central", "arquivoCoberturaElemento");
  desalocaCharPtr( &arquivoAvalCobIndividuos    , "central", "arquivoAvalCobIndividuos");
  desalocaCharPtr( &arquivoSemelhancaIndividuos , "central", "arquivoSemelhancaIndividuos");
  desalocaCharPtr( &arquivoObsCobertura         , "central", "arquivoObsCobertura");
  desalocaCharPtr( &arquivoRepositorio          , "central", "arquivoRepositorio");
  desalocaCharPtr( &arquivoBonusIneditismo      , "central", "arquivoBonusIneditismo");
  desalocaCharPtr( &arquivoIneditismo           , "central", "arquivoIneditismo");
  desalocaCharPtr( &criterioTeste               , "central", "criterioTeste");
  desalocaCharPtr( &funcaoATestar               , "central", "funcaoATestar");
  desalocaCharPtr( &criterioTesteValiMPI       , "central", "criterioTesteValiMPI");
  desalocaCharPtr( &diretorio                   , "central", "diretorio");
  desalocaCharPtr( &diretorioPool               , "central", "diretorioPool");
  desalocaCharPtr( &tipoString                  , "central", "tipoString");
  desalocaCharPtr( &comandPath                  , "central", "comandPath");
  //desalocaCharPtr( &enviroment                  , "central", "enviroment");
  
	desalocaCharPtr( &funcoes                  ,1024, "central", "funcoes");
	desalocaCharPtr( &ccargs                  ,1024, "central", "ccargs");
}

//_________________________________________________________________
/** Metodo que mostra na tela o valor de todas as variáveis de controle da classe central. */
void central::printAll()
{
  cout << "\n pausaGeracao > " << pausaGeracao ;
  cout << "\n ativaTabu > " << ativaTabu ;
  cout << "\n geraLog > " << geraLog ;
  cout << "\n numeroArgumentos > " << numeroArgumentos ;
  cout << "\n tamanhoMinimoString > " << tamanhoMinimoString ;
  cout << "\n tamanhoMaximoString > " << tamanhoMaximoString ;
  cout << "\n tamanhoMinimoInteiro > " << tamanhoMinimoInteiro ;
  cout << "\n tamanhoMaximoInteiro > " << tamanhoMaximoInteiro ;
  cout << "\n tamanhoMaximoArgumento > " << tamanhoMaximoArgumento ;
  cout << "\n variacaoInteiro > " << variacaoInteiro ;
  cout << "\n quantidadeElemento > " << quantidadeElemento ;
  cout << "\n coberturaAtual > " << coberturaAtual ;
  cout << "\n somatoriaFitness > " << somatoriaFitness ;
  cout << "\n maximoGeracoes > " << maximoGeracoes ;
  cout << "\n geracaoAtual > " << geracaoAtual ;
  cout << "\n indiceMelhorGeracao > " << indiceMelhorGeracao ;
  cout << "\n tamanhoIndividuo > " << tamanhoIndividuo ;
  cout << "\n tamanhoPopulacao > " << tamanhoPopulacao ;
  cout << "\n coberturaCriterio > " << coberturaCriterio ;
  cout << "\n melhorCobertura > " << melhorCobertura ;
  cout << "\n taxaMutacao > " << taxaMutacao ;
  cout << "\n taxaCrossover > " << taxaCrossover ;
  cout << "\n quantidadeElitismo > " << quantidadeElitismo ;
  cout << "\n quantidadeIneditismo > " << quantidadeIneditismo ;
  cout << "\n quantidadeFitness > " << quantidadeFitness ;
  cout << "\n geracoesComRepositorio > " << geracoesComRepositorio ;
  cout << "\n formatoIndividuo > " << formatoIndividuo ;
  cout << "\n linhaPerda > " << linhaPerda ;
  cout << "\n linhaCoberturaAtual > " << linhaCoberturaAtual ;
  cout << "\n linhaCoberturaAnterior > " << linhaCoberturaAnterior ;
  cout << "\n coberturaGlobal > " << coberturaGlobal ;
  cout << "\n arquivoTabu > " << arquivoTabu ;
  cout << "\n arquivoTabuAux > " << arquivoTabuAux ;
  cout << "\n arquivoFonte > " << arquivoFonte ;
  cout << "\n arquivoPopulacaoInicial > " << arquivoPopulacaoInicial ;
  cout << "\n arquivoPopulacao > " << arquivoPopulacao ;
  cout << "\n arquivoMelhorPopulacao > " << arquivoMelhorPopulacao ;
  cout << "\n arquivoPopulacaoTemporario > " << arquivoPopulacaoTemporario ;
  cout << "\n arquivoFitness > " << arquivoFitness ;
  cout << "\n arquivoVariacaoFitness > " << arquivoVariacaoFitness ;
  cout << "\n arquivoCoberturaIndividuo > " << arquivoCoberturaIndividuo ;
  cout << "\n arquivoCoberturaElemento > " << arquivoCoberturaElemento ;
  cout << "\n arquivoAvalCobIndividuos > " << arquivoAvalCobIndividuos ;
  cout << "\n arquivoSemelhancaIndividuos > " << arquivoSemelhancaIndividuos ;
  cout << "\n arquivoObsCobertura > " << arquivoObsCobertura ;
  cout << "\n arquivoRepositorio > " << arquivoRepositorio ;
  cout << "\n arquivoBonusIneditismo > " << arquivoBonusIneditismo ;
  cout << "\n arquivoIneditismo > " << arquivoIneditismo ;
  cout << "\n criterioTeste > " << criterioTeste ;
  cout << "\n funcaoATestar > " << funcaoATestar ;
  cout << "\n criterioTesteValiMPI > " << criterioTesteValiMPI ;
  cout << "\n diretorio > " << diretorio ;
  cout << "\n diretorioPool > " << diretorioPool ;
  cout << "\n tipoString > " << tipoString ;
  
	cout << "\n funcoes >" << funcoes;
	cout << "\n numero_processos >" << nProcess;
}


//_________________________________________________________________
/** Metodo que carrega na classe central informações sobre a execução da ferramenta. */
int central::interpretaArquivoConfiguracao(){
  FILE * ptrArqConf = NULL;

  int igual = -1, pv = -1, tamLinha = 500;
  char * linha = NULL, * parametro = NULL, * valor = NULL;
  alocaCharPtr( &linha, tamLinha, "interpretaArquivoConfiguracao", "linha");
  alocaCharPtr( &parametro, tamLinha, "interpretaArquivoConfiguracao", "parametro");
  alocaCharPtr( &valor, tamLinha, "interpretaArquivoConfiguracao", "valor");

  ptrArqConf = fopen("arqconfig.txt","r");

  if (ptrArqConf == NULL)
    {
      sprintf(ErrorText,"nao abriu o arquivo corretamente : arqconfig.txt");
      erro(ErrorText,1);
    }

  setTipoString( "alfabetico" );

  while( ! feof(ptrArqConf) ){
      memset(linha, '\0', tamLinha);
      fgets(linha, tamLinha, ptrArqConf);
      trim( & linha);

      if (linha[0] == '#'){
         pv = indexOf(linha,';');
         if(pv == -1){
            sprintf(ErrorText,"nao encontrou ';' na linha : %s", linha);
            erro(ErrorText,1);
         }
         linha[pv] = '\0';
         igual = indexOf(linha,'=');
         if(igual == -1){
            sprintf(ErrorText,"nao encontrou '=' na linha : %s", linha);
            erro(ErrorText,1);
         }
         memset(parametro, '\0', tamLinha);
         memset(valor, '\0', tamLinha);

         strncpy(parametro, linha, igual);
         strcpy (valor    , (linha + igual + 1) );
         trim( & parametro);
         trim( & valor);

         printf("\n\n parametro: <%s>  valor: <%s>",parametro,valor);

         if( ( strcmp(parametro,"#NumeroArgumentos") == 0 ) || ( strcmp(parametro,"#ArgsNumber") == 0 ))
            setNumeroArgumentos( atoi(valor) );
         else
            if( strcmp(parametro,"#Log") == 0 )
               setGeraLog( 1 );
            else
               if( strcmp(parametro,"#PausaGeracao") == 0 )
                  setPausaGeracao( 1 );
               else
                  if( strcmp(parametro,"#Elitismo") == 0 )
                     setQuantidadeElitismo( atof(valor) );
                  else
                     if( strcmp(parametro,"#Ineditismo") == 0 )
                        setQuantidadeIneditismo( atof(valor) );
                     else
                        if( strcmp(parametro,"#Fitness") == 0 )
                           setQuantidadeFitness( atof(valor) );
                        else
                           if( (strcmp(parametro,"#ArquivoFonte") == 0 ) || (strcmp(parametro,"#SourceFile") == 0) )
                              setArquivoFonte( valor );
                           else
                              if( ( strcmp(parametro,"#FormatoEntrada") == 0 )  || (strcmp(parametro,"#InputFormat") == 0) )
                                 setFormatoIndividuo( valor );
                              else
                                 if( ( strcmp(parametro,"#VariacaoString") == 0 ) || (strcmp(parametro,"#StringRange") == 0) )
                                    setTamanhoString( valor );
                                 else
                                    if( ( strcmp(parametro,"#StringType") == 0 ) || (strcmp(parametro,"#TipoString") == 0) )
                                       setTipoString( valor );
                                    else
                                       if( ( strcmp(parametro,"#ArquivoPopulacao") == 0 ) || (strcmp(parametro,"#PopulationFile") == 0) )
                                          setArquivoPopulacaoInicial( valor );
                                       else
                                          if( ( strcmp(parametro,"#TamanhoPopulacao") == 0 ) || (strcmp(parametro,"#PopulationSize") == 0) )
                                             setTamanhoPopulacao( atof(valor) );
                                          else
                                             if( ( strcmp(parametro,"#NumeroGeracoes") == 0 ) || (strcmp(parametro,"#GenerationNumber") == 0) )
                                                setMaximoGeracoes( atoi(valor) );
                                             else
                                                if( ( strcmp(parametro,"#CoberturaCriterio") == 0 ) || (strcmp(parametro,"#CriterioCoverage") == 0) )
                                                    setCoberturaCriterio( atof(valor) );
                                                else
                                                   if( ( strcmp(parametro,"#Criterio") == 0 ) || (strcmp(parametro,"#Criterium") == 0) )
                                                       setCriterioTeste( valor );
                                                   else
                                                       if( ( strcmp(parametro,"#TaxaMutacao") == 0 ) || (strcmp(parametro,"#MutationRate") == 0) )
                                                           setTaxaMutacao( atof(valor) );
                                                       else
                                                          if( ( strcmp(parametro,"#TaxaCrossover") == 0 ) || (strcmp(parametro,"#CrossOverRate") == 0) )
                                                             setTaxaCrossover( atof(valor) );
                                                          else
                                                             if( ( strcmp(parametro,"#VariacaoInt") == 0 ) || ( strcmp(parametro,"#IntRange") == 0) )
                                                                setVariacaoInteiro( valor );
                                                             else
                                                                if( strcmp(parametro,"#NomeFuncao") == 0 ){
                                                                   setFuncaoATestar( valor );
                                                                   setDiretorio( valor );
                                                                   setArquivoPopulacao( valor );
                                                                   setArquivoPopulacaoTemporario( valor );
                                                                   setArquivoFitness( valor );
                                                                   setArquivoIneditismo( valor );
                                                                   setArquivoBonusIneditismo( valor );
                                                                   setArquivoVariacaoFitness( valor );
                                                                   }// fim if-then
                                                                else
                                                                   if ( ( strcmp(parametro,"#AtivaTabu") == 0 ) && ( ( strcmp(valor,"sim") == 0 ) || (strcmp(valor,"1") == 0) ) )
                                                                      setAtivaTabu( 1 );
                                                                   else
                                                                      if ( strcmp(parametro,"#GeracoesComRepositorio") == 0 )
                                                                         setGeracoesComRepositorio( atof(valor) );
                                                                         
                                                                      else
                                                                         if(strcmp(parametro,"#NumeroProcessos") == 0)
                                                                             setNProcess(atoi(valor));
                                                                         else
                                                                             if(strcmp(parametro,"#Funcoes") == 0)
                                                                                  setFuncoes(valor);
                                                                             else
                                                                             if(strcmp(parametro,"#CCArgs") == 0)
                                                                                  setCCArgs(valor);

         }//if linha[0] == '#'
         else
            cout << "\n IGNORANDO: <" << linha <<">";
      } //fim while
   setArquivoCoberturaElemento ( "cobXElemento" );
   setArquivoCoberturaIndividuo( "cobXIndividuo" );
   setArquivoSemelhancaIndividuos ( "semelhancaIndividuos" );
   setArquivoAvalCobIndividuos ( "avalCobIndividuos" );
   setArquivoRepositorio( "repositorio" );
   setDiretorioPool ( "pool" );
   setArquivoObsCobertura ( "relCobertura" );
   setTamanhoIndividuo();
   setArquivoMelhorPopulacao("melhorPop");
   setArquivoTabu ("tabu");
   setArquivoTabuAux ("tabuAux");
   if ( tamanhoMaximoString > 15 ) tamanhoMaximoArgumento = tamanhoMaximoString;

  fclose(ptrArqConf);

  desalocaCharPtr( &linha, "interpretaArquivoConfiguracao", "linha");
  desalocaCharPtr( &parametro, "interpretaArquivoConfiguracao", "parametro");
  desalocaCharPtr( &valor, "interpretaArquivoConfiguracao", "valor");

  printf("\n");
  return true;

}

//_________________________________________________________________
/** Método usado para gerar arquivo tar com informações completas para cada geração. */
void central::backup(){
  sprintf(Comando, "tar -czf %s_GER_%0.0f.tgz %s*", funcaoATestar, geracaoAtual, diretorio);  system(Comando);
}


//_________________________________________________________________
/** Método usado para gerar informações do progresso do framework ( geração, cobertura ). */
void central::status(){
  printf("\n###########################################");
  printf("\nGERACAO: <%0.0f>   COBERTURA: <%0.2f>", geracaoAtual, coberturaAtual);
  FILE * arq;
  if(geracaoAtual){
    arq = fopen("resumo.tst", "a");
  }
  else{
    arq = fopen("resumo.tst", "w");
  }
  fprintf(arq,"\nGERACAO: <%0.0f>   COBERTURA: <%0.2f>", geracaoAtual, coberturaAtual);
  fflush(arq);
  fclose(arq);
}

//_________________________________________________________________
/** Método usado para apresentar o resultado da execução do framework. */
void central::resultado(){
  time_t tempo = 0;
  fimExecucao = getSecs();
  tempo = fimPrimeiraExecucao - inicioExecucao;
  char * tempoFmt = NULL, * tempoPrimAval = NULL;
  alocaCharPtr( &tempoFmt, 100, "central::resultado", "tempoFmt");
  alocaCharPtr( &tempoPrimAval, 100, "central::resultado", "tempoFmt");

  printf("\nResultado");
  printf("\nPopulacao gerada em Populacao.res");

  printf("\nCobertura Inicial: %0.2f", coberturaInicial);
  strftime( tempoPrimAval, 99, "Dia(s): %j - Horas: %H:%M:%S", gmtime( &tempo) );
  printf("\nTempo Avaliação Inicial: %s  - em segundos: %ld", tempoPrimAval, tempo);

  printf("\nMelhor Cobertura : %0.2f", melhorCobertura);
  printf("\nMelhor Geracao : %0.0f", indiceMelhorGeracao);

  printf("\nCobertura %0.0fª População: %0.2f", geracaoAtual, coberturaAtual);

  tempo = fimExecucao - inicioExecucao;
  strftime( tempoFmt, 99, "Dia(s): %j - Horas: %H:%M:%S", gmtime( &tempo) );
  printf("\nTempo de execucao: %s - em segundos: %ld", tempoFmt, tempo);

  printf("\n\nCobertura Possivel: %0.2f\n<%s>", (double) numberOf(coberturaGlobal, 'X') / quantidadeElemento, coberturaGlobal);

  sprintf(Comando, "\nResultado\nCobertura Inicial: %0.2f\nTempo Avaliação Inicial: %s  - em segundos: %ld\nMelhor Cobertura : %0.2f\nMelhor Geracao : %0.0f \nTempo de execucao : %s \nTempo em segundos : %ld", coberturaInicial, tempoPrimAval, tempo, melhorCobertura, indiceMelhorGeracao, tempoFmt, tempo);
  toFile("resultado.tst", Comando);
  sprintf(Comando, "\nCobertura %0.0fª População: %0.2f\n\nCobertura Possivel: %0.2f\n<%s>", geracaoAtual, coberturaAtual, (double) numberOf(coberturaGlobal, 'X') / quantidadeElemento, coberturaGlobal);
  toFile("resultado.tst", Comando);
  desalocaCharPtr( &tempoFmt, 100, "central::resultado", "tempoFmt");
  desalocaCharPtr( &tempoPrimAval, 100, "central::resultado", "tempoFmt");
}
//_________________________________________________________________
/** Método usado para atribuir valor a variável de controle que identifica o tipo de string que o framework suporta. */
int central::setTipoString(char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setTipoString, erro no valor passado, tam<=0...", 1);
  if(tipoString) desalocaCharPtr( &tipoString, "setTipoString", "tipoString");
  alocaCharPtr( &tipoString, tam + 10, "setTipoString", "tipoString");
  strcpy(tipoString, valor);
  return true;
}

//_________________________________________________________________
/** Método usado para atribuir valor à variável de controle que possui o número de entradas por argumentos necessário para execução do programa em teste. */
int central::setNumeroArgumentos (int valor){
  numeroArgumentos = valor;
  return true;
}

//_________________________________________________________________
/** Método usado para atribuir valor à variável de controle responsável pela geração de log de execução do framework. */
int central::setGeraLog (int valor){
  geraLog = valor;
  return true;
}

//_________________________________________________________________
/** Método usado para atribuir valor à variável de controle responsável por pausa ao fim de cada geração. */
int central::setPausaGeracao (int valor){
  pausaGeracao = valor;
  return true;
}

//_________________________________________________________________
/** Método usado para atribuir valor à variável responsável pela quantidade de indivíduos gerados por elitismo. */
int central::setQuantidadeElitismo (double valor){
  quantidadeElitismo = valor;
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::setQuantidadeIneditismo(double valor){
  quantidadeIneditismo = valor;
  return true;
}


//_________________________________________________________________
/** No descriptions */
int central::setQuantidadeFitness (double valor){
  quantidadeFitness = valor;
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::setDiretorio (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setDiretorio, erro no valor passado, tam<=0...", 1);
  if(diretorio) desalocaCharPtr( &diretorio, "setDiretorio", "diretorio");
  alocaCharPtr( &diretorio, tam + 10, "setTipoString", "diretorio");
  strcpy(diretorio, valor);
  strcat(diretorio, BARRA);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setDiretorioPool (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setDiretorioPool, erro no valor passado, tam<=0...", 1);
  if(diretorioPool) desalocaCharPtr( &diretorioPool, "setDiretorioPool", "diretorioPool");
  alocaCharPtr( &diretorioPool, tam + 10, "setTipoString", "diretorioPool");
  strcpy(diretorioPool, valor);
  strcat(diretorioPool, BARRA);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoPopulacaoInicial (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoPopulacaoInicial, erro no valor passado, tam<=0...", 1);

  if(arquivoPopulacaoInicial) desalocaCharPtr( &arquivoPopulacaoInicial, "setArquivoPopulacaoInicial", "arquivoPopulacaoInicial");
  alocaCharPtr( &arquivoPopulacaoInicial, tam + 10, "setArquivoPopulacaoInicial", "arquivoPopulacaoInicial");

  strcpy(arquivoPopulacaoInicial, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoPopulacao (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoPopulacao, erro no valor passado, tam<=0...", 1);

  if(arquivoPopulacao) desalocaCharPtr( &arquivoPopulacao, "setArquivoPopulacao", "arquivoPopulacao");
  alocaCharPtr( &arquivoPopulacao, 2 * tam + 10, "setArquivoPopulacao", "arquivoPopulacao");

  sprintf(arquivoPopulacao, "%s%s.pop", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoPopulacaoTemporario (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoPopulacaoTemporario, erro no valor passado, tam<=0...", 1);
  if(arquivoPopulacaoTemporario) desalocaCharPtr( &arquivoPopulacaoTemporario, "setArquivoPopulacaoTemporario", "arquivoPopulacaoTemporario");
  alocaCharPtr( &arquivoPopulacaoTemporario, 2 * tam + 10, "setArquivoPopulacaoTemporario", "arquivoPopulacaoTemporario");

  sprintf(arquivoPopulacaoTemporario, "%s%s.tmp", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoFitness (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoFitness, erro no valor passado, tam<=0...", 1);
  if(arquivoFitness) desalocaCharPtr( &arquivoFitness, "setArquivoFitness", "arquivoFitness");
  alocaCharPtr( &arquivoFitness, 2 * tam + 10, "setArquivoFitness", "arquivoFitness");

  sprintf(arquivoFitness, "%s%s.fit", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoIneditismo (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoIneditismo, erro no valor passado, tam<=0...", 1);
  if(arquivoIneditismo) desalocaCharPtr( &arquivoIneditismo, "setArquivoIneditismo", "arquivoIneditismo");
  alocaCharPtr( &arquivoIneditismo, 2 * tam + 10, "setArquivoIneditismo", "arquivoIneditismo");

  sprintf(arquivoIneditismo, "%s%s.ine", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoBonusIneditismo (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivobonusIneditismo, erro no valor passado, tam<=0...", 1);
  if(arquivoBonusIneditismo) desalocaCharPtr( &arquivoBonusIneditismo, "setArquivoBonusIneditismo", "arquivoIneditismo");
  alocaCharPtr( &arquivoBonusIneditismo, 2 * tam + 10, "setArquivoBonusIneditismo", "arquivoBonusIneditismo");

  sprintf(arquivoBonusIneditismo, "%s%s.bon", diretorio, valor);
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::setArquivoFonte (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoFonte, erro no valor passado, tam<=0...", 1);
  if(arquivoFonte) desalocaCharPtr( &arquivoFonte, "setArquivoFonte", "arquivoFonte");
  alocaCharPtr( &arquivoFonte, tam + 10, "setArquivoFonte", "arquivoFonte");

  strcpy(arquivoFonte, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoSemelhancaIndividuos (char * valor)
{
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoSemelhancaIndividuos, erro no valor passado, tam<=0...",1);
  if(arquivoSemelhancaIndividuos) desalocaCharPtr( &arquivoSemelhancaIndividuos, "setArquivoSemelhancaIndividuos", "arquivoSemelhancaIndividuos");
  alocaCharPtr( &arquivoSemelhancaIndividuos, 2 * tam + 10, "setArquivoSemelhancaIndividuos", "arquivoSemelhancaIndividuos");

  strcpy(arquivoSemelhancaIndividuos, diretorio);
  strcat(arquivoSemelhancaIndividuos, valor);
  sprintf(arquivoSemelhancaIndividuos, "%s%s.cov", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setFormatoIndividuo (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setFormatoIndividuo, erro no valor passado, tam<=0...", 1);
  if(formatoIndividuo) desalocaCharPtr( &formatoIndividuo, "setFormatoIndividuo", "formatoIndividuo");
  alocaCharPtr( &formatoIndividuo, tam + 10, "setFormatoIndividuo", "formatoIndividuo");

  strcpy(formatoIndividuo, valor);
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::geraLinhaPerda ()
{
  if(geraLog) toFile("log_erro.log", "------geraLinhaPerda");
  memset(linhaPerda, '-', (int) (quantidadeElemento) );
  linhaPerda[ (int) quantidadeElemento ] = '\0';
  for (int j = 0; j < quantidadeElemento; j++ )
    {
      if ( (linhaCoberturaAnterior[j] == 'X') && (linhaCoberturaAtual[j] != 'X') )
         *(linhaPerda+j) = 'P';
    }
  return true;
}

//_________________________________________________________________
/** No descriptions */    //aqui Lu
int central::alocaLinhaPerda ()
{
  if(linhaPerda) desalocaCharPtr( &linhaPerda, "alocaLinhaPerda", "linhaPerda");
  alocaCharPtr( &linhaPerda, (int)(quantidadeElemento + 10), "alocaLinhaPerda", "linhaPerda");
  memset ( linhaPerda, '-', (int) (quantidadeElemento) );
  linhaPerda[(int) (quantidadeElemento)] = '\0';
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::alocaLinhaCoberturaAtual ()
{
  if(linhaCoberturaAtual) desalocaCharPtr( &linhaCoberturaAtual, "alocaLinhaCoberturaAtual", "linhaCoberturaAtual");
  alocaCharPtr( &linhaCoberturaAtual, (int)(quantidadeElemento + 10), "alocaLinhaCoberturaAtual", "linhaCoberturaAtual");
  memset ( linhaCoberturaAtual, '-', (int) (quantidadeElemento) );
  linhaCoberturaAtual[(int) (quantidadeElemento)] = '\0';
  return true;

}
//_________________________________________________________________
/** No descriptions */
int central::alocaCoberturaGlobal ()
{
  if(coberturaGlobal) desalocaCharPtr( &coberturaGlobal, "alocaCoberturaGlobal", "coberturaGlobal");
  alocaCharPtr( &coberturaGlobal, (int)(quantidadeElemento + 10), "alocaCoberturaGlobal", "coberturaGlobal");
  memset ( coberturaGlobal, '-', (int) (quantidadeElemento) );
  coberturaGlobal[(int) (quantidadeElemento)] = '\0';
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::alocaLinhaCoberturaAnterior ()
{
  if(linhaCoberturaAnterior) desalocaCharPtr( &linhaCoberturaAnterior, "alocaLinhaCoberturaAnterior", "linhaCoberturaAnterior");
  alocaCharPtr( &linhaCoberturaAnterior, (int) (quantidadeElemento + 10), "alocaLinhaCoberturaAnterior", "linhaCoberturaAnterior");
  memset ( linhaCoberturaAnterior, '-', (int) (quantidadeElemento) );
  linhaCoberturaAnterior[(int) (quantidadeElemento)] = '\0';
  return true;
}



//_________________________________________________________________
/** No descriptions */
int central::setFuncaoATestar (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setFuncaoATestar, erro no valor passado, tam<=0...", 1);
  if(funcaoATestar) desalocaCharPtr( &funcaoATestar, "setFuncaoATestar", "funcaoATestar");
  alocaCharPtr( &funcaoATestar, tam + 10, "setFuncaoATestar", "funcaoATestar");

  strcpy(funcaoATestar, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoVariacaoFitness (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoVariacaoFitness, erro no valor passado, tam<=0...", 1);
  if(arquivoVariacaoFitness) desalocaCharPtr( &arquivoVariacaoFitness, "setArquivoVariacaoFitness", "arquivoVariacaoFitness");
  alocaCharPtr( &arquivoVariacaoFitness, 2 * tam + 10, "setArquivoVariacaoFitness", "arquivoVariacaoFitness");

  sprintf(arquivoVariacaoFitness, "%s%s.vfi", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoCoberturaElemento (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoCoberturaElemento, erro no valor passado, tam<=0...", 1);
  if(arquivoCoberturaElemento) desalocaCharPtr( &arquivoCoberturaElemento, "setArquivoCoberturaElemento", "arquivoCoberturaElemento");
  alocaCharPtr( &arquivoCoberturaElemento, 2 * tam + 10, "setArquivoCoberturaElemento", "arquivoCoberturaElemento");

  sprintf(arquivoCoberturaElemento, "%s%s.cov",diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoCoberturaIndividuo (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoCoberturaIndividuo, erro no valor passado, tam<=0...", 1);
  if(arquivoCoberturaIndividuo) desalocaCharPtr( &arquivoCoberturaIndividuo, "setArquivoCoberturaIndividuo", "arquivoCoberturaIndividuo");
  alocaCharPtr( &arquivoCoberturaIndividuo, 2 * tam + 10, "setArquivoCoberturaIndividuo", "arquivoCoberturaIndividuo");

  sprintf(arquivoCoberturaIndividuo, "%s%s.cov", diretorio, valor);
  return true;
}



//_________________________________________________________________
/** No descriptions */
int central::setArquivoRepositorio (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoRepositorio, erro no valor passado, tam<=0...", 1);
  if(arquivoRepositorio) desalocaCharPtr( &arquivoRepositorio, "setArquivoRepositorio", "arquivoRepositorio");
  alocaCharPtr( &arquivoRepositorio, tam + 10, "setArquivoRepositorio", "arquivoRepositorio");

  strcpy(arquivoRepositorio, valor);
  strcat(arquivoRepositorio, ".dep");
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::setArquivoAvalCobIndividuos (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoAvalCobIndividuos, erro no valor passado, tam<=0...", 1);
  if(arquivoAvalCobIndividuos) desalocaCharPtr( &arquivoAvalCobIndividuos, "setArquivoAvalCobIndividuos", "arquivoAvalCobIndividuos");
  alocaCharPtr( &arquivoAvalCobIndividuos, 2 * tam + 10, "setArquivoAvalCobIndividuos", "arquivoAvalCobIndividuos");

  sprintf(arquivoAvalCobIndividuos, "%s%s.cov", diretorio, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoObsCobertura (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoObsCobertura, erro no valor passado, tam<=0...", 1);
  if(arquivoObsCobertura) desalocaCharPtr( &arquivoObsCobertura, "setArquivoObsCobertura", "arquivoObsCobertura");
  alocaCharPtr( &arquivoObsCobertura, 2 * tam + 10, "setArquivoObsCobertura", "arquivoObsCobertura");

  sprintf(arquivoObsCobertura, "%s.tst", valor);
  return true;

}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoMelhorPopulacao (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoMelhorPopulacao, erro no valor passado, tam<=0...", 1);
  if(arquivoMelhorPopulacao) desalocaCharPtr( &arquivoMelhorPopulacao, "setArquivoMelhorPopulacao", "arquivoMelhorPopulacao");
  alocaCharPtr( &arquivoMelhorPopulacao, tam + 10, "setArquivoMelhorPopulacao", "arquivoMelhorPopulacao");

  sprintf(arquivoMelhorPopulacao, "%s.pop", valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setArquivoTabu (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoTabu, erro no valor passado, tam<=0...", 1);
  if(arquivoTabu) desalocaCharPtr( &arquivoTabu, "setArquivoTabu", "arquivoTabu");
  alocaCharPtr( &arquivoTabu, tam + 10, "setArquivoTabu", "arquivoTabu");

  sprintf(arquivoTabu, "%s.pop", valor);
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::setArquivoTabuAux (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setArquivoTabuAux, erro no valor passado, tam<=0...", 1);
  if(arquivoTabuAux) desalocaCharPtr( &arquivoTabuAux, "setArquivoTabuAux", "arquivoTabuAux");
  alocaCharPtr( &arquivoTabuAux, tam + 10, "setArquivoTabuAux", "arquivoTabuAux");

  sprintf(arquivoTabuAux, "%s.pop", valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setTamanhoString (char * valor){
  int tam = 0,posicao = indexOf(valor, '/');

  if( posicao != -1)
    {
      tam = strlen(valor) + 1;
      char * auxiliar = NULL;
      if(auxiliar) desalocaCharPtr( &auxiliar, "setTamanhoString", "auxiliar");
      alocaCharPtr( &auxiliar, tam, "setTamanhoString", "auxiliar");

      strncpy(auxiliar, valor, posicao);
      trim( & auxiliar);
      tamanhoMinimoString     = atoi(auxiliar);
      memset(auxiliar, '\0', tam);
      strcpy(auxiliar, valor + posicao + 1);
      trim( & auxiliar);
      tamanhoMaximoString     = atoi(auxiliar);
      desalocaCharPtr( &auxiliar, "setTamanhoString", "auxiliar");
    }
  else
    tamanhoMaximoString = atoi(valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setTamanhoPopulacao (double valor){
  tamanhoPopulacao = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setMaximoGeracoes (double valor){
  maximoGeracoes = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setCoberturaCriterio (double valor){
  coberturaCriterio = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setCriterioTeste (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setCriterioTeste, erro no valor passado, tam<=0...", 1);
  if(criterioTeste) desalocaCharPtr( &criterioTeste, "setCriterioTeste", "criterioTeste");
  alocaCharPtr( &criterioTeste, tam + 10, "setCriterioTeste", "criterioTeste");
  strcpy(criterioTeste, valor);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setTaxaMutacao (double valor){
  taxaMutacao = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setTaxaCrossover (double valor){
  taxaCrossover = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setVariacaoInteiro (char * valor){
  int tam = 0,posicao = indexOf(valor, '/');
  if( posicao != -1)
    {
	  tam = strlen(valor) + 1;
      char * auxiliar = NULL;
      if(auxiliar) desalocaCharPtr( &auxiliar, "setVariacaoInteiro", "auxiliar");
      alocaCharPtr( &auxiliar, tam, "setVariacaoInteiro", "auxiliar");

      strncpy(auxiliar, valor, posicao);
      trim( & auxiliar);
      tamanhoMinimoInteiro  = atoi(auxiliar);
      memset(auxiliar, '\0', tam);
      strcpy(auxiliar, valor + posicao + 1);
      trim( & auxiliar);
      tamanhoMaximoInteiro  = atoi(auxiliar);
      desalocaCharPtr( &auxiliar, "setVariacaoInteiro", "auxiliar");
    }
  else
    tamanhoMaximoInteiro  = atoi(valor);
  variacaoInteiro = tamanhoMaximoInteiro - tamanhoMinimoInteiro;
  printf("\nOlha : %d %d %d %d\n",tamanhoMaximoInteiro,tamanhoMinimoInteiro,variacaoInteiro,tamanhoMaximoInteiro - tamanhoMinimoInteiro);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setMelhorCobertura(double valor)
{
  melhorCobertura = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setIndiceMelhorGeracao(int valor)
{
  indiceMelhorGeracao = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setTamanhoIndividuo (){
  int tam = strlen( formatoIndividuo );
  for (int pos = 0; pos < tam; pos++)
    tamanhoIndividuo += tamanhoTipo(pos);
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::tamanhoTipo(int pos){
  switch( formatoIndividuo[pos] )
    {
    case 'I': return 6;
    case 'D': return 10;
    case 'F': return 9;
    case 'S': return (int) tamanhoMaximoString;
    case 'C': return 1;
    }
  return 0; //zero nao influencia no tamanho do outros tipos.
}
//_________________________________________________________________
/** No descriptions */
int central::setQuantidadeElemento (double valor){
   quantidadeElemento = valor;
   alocaCoberturaGlobal();
   alocaLinhaCoberturaAnterior();
   alocaLinhaCoberturaAtual();
   alocaLinhaPerda();
   return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setCoberturaAtual (double valor){
  coberturaAtual = valor;
  if ( geracaoAtual == 0)
    coberturaInicial = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setSomatoriaFitness ( double valor ){
  somatoriaFitness = valor;
  return true;
}
//_________________________________________________________________
/** No descriptions */
int central::setCriterioTesteValiMPI (char * valor){
  int tam = strlen(valor);
  if (tam <= 0) erro("setCriterioTesteValiMPI, erro no valor passado, tam<=0...", 1);

  if(criterioTesteValiMPI) desalocaCharPtr( &criterioTesteValiMPI, "setCriterioTesteValiMPI", "criterioTesteValiMPI");
  alocaCharPtr( &criterioTesteValiMPI, tam + 10, "setCriterioTesteValiMPI", "criterioTesteValiMPI");
  strcpy(criterioTesteValiMPI, valor);
  return true;

}
//_________________________________________________________________
/** No descriptions */
int central::inicioTipo (int pos){
  int res = 0;
  for (int i = 0; i != pos; i++)
    res+= tamanhoTipo(i);
  return res;
}
//_________________________________________________________________
/** Método usado para verificar se o framework deve encerrar execução ou por ter alcançado a cobertura desejada ou por alcançar limite de gerações. */
int central::paraTeste(){
  if ( geracaoAtual == ( maximoGeracoes + 1) ) return true;
  if (coberturaCriterio != -1)
    {
      double x = numberOf(coberturaGlobal, 'X') * (100/quantidadeElemento);
      if (x >= coberturaCriterio * 100 ) return true;
    }
  return false;
}

//_________________________________________________________________
/** Método para cálculo do módulo entre dois doubles. */
double central::modulo(double a, double b)
{
  if(a < 0) a*= -1;
  if(b < 0) b*= -1;
  for(; a >= b; a -= b);
  return a;
}

//_________________________________________________________________
/** Método para geração aleatória de um double, simulação de sorteio. */
double central::geraSorteio(double maximo)
{
/**/
  int num1 = genrand();
  return modulo (num1, maximo);
/*/
   int num1 = rand();
   return modulo (num1, maximo);

/**/
}




//_________________________________________________________________
/** Método para avaliar a cobertura de cada indivíduo na população do AG. */
int central::avaliacaoCobertura()
{
  if(geraLog) toFile("log_erro.log", "---avaliacaoCobertura");

  char * linha1 = NULL, * linha2 = NULL, * linha = NULL;
  FILE * ptrCoberturas;
  alocaCharPtr( &linha, (int) (quantidadeElemento + 20), "avaliacaoCobertura", "linha" );
  alocaCharPtr( &linha1, (int) (quantidadeElemento + 20), "avaliacaoCobertura", "linha1" );
  alocaCharPtr( &linha2, (int) (quantidadeElemento + 20), "avaliacaoCobertura", "linha2" );

  ptrCoberturas = fopen (arquivoObsCobertura, "r");
  if ( ptrCoberturas == NULL )
    {
      sprintf(ErrorText, "avaliacaoCobertura: erro abrir arquivo : <%s>", arquivoObsCobertura);
      erro( ErrorText, 1 );
    }

      //pprova("PTO 1 ---avaliacaoCobertura");


  for( int i = 0; (!feof(ptrCoberturas) ) ; i++)
    {
      memset(linha2, '\0', (int) (quantidadeElemento + 20));
      fgets(linha2, (int) (quantidadeElemento + 19), ptrCoberturas);
      printf("\n cont: %d, <%s>", i, linha2);
      trim( & linha2);

	  //pprova("PTO 2 ---avaliacaoCobertura");

      if (strcmp(linha2,"") !=0 )
	{
	  strcpy(linha2, linha2+13);
	  strcpy(linha, linha2);
	  for (int j = 0; j < quantidadeElemento; j++ )
	    {
	      if (linha[j] != linha1[j])
		if (linha[j] == 'X')
		  linha[j] = 'N';
		else if (i != 0)
		  linha[j] = 'P';
	    }
	  strcpy(linha1, linha2);
	  toFile("avalCoberturas.tst", linha);
	}// FIM IF LINHA2 != ""
	  //pprova("PTO 3 ---avaliacaoCobertura");
    }
  desalocaCharPtr( &linha, "avaliacaoCobertura", "linha" );
  desalocaCharPtr( &linha1, "avaliacaoCobertura", "linha1" );
  desalocaCharPtr( &linha2, "avaliacaoCobertura", "linha2" );
  fclose( ptrCoberturas );

      //pprova("PTO 4 ---avaliacaoCobertura");

  return true;

}

//_________________________________________________________________
/** No descriptions */
int central::atualizaLinhaCoberturas(char * novaCobertura)
{
  if ( strlen(novaCobertura)  != quantidadeElemento )
     erro("atualizaLinhaCoberturas, erro no tamanho do valor passado, tam != quantidadeElemento...", 1);
  if ( linhaCoberturaAtual    == NULL )
     erro("atualizaLinhaCoberturas, erro linhaCoberturaAtual == NULL...", 1);
  //	if ( linhaCoberturaAnterior == NULL )
  //		erro("atualizaLinhaCoberturas, erro linhaCoberturaAnterior == NULL...", 1);
  //setLinhaCoberturaAnterior(linhaCoberturaAtual);
  setLinhaCoberturaAnterior(linhaCoberturaAtual);
  setLinhaCoberturaAtual(novaCobertura);
  //setCoberturaAtual(0);
  return true;
}

//_________________________________________________________________
/** Método usado para verificar se um determinado indivíduo já foi executado
anteriormente, caso positivo, copia o desempenho armazenado no repositório
parra a variável desempenho.
*/
int central::inRepositorio(char * strIndiv, char ** desempenho)
{
  FILE * ptrRepositorio;
  ptrRepositorio = fopen(arquivoRepositorio,"r");

  char * linha = NULL, * representacao = NULL;
  alocaCharPtr( &linha, (int) (quantidadeElemento + tamanhoIndividuo + 10), "inRepositorio", "linha" );
  alocaCharPtr( &representacao, (int) (tamanhoIndividuo + 10), "inRepositorio", "representacao" );

  while(! feof(ptrRepositorio) )
  {
     memset(linha, '\0', (int) (quantidadeElemento + tamanhoIndividuo + 10));
     memset(representacao, '\0', (int)  tamanhoIndividuo  + 10);
     fgets(linha, (int) (quantidadeElemento + tamanhoIndividuo + 9), ptrRepositorio);
     trim( & linha);
     strncpy(representacao, linha, (int) tamanhoIndividuo);
     strcpy(linha, linha + (int) tamanhoIndividuo + 2);
     trim( & linha);

     if(strcmp(strIndiv, representacao) == 0)
      {
        strcpy(*desempenho, linha);
        fclose(ptrRepositorio);

        desalocaCharPtr( &linha, "inRepositorio", "linha" );
        desalocaCharPtr( &representacao, "inRepositorio", "representacao" );
        return true;
      } // fim if
  }// fim while
  fclose(ptrRepositorio);
  desalocaCharPtr( &linha, "inRepositorio", "linha" );
  desalocaCharPtr( &representacao, "inRepositorio", "representacao" );
  return false;
}// fim inRepositorio()

//_________________________________________________________________
/** No descriptions */
int central::atualizaPerda(char * desempenho)
{
  int indice = -1;
  while ( (indice = indexOf(linhaPerda, 'P')) > 0 )
  {
     if (desempenho[indice] == 'X')
       linhaPerda[indice] = '-';
  }
  return true;
}

//_________________________________________________________________
/** No descriptions */
int central::manutencaoMelhorGeracao()
{
  if ( coberturaAtual > melhorCobertura )
  {
     setMelhorCobertura(coberturaAtual);
     setIndiceMelhorGeracao(geracaoAtual);
     sprintf(Comando, "cp %s %s", arquivoPopulacao, arquivoMelhorPopulacao);
     //printf("\nVai copiar arquivoPopulacao para arquivoMelhorPopulacao");
     //pprova(Comando);
     system(Comando);
  }
  return true;
}
//_________________________________________________________________
/** Método usado para iniciar a execução da ferramenta.
Apagar diretórios e arquivos que possam ter sidos gerados por execuções anteriores. */
int central::prepareExecution(){
   
   cout << "Atenção: Preparando a execução do framework. Diretórios e arquivos serão removidos...";
   sprintf(Comando, TDS_PATH"removeFile.sh %s %s valimpi logerror.tes log_erro.log detalhes.log Populacao.res Tabu.res tabu.pop melhorPop.pop resumo.tst resultado.tst relCobertura.tst avalCoberturas.tst *.gfc lixo.lxo entrada.kyb resultado.tst", diretorio, arquivoRepositorio);
   setComandPath( Comando );
   system( comandPath );
   
   sprintf(Comando, "mkdir %s", diretorio);
   setComandPath( Comando );
   system( comandPath );

   //system(Comando);
   return true;
}
 //_________________________________________________________________
/** Método para atribuir valores para variável de controle comandPath, com realocação de memória se necessário. */
int central::setComandPath (char * valor){
   int tam = strlen(valor);
   if (tam <= 0) erro("setComandPath, erro no valor passado, tam<=0...", 1);

   try {
      //if (strlen(enviroment) <= 0 )erro("setComandPath, erro - conteudo em enviroment vazio...", 1);
      if (enviroment.tam <= 0 )erro("setComandPath, erro - conteudo em enviroment vazio...", 1);
      tam +=  enviroment.tam;
      if ( (tam > tamComandPath) && (comandPath) ){
         desalocaCharPtr( &comandPath , tamComandPath, "setComandPath", "comandPath");
         tamComandPath = tam +10;
         alocaCharPtr( &comandPath , tamComandPath, "setComandPath", "comandPath");
      }
      sprintf(comandPath,"%s%s", enviroment.valor, valor);
   }
   catch(...){
      erro("Erro ao setar comandPath. Provavel estouro", 1);
   }
   return true;
}
//_________________________________________________________________
/** Método para atribuir valores para variável de controle correctPath, com realocação de memória se necessário. */
int central::setEnviroment(char * valor){
   int tam = strlen(valor);
   if (tam <= 0) erro("setEnviroment, erro no valor passado, tam<=0...", 1);
   enviroment = valor;
   /*if ( (tam > tamEnviroment) && (enviroment) ) {
      desalocaCharPtr( &enviroment , tamEnviroment, "setEnviroment", "enviroment");
      tamEnviroment = tam +10;
      alocaCharPtr( &enviroment , tamEnviroment, "setEnviroment", "enviroment");
   }
   strcpy(enviroment, valor);
   */
   return true;

}
/** Método usado para recalcular a quantidade de individuos gerados por elitismo, seleção e ineditismo. */
int central::recalculaPorcEvolucao(){
   double total = (quantidadeElitismo + quantidadeIneditismo + quantidadeFitness);
   quantidadeElitismo   =(int) (quantidadeElitismo * tamanhoPopulacao / total );
   quantidadeIneditismo =(int) ( quantidadeIneditismo * tamanhoPopulacao / total );
   quantidadeFitness    = tamanhoPopulacao - (quantidadeElitismo + quantidadeIneditismo);
   return true;
}
/** Método usado para atribuir valor para variável de controle linhaCoberturaAnterior */
int central::setLinhaCoberturaAnterior( char * valor ){
   int tam = strlen(valor);
   if (tam <= 0) erro("setLinhaCoberturaAnterior, erro no valor passado, tam<=0...", 1);
   if(linhaCoberturaAnterior) desalocaCharPtr( &linhaCoberturaAnterior , "setLinhaCoberturaAnterior", "linhaCoberturaAnterior");
   alocaCharPtr( &linhaCoberturaAnterior , tam + 10, "setLinhaCoberturaAnterior", "linhaCoberturaAnterior");

   strcpy(linhaCoberturaAnterior, valor);
   return true;
}
/** Método usado para atribuir valor para variável de controle linhaCoberturaAtual. */
int central::setLinhaCoberturaAtual (char * valor){
   int tam = strlen(valor);
   if (tam <= 0) erro("setLinhaCoberturaAtual, erro no valor passado, tam<=0...", 1);
   if(linhaCoberturaAtual) desalocaCharPtr( &linhaCoberturaAtual , "setLinhaCoberturaAtual", "linhaCoberturaAtual");
   alocaCharPtr( &linhaCoberturaAtual , tam + 10, "setLinhaCoberturaAtual", "linhaCoberturaAtual");
   strcpy(linhaCoberturaAtual, valor);
   return true;
}

/** Método usado para configurar o valor de ativaTabu. */
int central::setAtivaTabu(int valor){
   ativaTabu = valor;
}
/** Método usado para configurar o atributo geracoesComRepositorio. */
int central::setGeracoesComRepositorio(double valor){
   geracoesComRepositorio = valor;
   return true;
}
/** Atualiza a coberturaGlobal com a cobertura passada por argumento. */
int central::atualizaCoberturaGlobal( char * novaCobertura ){
  int tam = (int) quantidadeElemento;
  if ( strlen(novaCobertura) != tam ) {
    sprintf( ErrorText, "central:atualizaCoberturaGlobal - Tamanho da novaCobertura ( %d) incorreto", strlen(novaCobertura) );
    erro(ErrorText, 1);
  }
  if ( strlen(coberturaGlobal) != tam ) {
    sprintf( ErrorText, "central:atualizaCoberturaGlobal - Tamanho da coberturaAtual ( %d) incorreto", strlen(coberturaGlobal) );
    erro(ErrorText, 1);
  }
  for ( int i = 0; i < tam; i++ )
     if( *(novaCobertura+i) == 'X')  *(coberturaGlobal+i ) = 'X';

}
/** Método que configura o final da primeira execução. */
int central::setFimPrimeiraExecucao(){
   fimPrimeiraExecucao = getSecs();
}

/** Método que seta o número de processos. */
int central::setNProcess(int n)
{
	nProcess = n;
	return 1;
}

/** Método que seta o argumento de funcoes necessário para ValiMPI. */
int central::setFuncoes (char * valor){
   int tam = strlen(valor);
   
   if (tam <= 0) erro("Nao pode alocar para Funcoes", 1);

   try {
      alocaCharPtr( &funcoes , tam + 1, "setFuncoes", "funcoes");
      strcpy(funcoes,valor);
      funcoes[tam] = '\0';
   }
   catch(...){
      erro("Erro ao setar funcoes. Provavel estouro", 1);
   }
   return true;
}

int central::setCCArgs (char * valor){
   int tam = strlen(valor);
   
   if (tam <= 0) erro("Nao pode alocar para CCArgs", 1);

   try {
      alocaCharPtr( &ccargs , tam + 1, "setCCArgs", "ccargs");
      strcpy(ccargs,valor);
      ccargs[tam] = '\0';
   }
   catch(...){
      erro("Erro ao setar ccargs. Provavel estouro", 1);
   }
   return true;
}
