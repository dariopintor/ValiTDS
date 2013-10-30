/***************************************************************************
                          ferramenta.cpp  -  description
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

#include "ferramenta.h"

/** No descriptions */
ferramenta::ferramenta(central ** parCtl){
   //cout << "\nConstruindo ferramenta...";
   ctl = parCtl;
}
ferramenta::~ferramenta(){
   //cout << "\nDestruindo ferramenta...";
   ctl = NULL;
}

//_________________________________________________________________

/** Método usado para inicar a ferramenta adequada baseado nas informações de controle contidas em ctl. */
int ferramenta::prepareTool(){
	char *mpi_root;
   if(strcmp((*ctl)->criterioTeste, "Analise de Mutantes") != 0)
    { //se for poketo#export POKEBIN=/home/especial/auri/ferramentas/poketool/bin

      (*ctl)->setEnviroment(SET_VALIMPI);
      cout <<"\nUtilizando ValiMPI." << "\n\nObs.: configure VALIMPI_ROOT.";
      
//      system((*ctl)->enviroment.valor);
      mpi_root = getenv("VALIMPI_ROOT");
      
      sprintf(Comando, "vali_inst %s > lixo.lxo", (*ctl)->arquivoFonte);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );
      
      sprintf(Comando, "vali_reduce . %s_instrumentado.c $VALIMPI_ROOT/vali_inst/PSincWords.cfg $VALIMPI_ROOT/vali_inst/shared.var > lixo.lxo" 
      , (*ctl)->arquivoFonte);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );
      
      sprintf(Comando, "vali_elem %d %s > lixo.lxo", (*ctl)->nProcess,(*ctl)->funcoes);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );
      
      
      sprintf(Comando, "vali_cc %s_instrumentado.c -o exe %s", (*ctl)->arquivoFonte,(*ctl)->ccargs);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );
    } // fim if se for para ValiMPI
  else
    { //se for proteum
      (*ctl)->setEnviroment(SET_PROTEUM);

      cout <<"\nUtilizando Proteum." << "\n\nObs.: configure PATH e PROTEUM14HOME.";
      sprintf(Comando, "mkdir %s", (*ctl)->diretorio);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );
      //COPIANDO O PROGRAMA PARA testeprog.c
      sprintf(Comando, "cp ValiMPITest/%s testeprog.c", (*ctl)->arquivoFonte);
      (*ctl)->setComandPath( Comando );
      system( (*ctl)->comandPath );

      //COMPILANDO O PROGRAMA testeprog.c GERANDO EXECUTAVEL exe
      (*ctl)->setComandPath( "gcc testeprog.c -o exe" );
      system( (*ctl)->comandPath );

      //CRIANDO SEÇAO DE TESTE testSection
      //system("/home/especial/auri/ferramentas/proteum1.4.1/LINUX/bin/test-new -research -S testeprog -E exe -C \"gcc testeprog.c -o exe\" testSection");
      (*ctl)->setComandPath( "test-new -research -S testeprog -E exe -C \"gcc testeprog.c -o exe\" testSection" );
      cout << "\n\n" << (*ctl)->comandPath << "\n\n";
      system( (*ctl)->comandPath );

      //GERANDO OS MUTANTES DE testeprog.c
      //system("/home/especial/auri/ferramentas/proteum1.4.1/LINUX/bin/muta-gen -all 100 testSection");
      (*ctl)->setComandPath( "muta-gen -all 100 testSection" );
      system( (*ctl)->comandPath );

      //GERANDO RELATORIO
      //system("/home/especial/auri/ferramentas/proteum1.4.1/LINUX/bin/report -tcase testSection");
      (*ctl)->setComandPath( "report -tcase testSection" );
      system( (*ctl)->comandPath );

    } //fim if se for proteum

  return true;
}
//_________________________________________________________________

/** Método usado para obter a quantidade de elementos requeridos pelo critério configurado. */
double ferramenta::obtemElementosRequeridos(){
   cout << "\n\nObtendo elementos requeridos";
  if(strcmp((*ctl)->criterioTeste, "Analise de Mutantes") != 0 )
    {
      return obtemElementosRequeridosValiMPI();
    }
  else
    {
      return obtemElementosRequeridosProteum();
    }
}
//_________________________________________________________________

/** Método usado para obter a quantidade de elementos requeridos para
critérios suportados pela ferramenta ValiMPI. */
double ferramenta::obtemElementosRequeridosValiMPI(){
   cout << "\n---obtemElementosValiMPI";
   double res = 0;
   char * arquivoElementos = NULL, * anterior = NULL, * auxiliar = NULL;
   char dir_elem_req[] = "valimpi/res/";

   alocaCharPtr( &arquivoElementos, 500, "obtemElementosRequeridosValiMPI", "arquivoElemntos");
   alocaCharPtr( &anterior, 500, "obtemElementosRequeridosValiMPI", "anterior");
   alocaCharPtr( &auxiliar, 500, "obtemElementosRequeridosValiMPI", "auxiliar");
   
   FILE * ptrArquivoElementos;
   memset(arquivoElementos, '\0', 500);
   if(strcmp((*ctl)->criterioTeste,"Todos os Arcos")==0)                         // arcs
   {
      sprintf(arquivoElementos, "%stodas-arestas.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todas-arestas");
   } else
   if(strcmp((*ctl)->criterioTeste,"Todos os Nos")==0)                                // nos
   {
      sprintf(arquivoElementos, "%stodos-nos.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-nos");
   }/* else
   if(strcmp((*ctl)->criterioTeste,"Todos os Potenciais Usos/du-Caminhos")==0)    // pudu
   {
      sprintf(arquivoElementos, "%stodos-p-usos.req", (*ctl)->diretorio);
      (*ctl)->setCriterioTesteValiMPI ("pudu");
   }*/ else
   if(strcmp((*ctl)->criterioTeste,"Todos os Potenciais Usos")==0)            // pu
   {
      sprintf(arquivoElementos, "%stodos-p-usos.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-p-usos");
   } /*else
   if(strcmp((*ctl)->criterioTeste,"Todos os Potenciais du-Caminhos")==0) // pdu
   {
      sprintf(arquivoElementos, "%spdupaths.tes", (*ctl)->diretorio);
      (*ctl)->setCriterioTesteValiMPI ("pdu");
   }*/else
   if(strcmp((*ctl)->criterioTeste,"Todos os Usos Computacionais")==0)            
   {
      sprintf(arquivoElementos, "%stodos-c-usos.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-c-usos");
   }else
   if(strcmp((*ctl)->criterioTeste,"Todos os Usos de Sincronismo")==0)            
   {
      sprintf(arquivoElementos, "%stodos-s-usos.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-s-usos");
   }else
   if(strcmp((*ctl)->criterioTeste,"Todos os Nos S")==0)            
   {
      sprintf(arquivoElementos, "%stodos-nosS.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-nosS");
   }else
   if(strcmp((*ctl)->criterioTeste,"Todos os Nos R")==0)            
   {
      sprintf(arquivoElementos, "%stodos-nosR.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todos-nosR");
   }else
   if(strcmp((*ctl)->criterioTeste,"Todos as Arestas S")==0)            
   {
      sprintf(arquivoElementos, "%stodas-arestasS.req", dir_elem_req);
      (*ctl)->setCriterioTesteValiMPI ("todas-arestasS");
   }

   ptrArquivoElementos = fopen(arquivoElementos,"r");

   if (ptrArquivoElementos == NULL)
   {
      sprintf(ErrorText,"nao abriu o arquivo dos elementos requeridos da ValiMPI corretamente : %s", arquivoElementos);
      erro(ErrorText,1);
   }

   /*ate aqui beleza...*/
   for (; ( !feof( ptrArquivoElementos ) ); )
   {
      strcpy(anterior, auxiliar);
      memset(auxiliar, '\0', 500);
      fgets(auxiliar, 500, ptrArquivoElementos);
      trim( & auxiliar);
   } // fim for

   int carEspecial = -1;
   /*if(strcmp((*ctl)->criterioTeste,"Todos os Nos")==0)
   {
      //todos os nos...
      for( ; (carEspecial = indexOf(anterior,' ')) != -1 ; )
      {
         strcpy(anterior, anterior + carEspecial + 1);
         trim( & anterior);
      }
   }// fim if
   else
   {*/
      // demais criterios
      carEspecial = indexOf(anterior, ')');
      anterior[carEspecial] = '\0';
   //}  fim else
   fclose(ptrArquivoElementos);
   res = atof(anterior);
   desalocaCharPtr( &arquivoElementos, 500,  "obtemElementosRequeridosValiMPI", "arquivoElemntos");
   desalocaCharPtr( &anterior, 500, "obtemElementosRequeridosValiMPI", "anterior");
   desalocaCharPtr( &auxiliar, 500, "obtemElementosRequeridosValiMPI", "auxiliar");

   printf("---Saindo de obtemElementosValiMPI");
   return res;
}
//_________________________________________________________________

/** Método usado para obter a quantidade de elementos requeridos para
critérios suportados pela ferramenta Proteum. */
double ferramenta::obtemElementosRequeridosProteum(){
   (*ctl)->setComandPath("grep 'TOTAL MUTANTS' testSection.lst > temp.tst");
   system( (*ctl)->comandPath );
   FILE * temp = NULL;
   char * linha = NULL;
   double res = 0;
   alocaCharPtr( &linha, 100, "obtemElementosRequeridosProteum", "linha");

   temp = fopen ("temp.tst", "r");
   if(temp == NULL)
   {
      sprintf(ErrorText,"nao abriu o arquivo corretamente : %s", "temp.tst");
      erro(ErrorText,1);
   }
   fgets(linha, 100, temp);
   strcpy(linha, linha + 19);
   trim ( & linha);

   fclose(temp);
   (*ctl)->setComandPath(TDS_PATH"removeFile.sh temp.tst");
   system( (*ctl)->comandPath );
   
   res = atof(linha);
   desalocaCharPtr( &linha, 100, "obtemElementosRequeridosProteum", "linha");
   return res;
}
/** Método usado para avaliar o nro-esimo indivíduo da população.

  Recupera o nro-esimo indivíduo da população;
  Recupera os argumentos/entradas que este representa;
  Separa os argumentos (argumento de chamada ou entrada de teclado) conforme necessidade do programa;
  Executa o programa e avalia o resultado da execução.
 */
int ferramenta::evaluateIndividual(int nro){
   int    tamFormato = strlen((*ctl)->formatoIndividuo);
   long   tamLinhaArgumento = (long) ( ((*ctl)->tamanhoMaximoArgumento + 2 ) * (*ctl)->numeroArgumentos + (*ctl)->numeroArgumentos );
   char * linhaArgumento = NULL;
   if (tamLinhaArgumento == 0) tamLinhaArgumento = 5;
   alocaCharPtr( &linhaArgumento,  (int) ( tamLinhaArgumento ), "evaluateIndividual", "linhaArgumento" );
   //strcpy (linhaArgumento, "");
   FILE * ptrTeclado = NULL;
   if (tamFormato > (*ctl)->numeroArgumentos)
      ptrTeclado = fopen("entrada.kyb","w");

   char * argMascarado  = NULL;
   alocaCharPtr( &argMascarado,  (int) ( (*ctl)->tamanhoMaximoArgumento ), "evaluateIndividual", "argMascarado" );

   char * argPuroStr = NULL;
   alocaCharPtr (&argPuroStr, (int) ( (*ctl)->tamanhoMaximoArgumento ), "evaluateIndividual", "argPuroStr" );
   int inicBlock = -1;

   individuo * indiv = new individuo( &(*ctl) );
   indiv->load( nro );

   // Preparando linhaArgumento - contem os valores passados por argumento.
   // Preparando entrada.kyb    - contem os valores entrados por teclado.

   for(int argCont = 0; argCont < tamFormato; argCont ++)
   {
      // para cada argumento/tipo do individuo
      inicBlock = (*ctl)->inicioTipo(argCont);
      memset( argMascarado,     '\0', (int) (*ctl)->tamanhoMaximoArgumento );
      memset( argPuroStr  ,     '\0', (int) (*ctl)->tamanhoMaximoArgumento );
      memcpy( argMascarado, indiv->representacao + inicBlock, (*ctl)->tamanhoTipo(argCont) );
      argMascarado[ (int) (*ctl)->tamanhoMaximoArgumento  - 1] = '\0'; //Modelo

      switch( (*ctl)->formatoIndividuo[argCont] )
      {
         case 'I': sprintf(argPuroStr,"%d", indiv->decode_block_int(argMascarado) );    break;
         case 'D': sprintf(argPuroStr,"%f", indiv->decode_block_double(argMascarado) ); break;
         case 'F': sprintf(argPuroStr,"%f", indiv->decode_block_float(argMascarado) );  break;
         case 'C': strcpy(argPuroStr, argMascarado); 	                               break;
         case 'S':
         {
            int pos = indexOf(argMascarado, (char) 216);
            if(pos == 0) printf ("Valor do argumento string eh vazio...ignorando... avaliar impacto");
            if(pos != -1) argMascarado[pos] = '\0';
            strcpy(argPuroStr, argMascarado );
            break;
         }

      }// fim switch

      if(argCont < (*ctl)->numeroArgumentos)
      {
         sprintf(ErrorText, "Entrada %d recuperado: %s - Argumento de chamada", argCont, argPuroStr);
         if ( argCont == 0 ){
            strcpy(linhaArgumento, argPuroStr);
         }
         else{
            strcat(linhaArgumento, argPuroStr);
         }
         strcat(linhaArgumento, " ");
      }
      else
      {
         sprintf(ErrorText, "Entrada %d recuperado: %s - Teclado", argCont, argPuroStr);
         fprintf(ptrTeclado, "%s\n", argPuroStr);
         fflush(ptrTeclado);
      }
      if ((*ctl)->geraLog) toFile("detalhes.log", ErrorText);
   }// fim for argCont
   if (tamFormato > (*ctl)->numeroArgumentos)
      fclose(ptrTeclado);
   printf("\nArgumento pela linha de comando: %s\n", linhaArgumento);
   sprintf(Comando, "vali_exec 1 run %d exe",(*ctl)->nProcess);
   if((*ctl)->numeroArgumentos > 0)
   sprintf(Comando, "vali_exec 1 run %d exe \"%s\"",(*ctl)->nProcess, linhaArgumento);

   if( (*ctl)->numeroArgumentos < (int) strlen( (*ctl)->formatoIndividuo ) )
   strcat(Comando, " < entrada.kyb");

   char * saida = NULL;
   alocaCharPtr( &saida, (int) ( strlen((*ctl)->diretorio) + 20 ), "evaluateIndividual" , "saida" );
   sprintf(saida, " > %soutput.out", (*ctl)->diretorio );
   strcat(Comando, saida);
   //executa o programa com os valores ajustados.
   (*ctl)->setComandPath(Comando);
   system((*ctl)->comandPath);
   /*****************************************************************************************Nao sei pra que é essa linha...*******/
      //redireciona a saida.
   //sprintf(Comando, "mv %spath.tes %spath1.tes", (*ctl)->diretorio, (*ctl)->diretorio);
   (*ctl)->setComandPath( Comando );

   system( (*ctl)->comandPath );
   //avalia o caso de teste recem executado.
   sprintf(Comando, "vali_eval %s %d %s > %svali_eval.out", (*ctl)->criterioTesteValiMPI, (*ctl)->nProcess, (*ctl)->funcoes,(*ctl)->diretorio);
   (*ctl)->setComandPath( Comando );

   system( (*ctl)->comandPath );
   
   desalocaCharPtr( &linhaArgumento,  (int) ( tamLinhaArgumento ), "evaluateIndividual", "linhaArgumento" );
   desalocaCharPtr (&argPuroStr, (int) ( (*ctl)->tamanhoMaximoArgumento ), "evaluateIndividual", "argPuroStr" );
   desalocaCharPtr( &saida, (int) ( strlen((*ctl)->diretorio) + 20 ), "evaluateIndividual" , "saida" );
   desalocaCharPtr( &argMascarado,  (int) ( (*ctl)->tamanhoMaximoArgumento ), "evaluateIndividual", "argMascarado" );
   delete (indiv);

   return true;
}


/** Método usado para obter linha de cobertura que contém o desempenho do individuo
perante aos elementos requeridos. */
int ferramenta::obtemCoberturaValiMPI(char ** linhaCobertura, int tamLinhaCobertura){
   int elem_coberto;
   char *frase = NULL;
   int tamExeResultado = (int) (strlen((*ctl)->diretorio) + strlen((*ctl)->criterioTesteValiMPI) + 15);
   char * arquivoExeResultado = NULL, * linhaCoberturaLocal = NULL;
   alocaCharPtr( &arquivoExeResultado,(int) tamExeResultado, "obtemCoberturaValiMPI", "arquivoExeResultado");
   alocaCharPtr( &linhaCoberturaLocal,(int) ((*ctl)->quantidadeElemento) + 5, "obtemCoberturaValiMPI", "linhaCoberturaLocal");
   //sprintf(arquivoExeResultado, "%s%sdif1-0.tes", (*ctl)->diretorio, (*ctl)->criterioTesteValiMPI);
   sprintf(arquivoExeResultado, "%svali_eval.out", (*ctl)->diretorio);
   FILE * ptrExeResultado = fopen( arquivoExeResultado, "r");

   if (ptrExeResultado == NULL) {
      sprintf(ErrorText,"nao abriu o arquivo de resultado corretamente : %s", arquivoExeResultado);
      erro(ErrorText,1);
   }
   rewind(ptrExeResultado);
   memset( linhaCoberturaLocal, '-', (int) (*ctl)->quantidadeElemento );
   linhaCoberturaLocal[ (int) (*ctl)->quantidadeElemento ] = '\0';
   char * elCoberto = NULL;
   alocaCharPtr( & elCoberto, 128, "obtemCoberturaValiMPI", "elCoberto");
   alocaCharPtr( & frase, 128, "obtemCoberturaValiMPI", "frase");
   for ( ; (!feof(ptrExeResultado)); )
   {
      //block contera o numero do elemento requerido satisfeito
      memset(elCoberto, '\0', 128);
      fgets( elCoberto, 127, ptrExeResultado);
      trim( & elCoberto);
      memcpy(frase,elCoberto + 3,22);
      frase[22] = '\0';
      if (strcmp(frase,"ELEMENTOS REQUERIDOS N") == 0) break;
      //sscanf(elCoberto,"%d",&elem_coberto);
      if( sscanf(elCoberto,"%d",&elem_coberto) > 0){
         linhaCoberturaLocal[ elem_coberto - 1 ] = 'X';
      } // fim if block ""
   } // fim for !feof(ptrExeResultado)
   fclose(ptrExeResultado);
   //Copia o resultado para a linha de cobertura externa apenas se a cobertura gerada for != "" e tiver tamanho coerente
   //com a quantidade de elementos requeridos.
   if ( ( strcmp(linhaCoberturaLocal, "") != 0) && ( strlen(linhaCoberturaLocal) == (*ctl)->quantidadeElemento ) )
      strcpy( *linhaCobertura, linhaCoberturaLocal);
   //printf("clocal - %s\n",linhaCoberturaLocal);
   desalocaCharPtr( &arquivoExeResultado,(int) tamExeResultado, "obtemCoberturaValiMPI", "arquivoExeResultado");
   desalocaCharPtr( &linhaCoberturaLocal,(int) ((*ctl)->quantidadeElemento) + 5, "obtemCoberturaValiMPI", "linhaCoberturaLocal");
   desalocaCharPtr( & elCoberto, 50, "obtemCoberturaValiMPI", "elCoberto");
   return true;
}
/** Executa a proteum para um determinado caso de teste da população. */
int ferramenta::evaluateIndividualProteum( int nro ){
   //DESABILITANDO TODOS OS CASOS DE TESTE
   (*ctl)->setComandPath("tcase -i testSection");
   system( (*ctl)->comandPath );

   //HABILITANDO CASO DE TESTE ESPECIFICO
   sprintf(Comando, "tcase -e -f %d -t %d testSection", nro, nro);
   (*ctl)->setComandPath(Comando);
   system( (*ctl)->comandPath );

   //EXECUTANDO OS MUTANTES PARA OS CASOS DE TESTE HABILITADOS
   (*ctl)->setComandPath("exemuta -exec testSection");
   system( (*ctl)->comandPath );

   //DIRECIONANDO OS MUNTANTES MORTOS PARA MORTO.TXT
   (*ctl)->setComandPath("muta -l testSection | mortos > mortos.txt");
   system( (*ctl)->comandPath );

   return true;
}
/** Método utilizado para obter a cobertura de um determinado caso de teste.
 */
int ferramenta::obtemCoberturaProteum(char ** linhaCobertura, int tamLinhaCobertura){
   char * linhaCoberturaLocal = NULL;
   alocaCharPtr( &linhaCoberturaLocal,(int) ((*ctl)->quantidadeElemento) + 5, "obtemCoberturaValiMPI", "linhaCoberturaLocal");
   memset( linhaCoberturaLocal, '-', (int) (*ctl)->quantidadeElemento );
   FILE * mortosF = fopen("mortos.txt", "r");
   if (mortosF == NULL)
      erro("nao abriu o arquivo corretamente : mortos.txt",1);

   int tamBloco = 200;
   char * block = NULL;
   alocaCharPtr( &block, tamBloco, "obtemCoberturaProteum", "block");
   while( ! feof(mortosF) ) {
      memset( block, '\0', tamBloco );
      fgets ( block, tamBloco, mortosF );
      trim  ( & block );
      *(linhaCoberturaLocal + atoi(block)) = 'X';
    } // fim while

   fclose(mortosF);
   strcpy( *linhaCobertura, linhaCoberturaLocal);
   desalocaCharPtr( &linhaCoberturaLocal,(int) ((*ctl)->quantidadeElemento) + 5, "obtemCoberturaValiMPI", "linhaCoberturaLocal");
   desalocaCharPtr( &block, tamBloco, "obtemCoberturaProteum", "block");

   return true;

}
