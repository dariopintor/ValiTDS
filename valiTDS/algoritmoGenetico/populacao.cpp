/***************************************************************************
                          populacao.cpp  -  description
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

#include "populacao.h"

populacao::~populacao(){
   //cout << "\nDestruindo população...";
   ctl = NULL;
}
/** No descriptions */
 populacao::populacao(central ** parCtl){
   //cout << "\nConstruindo população...";
   ctl = parCtl;
}

//_________________________________________________________________

/** Método usado para gerar população inicial para o AG.
Cria a população inicial aleatória, com base nas configurações fornecidas ou
Cria a população inicial baseado em um arquivo fornecido. */
int populacao::geraPopulacaoInicial(){
   int retorno = 0;
   toFile("log_erro.log", "---geraPopulacaoInicial");
   if ( strcmp((*ctl)->arquivoPopulacaoInicial,"") == 0)
   {
      retorno =  geraPopulacaoInicialAleatoria();
   }
   else
   {
      retorno = geraPopulacaoInicialArquivo();
   }
   if((*ctl)->geraLog) toFile("log_erro.log", "---saindo geraPopulacaoInicial");
   return retorno;
}

//_________________________________________________________________

/** Cria a população inicial aleatória, com base nas configurações fornecidas */
int populacao::geraPopulacaoInicialAleatoria(){
   cout << "\nGerando pop.inic.aleatoria";
   individuo * indiv = NULL;
   indiv = new individuo( &(*ctl) );
   int foi = 0;
   for (int contador = 0; contador < (*ctl)->tamanhoPopulacao; )
   {
   	
      indiv->novo();
      /*
      sprintf(ErrorText, "individuo nro %d", contador);
      if ( (contador == 10 ) && (!foi) ) {
        foi = !foi;
        sprintf(ErrorText, "individuo nro %d", contador - 1);
        }
      if( toPopulacao( contador, ErrorText, (*ctl)->arquivoPopulacao ) ) contador ++;
      */
      if( toPopulacao( contador, indiv->representacao, (*ctl)->arquivoPopulacao ) ) contador ++;
   } // fim for
   delete (indiv);
   
   return true;
}

//_________________________________________________________________

/** Cria a população inicial  baseado em arquivo fornecido. */
int populacao::geraPopulacaoInicialArquivo(){
   printf("\nGerando pop.inic.arquivo %s", (*ctl)->arquivoPopulacaoInicial);

   FILE * ptrPopulacaoInicial;
   ptrPopulacaoInicial = fopen((*ctl)->arquivoPopulacaoInicial,"r");
   if( ptrPopulacaoInicial == NULL){
      sprintf(ErrorText, "nao abriu o arquivo corretamente : %s", (*ctl)->arquivoPopulacaoInicial);
      erro(ErrorText,1);
   }
   individuo * indiv = NULL;
   indiv = new individuo( &(*ctl) );
   char * linha  = NULL;
   alocaCharPtr( &linha , (int) ((*ctl)->tamanhoIndividuo * 2), "geraPopulacaoInicialArquivo", "linha");


   int contador = 0;
   for (contador = 0; !feof (ptrPopulacaoInicial); )
   {
      memset(linha, '\0', (int) ((*ctl)->tamanhoIndividuo * 2) );
      fgets(linha, (int) ((*ctl)->tamanhoIndividuo * 2), ptrPopulacaoInicial);
      trim( & linha);
      if( strcmp(linha,"" ) != 0 )
      {
         indiv->novo(linha);
         if( toPopulacao( contador, indiv->representacao, (*ctl)->arquivoPopulacao ) ) contador ++;
      }
   } // fim for
   (*ctl)->setTamanhoPopulacao( contador );
   (*ctl)->recalculaPorcEvolucao();

   //(*ctl)->printAll();
   //pprova("Analise ctl...");

   desalocaCharPtr( &linha , (int) ((*ctl)->tamanhoIndividuo * 2), "geraPopulacaoInicialArquivo", "linha");
   fclose ( ptrPopulacaoInicial );
   delete (indiv);
   return true;
}

//_________________________________________________________________

/** Método usado para incluir um novo indivíduo no arquivo de população.
Caso o indivíduo já exista na população a inserção não será realizada. */
int populacao::toPopulacao(int nro, char * strIndividuo, char * arquivo){
   /**/
   if ( ( strcmp(strIndividuo, "") == 0 ) || ( *strIndividuo == (char)216 ) )
      cout<< "populacao::toPopulacao::erro, tentando salvar individuo vazio ou 216,216";
   /**/
   if ( nro != 0 ){
      if (inPopulacao(strIndividuo, arquivo) ){
         return false;
      }
   }
   FILE * pop;
   pop = fopen( arquivo,"a+" );
   fprintf( pop,"%5d : %s\n", nro, strIndividuo );
   fflush(pop);
   fclose( pop );
   pop = NULL;
   return true;
}

//_________________________________________________________________

/** Método usado para verificar se um individuo está na população representada pelo
arquivo passado por argumento. */
//alocacoes de char * - ok

int populacao::inPopulacao(char * strIndividuo, char * arquivo){
   if(strlen(strIndividuo) <= 0)
   return false;
   int retorno = false;

   FILE * pop;
   pop = fopen(arquivo,"r");
   if(pop == NULL) erro("nao abriu o arquivo de populacao corretamente", 1);
   int pos = 0;
   char * linha = NULL, * representacao = NULL;
   alocaCharPtr( &linha, (int) ((*ctl)->tamanhoIndividuo + 20) ,"inPopulacao", "linha" );
   alocaCharPtr( &representacao, (int) ((*ctl)->tamanhoIndividuo + 10) ,"inPopulacao", "representacao" );

   while(! feof(pop) )
   {
      //rastro("Entrou no while");
      memset(linha, '\0', (int)( (*ctl)->tamanhoIndividuo + 20 ) );
      memset(representacao, '\0',(int) (*ctl)->tamanhoIndividuo + 10);
      fgets(linha, (int)((*ctl)->tamanhoIndividuo + 20), pop);
      pos = indexOf(linha, ':');
      if(pos != -1)
      {
         strcpy(representacao, linha + pos + 1);
         trim( & representacao);
         if(strcmp(strIndividuo, representacao) == 0)
         {
            //fclose(pop);
            //desalocaCharPtr (& representacao, (int) ((*ctl)->tamanhoIndividuo + 10), "inPopulacao", "representacao");
            //desalocaCharPtr (& linha, (int) ((*ctl)->tamanhoIndividuo + 20), "inPopulacao", "linha");
            retorno =  true;
            break;
         }
      } // fim if
   }// fim while

   fclose(pop);
   desalocaCharPtr (& representacao, (int) ((*ctl)->tamanhoIndividuo + 10), "inPopulacao", "representacao");
   desalocaCharPtr (& linha, (int) ((*ctl)->tamanhoIndividuo + 20), "inPopulacao", "linha");
   return retorno;
}

//_________________________________________________________________

/** Método usado para avaliar a população do AG.
Cada individuo é executado e o fitness é calculado com base no número de
elementos requeridos satisfeitos pela execução do mesmo. */
int populacao::avaliaPopulacao(){
   if((*ctl)->geraLog) toFile("log_erro.log", "---avaliaPopulacao");
   geraCoberturaIndividuo();
   toFile("log_alocacoes.tst","0, 0, 0, PProva");
   toFile("log_alocacoes.tst","1, 0, 0, PProva");
   geraBonusIneditismo();
   geraIneditismoPopulacao();

   //geraCoberturaDesempenhoIndividuos();
   /*
   geraLinha exige que a cobertura da populacao seja calculada antes, portanto foi modificada para
   o metodo geraCoberturaIndividuo, mais especificamente geraCoberturaIndividuoProteum.
   Deve ser implementado em geraCoberturaValiMPI.
   Ate entao era feito em geraFitness() e devera ser mudado...
   */

   (*ctl)->geraLinhaPerda();
   cout << "\n Linha de perda:\n" << (*ctl)->linhaPerda;
   //double quantPerdida = numberOf((*ctl)->linhaPerda, 'P');

   //sprintf(ErrorText, " ### Perda de %0.1f elementos...", quantPerdida );
   //toFile("linhasPerdas.fil", ErrorText );
   //toFile("linhasPerdas.fil", (*ctl)->linhaPerda);

   // Procedimento para recuperacao de individuos perdidos da geracao anterior
   // para a geracao atual que nao poderiam ser
   /*
   // Esse codigo sera reavaliado... esta comentado para gerar relatorio de teste para
   // publicacao em artigo...

   if (quantPerdida)
   {
      //recuperaIndividuos((quantPerdida > (*ctl)->maximoRecuperados)? (*ctl)->maximoRecuperados : quantPerdida );
      // Para efeito de teste...
      recuperaIndividuos( 2 );
      geraCoberturaIndividuo();
      geraIneditismo();
   }
   */
   geraFitness();
   if((*ctl)->geraLog) toFile("log_erro.log", "---saindo avaliaPopulacao");
   return true;
}// fim avaliaPopulacao()

//_________________________________________________________________

/** Método usado para gerar a cobertura dos indivíduos da população. */
int populacao::geraCoberturaIndividuo(){

   if((*ctl)->geraLog) toFile("log_erro.log", "------geraCoberturaIndividuo");
   if(strcmp((*ctl)->criterioTeste, "Analise de Mutantes") != 0)
   {
      //se for ValiMPI
      printf("\nGerando cobertura para ValiMPI...");
      geraCoberturaIndividuoValiMPI();
   }
   else
   {
      printf("\nGerando cobertura para Proteum...");
      geraCoberturaIndividuoProteum();
   }
   //Tanto geraCoberturaValiMPI como geraCoberturaProteum geram (*ctl)->coberturaCriterio.
   (*ctl)->setCoberturaAtual  (  numberOf((*ctl)->linhaCoberturaAtual, 'X') *  100 / (*ctl)->quantidadeElemento  );

   cout << "\nCobertura Gerada...";
   cout << "coberturaGlobal - " << (*ctl)->coberturaGlobal<< "\nlinhaCobertura - " << (*ctl)->linhaCoberturaAtual;
   sobrepoe(&((*ctl)->coberturaGlobal), (*ctl)->linhaCoberturaAtual);

   geraCoberturaElementos();

   if((*ctl)->geraLog) toFile("log_erro.log", "------saindo geraCoberturaIndividuo");
   return true;
}
//_________________________________________________________________

/** Método usado para gerar a cobertura dos indivíduos da população com base em
arquivos gerados pela utilização da ferramenta Proteum. */
int populacao::geraCoberturaIndividuoProteum(){
   //Prepara a avaliação - manipulação com arquivos do diretorio pool
   //Este diretório deve ser regerado para avaliação.
   if ( geraPool() != true)
      return false;

   tabu * listaTabu = NULL;

   if ( (*ctl)->ativaTabu )
      listaTabu = new tabu( & (*ctl) );

   individuo * indiv = NULL;
   indiv = new individuo(& (*ctl) );

   ferramenta * fr   = NULL;
   fr = new ferramenta(& (*ctl) );

   char * linhaCobertura = NULL;
   char * linhaCoberturaCriterio = NULL;

   alocaCharPtr( &linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCobertura" );
   alocaCharPtr( &linhaCoberturaCriterio, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCoberturaCriterio" );

   memset(linhaCoberturaCriterio , '-', (int) ( (*ctl)->quantidadeElemento ) );
   //linhaCoberturaCriterio[ (int) (*ctl)->quantidadeElemento ] = '\0';
   cout << "\nAvaliando os Indivíduos:\n" ;

   sprintf(Comando, "rm %s -rf", (*ctl)->arquivoCoberturaIndividuo);
   (*ctl)->setComandPath(Comando);
   system( (*ctl)->comandPath );

   for (int contador = 0; contador < (*ctl)->tamanhoPopulacao; contador ++){
      indiv->load(contador); //ou contador+1);
      memset (linhaCobertura, '-', (int) ((*ctl)->quantidadeElemento) );

      //verifica necessidade de execucao
      if ( ((*ctl)->geracaoAtual == 0) || ((*ctl)->geracaoAtual >= (*ctl)->geracoesComRepositorio) || (! (*ctl)->inRepositorio(indiv->representacao, & linhaCobertura) ) )
      //if (true)
      {
         //deve executar o programa.
         fr->evaluateIndividualProteum( contador );
         fr->obtemCoberturaProteum( & linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) );

         toRepositorio( contador, linhaCobertura );
      }  // fim if
      else{
         cout << "R";
      }

      //atualiza a cobertura do criterio / sobrepoe.
      sobrepoe(&linhaCoberturaCriterio, linhaCobertura);

      if ( ! appendToFile( (*ctl)->arquivoCoberturaIndividuo, contador, linhaCobertura ) ){
        sprintf(ErrorText, "nao gravou no arquivo : %s", (*ctl)->arquivoCoberturaIndividuo);
        erro(ErrorText,1);
        }

      //atualiza lista tabu se necessario
      if ( (*ctl)->ativaTabu ) {
        listaTabu->manutencaoTabu( linhaCobertura, contador);
        }

   }   // fim for contador
   (*ctl)->atualizaLinhaCoberturas(linhaCoberturaCriterio);

   desalocaCharPtr( &linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCobertura" );
   desalocaCharPtr( &linhaCoberturaCriterio, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCoberturaCriterio" );
   delete (indiv);
   delete (fr);

   return true;
}
//_________________________________________________________________

/** Método usado para gerar a cobertura dos indivíduos da população com base em
arquivos gerados pela utilização da ferramenta ValiMPI.

Para cada individuo da populacao, deve obter a cobertura.
  verifica se ja esta no repositorio,
      se  estiver,
          recupera a cobertura/desempenho do repositorio.
      se nao estiver
          executa o programa instrumentado para cada individuo.
          obtem a cobertura alcancada.
  Documenta a cobertura no arquivo

  verifica se deve ser incluido na lista tabu.
      se tiver,
          substitui todos os individuos com cobertura coberta por esse individuo e insere na lista tabu
      senao
          nao faz nada.
*/
int populacao::geraCoberturaIndividuoValiMPI(){
   individuo * indiv = NULL;
   indiv = new individuo(& (*ctl) );
   ferramenta * fr   = NULL;
   fr = new ferramenta(& (*ctl) );
   tabu * listaTabu = NULL;

   if ( (*ctl)->ativaTabu )
      listaTabu = new tabu( & (*ctl) );

   char * linhaCobertura = NULL;
   char * linhaCoberturaCriterio = NULL;

   alocaCharPtr( &linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCobertura" );
   alocaCharPtr( &linhaCoberturaCriterio, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCoberturaCriterio" );

   memset(linhaCoberturaCriterio , '-', (int) ( (*ctl)->quantidadeElemento ) );
   //linhaCoberturaCriterio[ (int) (*ctl)->quantidadeElemento ] = '\0';
   cout << "\nAvaliando os Indivíduos:\n" ;
   //printf( "\nAvaliando os Indivíduos:\n" );
   sprintf(Comando, "rm %s -rf", (*ctl)->arquivoCoberturaIndividuo);
   (*ctl)->setComandPath(Comando);
   system( (*ctl)->comandPath );

   for (int contador = 0; contador < (*ctl)->tamanhoPopulacao; contador ++){
      //recupera individuo da populacao e inicializa a linha de cobertura.
      indiv->load(contador); //ou contador+1);
      memset (linhaCobertura, '-', (int) ((*ctl)->quantidadeElemento) );
      //linhaCobertura [(int) (*ctl)->quantidadeElemento] = '\0';
      //cout << "\nIndivíduo " << contador << "- ";

      //verifica necessidade de execucao
      if ( ((*ctl)->geracaoAtual == 0) || ((*ctl)->geracaoAtual >= (*ctl)->geracoesComRepositorio ) || (! (*ctl)->inRepositorio(indiv->representacao, & linhaCobertura) ) )
      //if (true)
      {
         //deve executar o programa.
         fr->evaluateIndividual( contador );
         fr->obtemCoberturaValiMPI( & linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) );

         toRepositorio( contador, linhaCobertura );
      }  // fim if
      else{
         cout << "R";
      }

      //atualiza a cobertura do criterio / sobrepoe.
      sobrepoe(&linhaCoberturaCriterio, linhaCobertura);

      if ( ! appendToFile( (*ctl)->arquivoCoberturaIndividuo, contador, linhaCobertura ) ){
        sprintf(ErrorText, "nao gravou no arquivo : %s", (*ctl)->arquivoCoberturaIndividuo);
        erro(ErrorText,1);
        }

      //atualiza lista tabu se necessario
      if ( (*ctl)->ativaTabu ) {
        listaTabu->manutencaoTabu( linhaCobertura, contador);
        }
      //tabu->atualiza(indiv.representacao, linhaCobertura);
   }   // fim for contador

   (*ctl)->atualizaLinhaCoberturas(linhaCoberturaCriterio);
   //(*ctl)->setCoberturaAtual( 0);



   desalocaCharPtr( &linhaCobertura, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCobertura" );
   desalocaCharPtr( &linhaCoberturaCriterio, (int) ( (*ctl)->quantidadeElemento + 20 ) ,"geraCoberturaIndividuoValiMPI", "linhaCoberturaCriterio" );
   delete (indiv);
   delete (fr);

   return true;
}  // fim geraCoberturaIndividuoValiMPI()

//_________________________________________________________________

/** Método usado para armazenar desempenho de um indivíduo, assim não precisa executa-lo
novamente para obter sua cobertura. */
int populacao::toRepositorio ( int nro, char * desempenho){
  individuo * indiv = new individuo ( &(*ctl) );
//gravaNew(indiv);
  if( nro >= (*ctl)->tamanhoPopulacao)
    erro("extrapolou tamanho da populacao",1);

  indiv->load(nro);

  FILE * ptrRepositorio;
  ptrRepositorio = fopen((*ctl)->arquivoRepositorio,"a");
  fprintf(ptrRepositorio,"%s : %s\n", indiv->representacao, desempenho);
  fflush(ptrRepositorio);
  fclose(ptrRepositorio);

  delete (indiv);
  return true;
}
/** Método usado para sobrepor duas linhas de coberturas.
 */
int populacao::sobrepoe(char ** cobertura, char * desempenho){
   int i=0;
   char * coberturaLocal = NULL;
   alocaCharPtr(& coberturaLocal, ((int)(*ctl)->quantidadeElemento + 2), "sobrepoe", "coberturaLocal");
   strcpy(coberturaLocal, * cobertura );
   //cout << "\nCobertura: "<< coberturaLocal <<"\nDesempenho: "<< desempenho;
   if(strcmp( coberturaLocal, "")==0)
      strcpy( coberturaLocal, desempenho);
   else
   {
      int tam =  strlen( * cobertura);
      for (i=0; i<tam; i++)
        if( coberturaLocal[i] == '-')  coberturaLocal[i] = desempenho[i];
   }// fim else
   strcpy ( *cobertura, coberturaLocal );
   desalocaCharPtr(& coberturaLocal, ((int)(*ctl)->quantidadeElemento + 2), "sobrepoe", "coberturaLocal");
   return true;
}// fim sobrepoe


/** Método que evolui a população de indivíduos. */
int populacao::evoluiPopulacao(){
  if( (*ctl)->geraLog) toFile("log_erro.log", "---EvoluiPopulacao");

  sprintf( Comando, TDS_PATH"removeFile.sh %s -rf", (*ctl)->arquivoPopulacaoTemporario );
  
  (*ctl)->setComandPath(Comando);
  system ( (*ctl)->comandPath );

  if ((*ctl)->quantidadeFitness > 0)    evolucaoPorFitness();

  if ((*ctl)->quantidadeElitismo > 0)   evolucaoPorElitismo();

  if ((*ctl)->quantidadeIneditismo > 0) evolucaoPorIneditismo();

  /*
    Para recuperar individuos que foram perdidos da geracao passada e nao poderiam ser
    pois era um individuo que cobria um elemento nao coberto na nova populacao, deve-se
    manter uma copia da populacao anterior. Essa esta sendo guardada em
    ctl->arquivoPopulacaoTemporario...
  */
  sprintf( Comando, "cp %s %s", (*ctl)->arquivoPopulacao, "popManejo.pop" );
  (*ctl)->setComandPath(Comando);
  system ( (*ctl)->comandPath );
  sprintf( Comando, "mv %s %s", (*ctl)->arquivoPopulacaoTemporario, (*ctl)->arquivoPopulacao );
  (*ctl)->setComandPath(Comando);
  system ( (*ctl)->comandPath );
  sprintf( Comando, "mv %s %s", "popManejo.pop", (*ctl)->arquivoPopulacaoTemporario );
  (*ctl)->setComandPath(Comando);
  system ( (*ctl)->comandPath );

  //rastro("saiu - populacao::evolui");

  if((*ctl)->geraLog) toFile("log_erro.log", "---saindo EvoluiPopulacao");

  return true;

}
/** Método usado para evoluir a população com base no fitness dos indivíduos. */
int populacao::evolucaoPorFitness(){
  if((*ctl)->geraLog) toFile("log_erro.log", "------evolucaoFitness");
  individuo * indiv1 = new individuo(&(*ctl));
  individuo * indiv2 = new individuo(&(*ctl));
  int cross = 0, mut = 0;
  double sorteio = 0;

  int contador = 0;

  /*prova*/
  //Apagar o arquivo evolucaio.fil caso seja a primeira evolucao da população, retirando assim,
  //informações de execuções anteriores.
  if ((*ctl)->geracaoAtual == 0) system("rm evolucao.fil");
  /*pprova*/
  toFile("evolucao.fil", "");
  toFile("evolucao.fil", "##############################################################");
  sprintf(ErrorText, "Evolucao Geracao :%d", (int) (*ctl)->geracaoAtual);
  toFile("evolucao.fil", ErrorText);
  toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR FITNESS (%0.0f) / somatoriaFitness = %0.0f", (*ctl)->quantidadeFitness, (*ctl)->somatoriaFitness);
  toFile("evolucao.fil", ErrorText);
  /**/

  //contador possui a quantidade de indivíduos gerados e aceitos na próxima geração.
  //Iteração para gerar novo indivíduo enquanto contador for menr que a quantidade configurada.
  for(contador=0; contador < (*ctl)->quantidadeFitness; )
    {
      sorteio =  (*ctl)->geraSorteio( (*ctl)->somatoriaFitness );

      indiv1->load( (int) indiceIndividuoSorteado( sorteio ) );
      /*prova* /
      sprintf(ErrorText, "\n1 Sorteio : %f : <%s>", sorteio, indiv1.representacao);
      printf(ErrorText);
      /**/

      /*prova*/
      toFile("evolucao.fil", "--------------------------------------------------------------");
      sprintf(ErrorText, "1 Sorteio : %f : <%s>", sorteio, indiv1->representacao);
      toFile("evolucao.fil", ErrorText);
      /**/

      sorteio = (*ctl)->geraSorteio( (*ctl)->somatoriaFitness );
      indiv2->load( (int) indiceIndividuoSorteado ( sorteio ) );
      /*prova* /
      sprintf(ErrorText, "\n2 Sorteio : %f : <%s>", sorteio, indiv2.representacao);
      printf(ErrorText);
      /**/

      /*prova*/
      sprintf(ErrorText, "2 Sorteio : %f : <%s>", sorteio, indiv2->representacao);
      toFile("evolucao.fil", ErrorText);
      /**/

      cross = genrand() % 100;
      if(cross <= (*ctl)->taxaCrossover * 100){
        crossover( &(indiv1->representacao), &(indiv2->representacao) );
        /*prova*/
        sprintf(ErrorText, "    op CROSSOVER : %s / %s", indiv1->representacao, indiv2->representacao);
        toFile("evolucao.fil", ErrorText);
        /**/
        }
      mut   = genrand() % 100;
      if(mut <= (*ctl)->taxaMutacao * 100){
        mutacao(indiv1->representacao);
        /*prova*/
        sprintf(ErrorText, "    op MUTACAO 1  : %s", indiv1->representacao);
        toFile("evolucao.fil", ErrorText);
        /**/
        }
      if( toPopulacao( contador, indiv1->representacao, (*ctl)->arquivoPopulacaoTemporario ) ){
        contador ++;
        /*prova*/
        sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, indiv1->representacao);
        toFile("evolucao.fil", ErrorText);
        /**/
        }
      if(contador < (*ctl)->quantidadeFitness ){
        mut   = genrand() % 100;
        if(mut <= (*ctl)->taxaMutacao * 100){
          mutacao(indiv2->representacao);
          /*prova*/
          sprintf(ErrorText, "    op MUTACAO 2  : %s", indiv2->representacao);
          toFile("evolucao.fil", ErrorText);
          /**/
          }
        if( toPopulacao( contador, indiv2->representacao, (*ctl)->arquivoPopulacaoTemporario ) ){
          contador ++;
          /*prova*/
          sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, indiv2->representacao);
          toFile("evolucao.fil", ErrorText);
          /**/
          }
        }// fim if
    } // fim for fitness
  delete (indiv1);
  delete (indiv2);
  if((*ctl)->geraLog) toFile("log_erro.log", "------saindo evolucaoFitness");
  return true;

}
/** Método retorna o índice do indivíduo sorteado.
Com base na somatória do fitness e na ordem dos indivíduos, simulando o método de seleção da roleta. Retorna qual o indivíduo possui está na faixa sorteada. */
int populacao::indiceIndividuoSorteado(double sorteio){
  double superior = 0;
  int tamLinha = nroEspacos( (int) (*ctl)->tamanhoPopulacao ) + 30;
  char * linha = NULL;
  alocaCharPtr( &linha , tamLinha, "populacao::indiceIndividuoSorteado", "linha" );
  FILE * ptrFitness;
  ptrFitness = fopen( (*ctl)->arquivoFitness, "r" );
  if(ptrFitness == NULL){
      sprintf(ErrorText,"nao abriu o arquivo de Variacao de fitness : %s", (*ctl)->arquivoVariacaoFitness);
      erro(ErrorText,1);
    }

  for (int i=0; ( i < (*ctl)->tamanhoPopulacao) ; i++)
    {
      memset( linha, '\0', tamLinha );
      fgets(linha, tamLinha, ptrFitness);
      strcpy(linha, linha + indexOf(linha,':') + 1);
      trim(&linha);
      superior += atof(linha);
      if(sorteio <= superior){
        fclose(ptrFitness);
        desalocaCharPtr( &linha , tamLinha, "populacao::indiceIndividuoSorteado", "linha" );
        return i;
      } // fim if
    }// fim for
  fclose(ptrFitness);
  desalocaCharPtr( &linha , tamLinha, "populacao::indiceIndividuoSorteado", "linha" );
  return -1;
}
/** Método usado para aplicar mutação em um indivíduo. */
int populacao::mutacao( char * indiv ){
  int i=0, mudou=0, posMut = rand() % strlen(indiv);
  for(;mudou == 0;){
    switch( indiv[ posMut ] ) {
      case '+': indiv[posMut] = '-'; mudou = 1;    break;
      case '-': indiv[posMut] = '+'; mudou = 1;    break;
      //case '#': posMut = rand() % strlen( indiv ); break;  //escolhe outra posicao
      case ( (char) 216 ) : posMut = rand() % strlen( indiv ); break;  //escolhe outra posicao
      default:{
        int pos=0;
        mudou = 1;
        for( i = 1; posMut >= (*ctl)->inicioTipo(i); i++ );
        if( ( (*ctl)->formatoIndividuo[ i-1 ] == 'C' ) || ( (*ctl)->formatoIndividuo[ i-1 ] == 'S' ) ){
          indiv[posMut] = generateChar( (*ctl)->tipoString  );
        } // fim if
        else{
          indiv[posMut] = generateChar("n");
        } // fim else
      }//fim default
    }// fim switch
  }// fim for
  return true;
}
/** Método que aplica operador crossover nos indivíduos representados por indiv1 e indiv2 */
int populacao::crossover( char ** indiv1, char ** indiv2 ){
  int i=0, ocorre=0, posCross=0, tamTipo=0, inicTipo=0, tamFormat = 0;
  char * block = NULL, * indivAux = NULL;

  alocaCharPtr( &block , (int) ((*ctl)->tamanhoIndividuo + 5), "populacao::crossover", "block" );
  alocaCharPtr( &indivAux , (int) ((*ctl)->tamanhoIndividuo + 5), "populacao::crossover", "indivAux" );

  strcpy( indivAux, * indiv1);

  tamFormat = strlen( (*ctl)->formatoIndividuo );
  for(i=0; i<tamFormat; i++)
    {
      ocorre = rand() % 2;
      if(ocorre){    // ocorre crossover no tipo chance de 50%
        inicTipo = (*ctl)->inicioTipo(i);
        tamTipo =  (*ctl)->tamanhoTipo(i);
        posCross = (rand() % tamTipo);
        switch( (*ctl)->formatoIndividuo[i] )
          {
          case 'S':
            {
              memset( block, '\0', (int) ((*ctl)->tamanhoIndividuo + 5) );
              int maxTam=0, maxTam2=0;
              strncpy( block, * indiv1 + inicTipo, tamTipo );
              //maxTam = indexOf(block, '#');
              maxTam = indexOf(block, (char) 216);
              if(maxTam == -1)
                maxTam = tamTipo;
              memset( block, '\0', (int) ((*ctl)->tamanhoIndividuo + 5) );
              strncpy( block, * indiv2 + inicTipo, tamTipo );
              //maxTam2 = indexOf(block, '#');
              maxTam2 = indexOf(block, (char) 216);
              if(maxTam2 == -1)
                maxTam2 = tamTipo;
              if(maxTam > maxTam2)
                maxTam = maxTam2;
              if(maxTam == 0)
                posCross = 0;
              else
                posCross = (rand() % maxTam);
              break;
            }// case
          case 'C':
            {
              posCross = 0;
              break;
            }// case
          }// fim switch
        strncpy(*indiv1 +(posCross+inicTipo), *indiv2+(posCross+inicTipo), (tamTipo-posCross));
        strncpy(*indiv2 +(posCross+inicTipo), indivAux+(posCross+inicTipo), (tamTipo-posCross));
      }// fim if
    }// fim for
  //  rastro("saiu - populacao::crossover");
  desalocaCharPtr( &block , (int) ((*ctl)->tamanhoIndividuo + 5), "populacao::crossover", "block" );
  desalocaCharPtr( &indivAux , (int) ((*ctl)->tamanhoIndividuo + 5), "populacao::crossover", "indivAux" );
  return true;
}
/** Método usado para gerar o fitness da população */
int populacao::geraFitness(){
  if((*ctl)->geraLog) toFile("log_erro.log", "------geraFitness");

  char * linhaCobertura = NULL, * desempenho = NULL;
  double fitness = 0, somatoriaFitness = 0, cobertura=0;
  alocaCharPtr( &linhaCobertura , (int) ((*ctl)->quantidadeElemento + 20), "populacao::geraFitness", "linhaCobertura" );
  alocaCharPtr( &desempenho , (int) ((*ctl)->quantidadeElemento + 20), "populacao::geraFitness", "desempenho" );

  FILE * ptrFitness, * ptrCobertura;
  ptrFitness = fopen((*ctl)->arquivoFitness, "w");

  ptrCobertura = fopen((*ctl)->arquivoCoberturaIndividuo, "r");
  if(ptrCobertura == NULL)
    {
      sprintf( ErrorText,"nao abriu o arquivo de cobertura/individuo : %s", (*ctl)->arquivoCoberturaIndividuo );
      erro( ErrorText, 1 );
    }

  for (int i=0; i < (*ctl)->tamanhoPopulacao; i++){
      memset(desempenho  , '\0', (int) ( (*ctl)->quantidadeElemento + 20 ) );
      fgets(desempenho, (int) ( (*ctl)->quantidadeElemento + 20 ), ptrCobertura);

      memcpy(desempenho, desempenho + indexOf(desempenho,':') + 1, strlen(desempenho) - indexOf(desempenho,':'
));
      trim(& desempenho);
      sobrepoe(& linhaCobertura, desempenho);

      fitness = (double)numberOf(desempenho, 'X') * 100 / (double) ((*ctl)->quantidadeElemento);

      fprintf(ptrFitness,"%5d : %10.2f\n", i, fitness);
      fflush(ptrFitness);
      somatoriaFitness +=fitness;
    }// fim for
  //rastro("PONTO1.7");*/
  fclose(ptrFitness);
  fclose(ptrCobertura);
  (*ctl)->setSomatoriaFitness( somatoriaFitness );

  toFile ( (*ctl)->arquivoObsCobertura, linhaCobertura);

  desalocaCharPtr( &linhaCobertura , (int) ((*ctl)->quantidadeElemento + 20), "populacao::geraFitness", "linhaCobertura" );
  desalocaCharPtr( &desempenho , (int) ((*ctl)->quantidadeElemento + 20), "populacao::geraFitness", "desempenho" );

  if((*ctl)->geraLog) toFile("log_erro.log", "------saindo geraFitness");

  return true;
}
/** Método usado para realizar evolução por elitismo. */
int populacao::evolucaoPorElitismo(){
  if((*ctl)->geraLog) toFile("log_erro.log", "------evolucaoIneditismo");

  int contador = 0;
  double posicao = 0;

  individuo * indiv1 = new individuo( &(*ctl) );

  /*prova*/
  //toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR INEDITISMO (%0.0f)", (*ctl)->quantidadeIneditismo);
  //toFile("evolucao.fil", ErrorText);
  /**/
  for(contador = (int)( (*ctl)->quantidadeFitness /*+ (*ctl)->quantidadeElitismo*/ ); contador < (int) ( (*ctl)->quantidadeFitness + (*ctl)->quantidadeElitismo  ); )
    {
      posicao = melhorFitAntNaoEm( (*ctl)->arquivoPopulacaoTemporario );
      if (posicao != -1){
        indiv1->load( (int) posicao );
        /*prova*/
        sprintf(ErrorText, " Ineditismo do indiv pos %0.0f : %s", posicao, indiv1->representacao);
        //toFile("evolucao.fil", ErrorText);
        /**/
      }
      else{
        indiv1->novo();
        /*prova*/
	  sprintf(ErrorText, " Ineditismo do novo indiv : %s", indiv1->representacao);
	  //toFile("evolucao.fil", ErrorText);
	  /**/
	}
      if ( toPopulacao( contador , indiv1->representacao, (*ctl)->arquivoPopulacaoTemporario ) )
	{
	  contador ++;
	  /*prova*/
	  sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, indiv1->representacao);
	  //toFile("evolucao.fil", ErrorText);
	  /**/
	}
    } // fim for ineditismo
  if((*ctl)->geraLog) toFile("log_erro.log", "------saindo evolucaoIneditismo");
  delete ( indiv1 );
  return true;

}

/** Metodo usado para obter o indice do individuo a ser mantido */
double populacao::melhorInedAntNaoEm ( char * arquivoAuxiliar ){
  FILE * ptrIneditismo;
  individuo * indiv = new individuo( &(* ctl) );

  ptrIneditismo = fopen( (*ctl)->arquivoIneditismo, "r" );
  if(ptrIneditismo == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de Ineditismo corretamente : %s", (*ctl)->arquivoIneditismo);
    erro(ErrorText, 1);
  }
  int pos2p = 0;

  double posMelhor = -1, pos = 0, ineditismo = 0, ineditismoMelhor = -1;

  char * linha = NULL;
  int tamLinha = 100;
  alocaCharPtr( &linha , tamLinha, "populacao::melhorInedAntNaoEm", "linha" );
  //while(! feof(ptrIneditismo) )
  for( int cont = 0; cont < (*ctl)->tamanhoPopulacao; cont ++ ){
    memset(linha, '\0', 100);
    fgets(linha,  100, ptrIneditismo);
    pos2p = indexOf(linha, ':');
    if(pos2p != -1){
      strcpy( linha, linha + pos2p + 1);
      trim  ( & linha );
      ineditismo = atof( linha );
      indiv->load( cont );
      if ( (ineditismo > ineditismoMelhor) && (!inPopulacao(indiv->representacao, arquivoAuxiliar) ) ){
        posMelhor = cont;
        ineditismoMelhor = ineditismo;
      }
    } // fim if
  }// fim for
  fclose(ptrIneditismo);
  desalocaCharPtr( &linha , tamLinha, "populacao::melhorInedAntNaoEm", "linha" );
  delete ( indiv );
  return posMelhor;
}
/** Metodo usado para obter o indice do individuo a ser mantido */
double populacao::melhorFitAntNaoEm( char * arquivoAuxiliar ){
   FILE * ptrFitness;
   individuo * indiv = new individuo( &(* ctl) );

   ptrFitness = fopen( (*ctl)->arquivoFitness, "r" );
   if(ptrFitness == NULL){
       sprintf(ErrorText, "nao abriu o arquivo de Fitness corretamente : %s", (*ctl)->arquivoFitness);
       erro(ErrorText, 1);
      }
   int pos2p = 0;
   double posMelhor = -1, pos = 0, fit = 0, fitMelhor = -1;

   char * linha = NULL;
   int tamLinha = 100;
   alocaCharPtr( &linha , tamLinha, "populacao::melhorFitAntNaoEm", "linha" );

   for( int cont = 0; cont < (*ctl)->tamanhoPopulacao; cont ++ ){
      memset(linha, '\0', tamLinha);
      fgets(linha,  tamLinha, ptrFitness);
      pos2p = indexOf(linha, ':');
      if(pos2p != -1){
         strcpy(linha, linha + pos2p + 1);
         trim( & linha);
         fit = atof( linha );
         indiv->load( cont );
         if ( (fit > fitMelhor) && (!inPopulacao(indiv->representacao, arquivoAuxiliar) ) ){
            posMelhor = cont;
            fitMelhor = fit;
            }
         } // fim if
      }// fim for
   fclose(ptrFitness);
   desalocaCharPtr( &linha , tamLinha, "populacao::melhorFitAntNaoEm", "linha" );
   return posMelhor;
}

/** Método usado para calcular o ineditismo da população. */
int populacao::geraBonusIneditismo(){

  if( (*ctl)->geraLog) toFile("log_erro.log", "------geraIneditismo");
  char * elemCobertura = NULL;
  int contador=0, cont=0, lixo=0, ponto2=0, quantCob=0;
  double tamElCob = 0, bonificacao = 0;
  FILE * ptrCobertura, * ptrBonusIneditismo;
  int pesoIneditismo = 2;
  tamElCob = (*ctl)->tamanhoPopulacao + 20;

  alocaCharPtr( &elemCobertura , (int)tamElCob, "populacao::geraIneditismo", "elemCobertura" );

  ptrBonusIneditismo = fopen( (*ctl)->arquivoBonusIneditismo,"w");
  ptrCobertura   = fopen( (*ctl)->arquivoCoberturaElemento ,"r");
  if ( ptrCobertura == NULL ){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura de Elementos corretamente : %s", (*ctl)->arquivoCoberturaElemento);
    erro(ErrorText,1);
  }
  printf("\n<populacao::geraIneditismo> Calculando ineditismo para os elementos\n");
  for (contador = 0; contador < (*ctl)->quantidadeElemento; contador++){
    printf("*");
    memset(elemCobertura, '\0', (int) tamElCob );
    fgets(elemCobertura, ( (int) tamElCob) -1, ptrCobertura);
    ponto2 = indexOf(elemCobertura,':');
    strcpy(elemCobertura, elemCobertura + ponto2 + 1);
    trim(&elemCobertura);
    /** /
    if(ctl->pausaGeracao)
    {
      printf("\n linha lida tam %d / tamPopulacao %d \n<%s>", (int) ctl->tamanhoPopulacao, strlen(elemCobertura), elemCobertura);
      //pprova("Analisar, aqui deu pau por terem tamanhos diferentes...");
    }
    /**/

    if( strlen(elemCobertura) != (*ctl)->tamanhoPopulacao ){
      sprintf(ErrorText, "Erro no calculo da bonificacao p/Elemento %d\nTamanho da linha de cobertura do Elemento = %d, deveria ser %0.0f \n linha de cobertura : '%s'", contador, strlen(elemCobertura), (*ctl)->tamanhoPopulacao, elemCobertura);
      erro(ErrorText , 1);
    }

    bonificacao = 0;
    quantCob = numberOf(elemCobertura, 'X');
    if(quantCob)
      bonificacao = 100 * ( 1 - ( quantCob / (*ctl)->tamanhoPopulacao ) );
    fprintf(ptrBonusIneditismo,"%5d : %10.2f\n", contador, bonificacao);
    fflush(ptrBonusIneditismo);
  }// fim for

  fclose(ptrBonusIneditismo);
  fclose(ptrCobertura);

  desalocaCharPtr( &elemCobertura , tamElCob, "populacao::geraIneditismo", "elemCobertura" );

  if((*ctl)->geraLog) toFile("log_erro.log", "------saindo geraIneditismo");
  return true;
}
/** Método usado para calcular a cobertura dos elementos, com base na cobertura dos indivíduos. */
int populacao::geraCoberturaElementos(){
//  Luciano Petinati Ferreira
//  data : 17/07/2002
//  hora : 22:00
//  Testado 1 vez
  if((*ctl)->geraLog) toFile("log_erro.log", "***------geraCoberturaElementos");
  char * linhaCobInd = NULL, * linhaCobElem = NULL;
  int contador=0, cont=0, lixo=0, ponto2=0;
  FILE * ptrCobInd, * ptrCobElem;
  alocaCharPtr( &linhaCobInd , (int)((*ctl)->quantidadeElemento + 20 ), "populacao::geraCoberturaElemento", "linhaCobInd" );
  alocaCharPtr( &linhaCobElem , (int)((*ctl)->tamanhoPopulacao + 20 ), "populacao::geraCoberturaElemento", "linhaCobElem" );

  ptrCobElem = fopen((*ctl)->arquivoCoberturaElemento  ,"w");
  ptrCobInd  = fopen((*ctl)->arquivoCoberturaIndividuo ,"r");
  if (ptrCobInd == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura corretamente : %s", (*ctl)->arquivoCoberturaIndividuo);
    erro(ErrorText,1);
  }

  for (contador = 0; contador < (*ctl)->quantidadeElemento; contador++){
    rewind( ptrCobInd );
    memset(linhaCobElem , '\0', (int) ((*ctl)->tamanhoPopulacao + 20 ));

    for (cont = 0; cont < (int) ((*ctl)->tamanhoPopulacao); cont++){
      memset( linhaCobInd, '\0', (int) ((*ctl)->quantidadeElemento + 20 ) );
      fgets ( linhaCobInd, (int) ((*ctl)->quantidadeElemento + 20 ), ptrCobInd );
      ponto2 = indexOf(linhaCobInd,':');
      strcpy(linhaCobInd, linhaCobInd + ponto2 + 1);
      trim(&linhaCobInd);

      if( strlen(linhaCobInd) == (*ctl)->quantidadeElemento ){
        trim(& linhaCobInd);
        linhaCobElem[cont] = linhaCobInd[contador];
      }
    }// fim for
    /** /
    if (ctl->pausaGeracao)
    {
    printf("\n Vai gravar no arquivo ce cobertura do elemento:");
    pprova(linhaCobElem);
    }
/**/
    if( strlen(linhaCobElem) != (*ctl)->tamanhoPopulacao ){
      sprintf(ErrorText, "populacao::geraCoberturaElementos - Cobertura do elemento gerada errada para o elm %d - ", contador);
      erro(ErrorText, 1);
      }
    fprintf( ptrCobElem,"%5d : %s\n", contador, linhaCobElem );
    fflush( ptrCobElem );
  }// fim for

  fclose( ptrCobElem );
  fclose( ptrCobInd  );
  desalocaCharPtr( &linhaCobInd , (int)((*ctl)->quantidadeElemento + 20 ), "populacao::geraCoberturaElemento", "linhaCobInd" );
  desalocaCharPtr( &linhaCobElem , (int)((*ctl)->tamanhoPopulacao + 20 ), "populacao::geraCoberturaElemento", "linhaCobElem" );

  if((*ctl)->geraLog) toFile("log_erro.log", "***------saindo geraCoberturaElementos");

  return true;
}
/** Método usado para evoluir população com base no índice de ineditismo do indivíduo. */
int populacao::evolucaoPorIneditismo(){
  if((*ctl)->geraLog) toFile("log_erro.log", "------evolucaoIneditismo");

  int contador = 0;
  double posicao = 0;
  individuo * indiv1 = new individuo( & (*ctl) );
  /*prova*/
  //toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR INEDITISMO (%0.0f)", (*ctl)->quantidadeIneditismo);
  //toFile("evolucao.fil", ErrorText);
  /**/
  for(contador = (int)( (*ctl)->quantidadeFitness + (*ctl)->quantidadeElitismo ); contador < (int) ( (*ctl)->quantidadeFitness + (*ctl)->quantidadeElitismo + (*ctl)->quantidadeIneditismo ); ){
    posicao = melhorInedAntNaoEm( (*ctl)->arquivoPopulacaoTemporario );
    if (posicao != -1){
      indiv1->load( (int) posicao );
      /*prova*/
      sprintf(ErrorText, " Ineditismo do indiv pos %0.0f : %s", posicao, indiv1->representacao);
      //toFile("evolucao.fil", ErrorText);
      /**/
    }
    else{
      indiv1->novo();
      /*prova*/
      sprintf(ErrorText, " Ineditismo do novo indiv : %s", indiv1->representacao);
      //toFile("evolucao.fil", ErrorText);
      /**/
    }
    if ( toPopulacao( contador , indiv1->representacao, (*ctl)->arquivoPopulacaoTemporario ) ){
      contador ++;
      /*prova*/
      sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, indiv1->representacao);
      //toFile("evolucao.fil", ErrorText);
      /**/
    }
  } // fim for ineditismo
  if((*ctl)->geraLog) toFile("log_erro.log", "------saindo evolucaoIneditismo");
  delete(indiv1);
  return true;
}
/** Método usado para gerar um arquivo que reflita os dados de uma população de forma entendível/decodificada. */
int populacao::decodificaPopulacao(char * origem, char * destino){
   if((*ctl)->geraLog) toFile("log_erro.log", "---decodificaPopulacao");
   FILE * ptrPopulacao, * ptrPopRes;
   char   * block = NULL, * block_aux = NULL, * gene = NULL;

   individuo * indiv = NULL;
   indiv = new individuo( &(*ctl) );

  int    tamFormato = strlen((*ctl)->formatoIndividuo), inicBlock, pos;
  int    geneTam = 0, tamBloco = 30;

  geneTam = (int) ( (*ctl)->tamanhoIndividuo + 20 );

  if((*ctl)->tamanhoMaximoString > tamBloco)
    tamBloco = (int) (*ctl)->tamanhoMaximoString;

  ptrPopulacao = fopen(origem, "r");
  if (ptrPopulacao == NULL){
      sprintf(ErrorText,"nao abriu o arquivo de populacao corretamente : %s", origem);
      erro(ErrorText,1);
    }
  ptrPopRes = fopen(destino, "w");
  alocaCharPtr( &block , tamBloco, "decodificaPopulacao", "block");
  alocaCharPtr( &block_aux , tamBloco, "decodificaPopulacao", "block_aux");
  alocaCharPtr( &gene , geneTam, "decodificaPopulacao", "gene");

  for (int contador = 1; !feof(ptrPopulacao); contador++){
      memset(gene, '\0', geneTam);
      fgets(gene, geneTam, ptrPopulacao);
      trim( & gene);
      if( strcmp(gene,"") != 0 ){
         strcpy(gene, gene + indexOf(gene, ':')+1);
         trim( & gene);
         for (int i = 0; i < tamFormato ; i++){
            inicBlock = (*ctl)->inicioTipo(i);
            memset( block,     '\0', tamBloco );
            memset( block_aux, '\0', tamBloco );
            memcpy( block, gene+inicBlock, (*ctl)->tamanhoTipo(i) );
            switch( (*ctl)->formatoIndividuo[i] ){
               case 'I': sprintf(block_aux,"%d", indiv->decode_block_int(block) ); break;
               case 'D': sprintf(block_aux,"%f", indiv->decode_block_double(block) ); break;
               case 'F': sprintf(block_aux,"%f", indiv->decode_block_float(block) ); break;
               case 'S':
               {
                  //pos = indexOf(block,'#');
                  pos = indexOf(block, (char) 216);
                  if(pos == 0) printf ("Valor do argumento string eh vazio... avaliar impacto");
                  if(pos != -1) block[pos] = '\0';
                  strcpy(block_aux, block );
                  break;
               }
               case 'C':
               {
                  memset(block_aux, '\0', tamBloco);
                  strcpy(block_aux, block);
                  break;
               }
            }// fim switch
            fprintf(ptrPopRes, "%s", block_aux);
            if( i != tamFormato - 1 )
               fprintf(ptrPopRes, ", ");
            }//fim for
         fprintf(ptrPopRes, "\n");
         fflush (ptrPopRes);
      } // fim if gene == ""
  } // fim for
  fclose(ptrPopRes);
  fclose(ptrPopulacao);
  desalocaCharPtr( &block , tamBloco, "decodificaPopulacao", "block");
  desalocaCharPtr( &block_aux , tamBloco, "decodificaPopulacao", "block_aux");
  desalocaCharPtr( &gene , geneTam, "decodificaPopulacao", "gene");

  if((*ctl)->geraLog) toFile("log_erro.log", "---decodificaPopulacao");
  return true;
}
/** Este método é usado para limpar e regerar o diretório de pool e seus arquivos.
Os arquivos são gerados para serem importados e executados para serem avaliados */
int populacao::geraPool(){
   //Recriando o diretorio de pool.
   sprintf(Comando, TDS_PATH"removeFile.sh %s; mkdir %s ", (*ctl)->diretorioPool , (*ctl)->diretorioPool);
   (*ctl)->setComandPath(Comando);
   system( (*ctl)->comandPath );


   //gerando arquivos
   int tamFormato = strlen((*ctl)->formatoIndividuo);
   char * arqTecN = NULL, * arqInputN = NULL;
   alocaCharPtr( &arqTecN , 200, "geraPool", "arqTecN");
   alocaCharPtr( &arqInputN , 200, "geraPool", "arqInputN");

   individuo * indiv = NULL;
   indiv = new individuo(& (*ctl) );

   char * argMascarado  = NULL;
   alocaCharPtr( &argMascarado,  (int) ( (*ctl)->tamanhoMaximoArgumento ), "geraPool", "argMascarado" );
   char * argPuroStr = NULL;
   alocaCharPtr (&argPuroStr, (int) ( (*ctl)->tamanhoMaximoArgumento ), "geraPool", "argPuroStr" );

   FILE * tecF, * inputF;

   for (int contador = 1; contador <= (*ctl)->tamanhoPopulacao; contador++){
      memset(arqTecN, '\0', 200);
      sprintf(arqTecN, "%stec%d.tes", (*ctl)->diretorioPool, contador);
      tecF = fopen(arqTecN,"w");

      memset(arqInputN , '\0', 200);
      sprintf(arqInputN, "%sinput%d.tes", (*ctl)->diretorioPool, contador);
      inputF = fopen(arqInputN, "w");

      indiv->load(contador -1);

      for (int i = 0; i < tamFormato ; i++){
         //inicBlock = (*ctl)->inicioTipo(argCont);
         memset( argMascarado,     '\0', (int) (*ctl)->tamanhoMaximoArgumento );
         memset( argPuroStr  ,     '\0', (int) (*ctl)->tamanhoMaximoArgumento );
         memcpy( argMascarado, indiv->representacao + ( (*ctl)->inicioTipo( i ) ), (*ctl)->tamanhoTipo( i ) );
         argMascarado[ (int) (*ctl)->tamanhoMaximoArgumento  - 1] = '\0'; //Modelo

         switch( (*ctl)->formatoIndividuo[i] ){
            case 'I': sprintf(argPuroStr,"%d", indiv->decode_block_int(argMascarado) );    break;
            case 'D': sprintf(argPuroStr,"%f", indiv->decode_block_double(argMascarado) ); break;
            case 'F': sprintf(argPuroStr,"%f", indiv->decode_block_float(argMascarado) );  break;
            case 'C': strcpy(argPuroStr, argMascarado); 	                               break;
            case 'S':{
               int pos = indexOf(argMascarado, (char) 216);
               if(pos == 0) printf ("Valor do argumento string eh vazio...ignorando... avaliar impacto");
               if(pos != -1) argMascarado[pos] = '\0';
               strcpy(argPuroStr, argMascarado );
               break;
               }

            }// fim switch
         if( i < (*ctl)->numeroArgumentos ){
            fprintf(inputF, "%s\n", argPuroStr);
            fflush(inputF);
            }
            else{
            fprintf(tecF, "%s\n", argPuroStr);
            fflush(tecF);
            }
         }//fim for
      fclose(tecF);
      fclose(inputF);
    } // fim for

   //Importanto os arquivos...
   if( (*ctl)->geracaoAtual > 0){
      sprintf(Comando, "tcase -d testSection");
      (*ctl)->setComandPath(Comando);
      system( (*ctl)->comandPath );
    }
    sprintf( Comando, "tcase -poke -E exe -DD %s -f 1 -t %d testSection", (*ctl)->diretorioPool, (*ctl)->tamanhoPopulacao );
    (*ctl)->setComandPath(Comando);
    system( (*ctl)->comandPath );

   desalocaCharPtr( &arqTecN , 200, "geraPool", "arqTecN");
   desalocaCharPtr( &arqInputN , 200, "geraPool", "arqInputN");
   desalocaCharPtr( &argMascarado,  (int) ( (*ctl)->tamanhoMaximoArgumento ), "geraPool", "argMascarado" );
   desalocaCharPtr (&argPuroStr, (int) ( (*ctl)->tamanhoMaximoArgumento ), "geraPool", "argPuroStr" );

   return true;

} // fim geraPool
/** Este método retorna o valor do bonus para os indivíduos que cobriram o elemento informado por pos. */
double populacao::getBonusElemento(int pos){

   int i = 0;
   char * gene = NULL, * bonificacaoStr = NULL;
   FILE * ptrBonusIneditismo = NULL;
   double bonificacao = 0;

   ptrBonusIneditismo = fopen( (*ctl)->arquivoBonusIneditismo, "r");
   if(ptrBonusIneditismo == NULL){
      sprintf( ErrorText,"populacao::getBonusElemento - Nao abriu corretamente o arquivo  : %s", (*ctl)->arquivoCoberturaIndividuo );
      erro( ErrorText, 1 );
    }
    if(pos >= (*ctl)->quantidadeElemento){
      sprintf(ErrorText,"Pos, %d, extrapolou o indice do elemento buscado %f", pos, (*ctl)->quantidadeElemento);
      erro(ErrorText ,1);
    }
    int tamLinha = 100;

    alocaCharPtr( &gene, tamLinha, "getBonusElemento", "gene");
    alocaCharPtr( &bonificacaoStr, tamLinha, "getBonusElemento", "bonificacaoStr");

   for (i = 0; i <= pos; i++){
      memset(gene, '\0', tamLinha);
      try{
         fgets(gene, tamLinha, ptrBonusIneditismo);
      }
      catch(...){
         erro("Estouro de memoria ao tentar recuperar bonus do arquivo de populacao para var gene, metodo load",1);
      }

   }// fim for

   trim ( & gene);
   try{
      i = indexOf(gene, ':') + 1;
      strcpy(bonificacaoStr, gene + i );
      trim ( & bonificacaoStr);
      bonificacao = atof( bonificacaoStr);
   }
   catch(...){
      erro("Estouro de memoria ao tentar recuperar individuo da linha do arquivo de populacao , metodo load",1);
   }

   desalocaCharPtr( &gene, tamLinha, "getBonusElemento", "gene");
   desalocaCharPtr( &bonificacaoStr, tamLinha, "getBonusElemento", "bonificacaoStr");

   fclose(ptrBonusIneditismo);
   return bonificacao;

}
/** Gera o arquivo com a bonificação final por ineditismo. */
int populacao::geraIneditismoPopulacao(){
//  Luciano Petinati Ferreira
//  data : 17/07/2002
//  hora : 22:00
//  Testado 1 vez
  if((*ctl)->geraLog) toFile("log_erro.log", "---------geraIneditismoPopulacao");
  char * linhaCobInd = NULL;
  int cont=0, ponto2=0;
  double ineditismo = 0;
  FILE * ptrCobInd, * ptrIneditismo;

  alocaCharPtr( &linhaCobInd , (int)((*ctl)->quantidadeElemento + 20 ), "populacao::geraIneditismoPopulacao", "linhaCobInd" );

  ptrIneditismo = fopen((*ctl)->arquivoIneditismo  ,"w");
  ptrCobInd  = fopen((*ctl)->arquivoCoberturaIndividuo ,"r");

  if (ptrCobInd == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura corretamente : %s", (*ctl)->arquivoCoberturaIndividuo);
    erro(ErrorText,1);
  }
  for (cont = 0; cont < (int) ((*ctl)->tamanhoPopulacao); cont++){
     memset( linhaCobInd, '\0', (int) ((*ctl)->quantidadeElemento + 20 ) );
     fgets ( linhaCobInd, (int) ((*ctl)->quantidadeElemento + 20 ), ptrCobInd );
     ponto2 = indexOf(linhaCobInd,':');
     strcpy(linhaCobInd, linhaCobInd + ponto2 + 1);
     trim(&linhaCobInd);
     ineditismo = 0;

     if( strlen(linhaCobInd) != (*ctl)->quantidadeElemento ){
        sprintf(ErrorText, "populacao::geraIneditismoPopulacao - Cobertura do individuo gerada errada para o individuo %d - ", cont);
        erro(ErrorText, 1);
        }

     for (int i = 0; i < (*ctl)->quantidadeElemento; i++){
        if ( *( linhaCobInd +i) == 'X')
            ineditismo += getBonusElemento( i );
     }// fim for

     fprintf( ptrIneditismo, "%5d : %f\n", cont, ineditismo );
     fflush( ptrIneditismo );

     }// fim for
  fclose( ptrIneditismo );
  fclose( ptrCobInd  );

  desalocaCharPtr( &linhaCobInd , (int)((*ctl)->quantidadeElemento + 20 ), "populacao::geraIneditismoPopulacao", "linhaCobInd" );
  if((*ctl)->geraLog) toFile("log_erro.log", "---------saindo geraIneditismoPopulacao");

  return true;
}
