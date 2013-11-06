package algoritmoGenetico;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Formatter;

import main.Diversos;
import ferramenta.Central;
import ferramenta.Ferramenta;

/***************************************************************************
 populacao.cpp  -  description
 -------------------
 begin                : Dom Jul 6 2003
 copyright            : (C) 2003 by Luciano Petinati Ferreira
 email                : petinat@inf.ufpr.br
 ***************************************************************************/

/***************************************************************************
 * * This program is free software; you can redistribute it and/or modify * it
 * under the terms of the GNU General Public License as published by * the Free
 * Software Foundation; either version 2 of the License, or * (at your option)
 * any later version. * *
 ***************************************************************************/

public class Populacao {
	
	/** objeto da classe central */
	Central objCentral;
	Individuo objIndividuo;
	Diversos objDiversos;
	Ferramenta objFerramenta;

	
	public Populacao() {
		System.out.println("\nConstruindo populacao...");
		objCentral = new Central();
		objIndividuo = new Individuo();
		objDiversos = new Diversos();
		objFerramenta = new Ferramenta();
	}
 
	
	/** Metodo usado para gerar populacao inicial para o AG. Cria a populacao
	 * inicial aleatoria, com base nas configuracoes fornecidas ou Cria a
	 * populacao inicial baseado em um arquivo fornecido.
	 * @throws IOException */
	public void geraPopulacaoInicial() throws IOException {
			
		int retorno = 0;
				// objDiversos.toFile("log_erro.log", "---geraPopulacaoInicial");
		if (objCentral.arquivoPopulacao == null) {
			geraPopulacaoInicialAleatoria();
		} else {
			geraPopulacaoInicialArquivo();
		}
		}

	/** Cria a populacao inicial aleatoria, com base nas configuracoees fornecidas */
	public void geraPopulacaoInicialAleatoria() {
		System.out.println("\nGerando pop.inic.aleatoria");
				
		for (int contador = 0; contador < objCentral.tamanhoPopulacao;) {
			objIndividuo.novo();		
		} // fim for
	}


	/** Cria a populacao inicial baseado em arquivo fornecido. 
	 * @throws IOException */
	public void geraPopulacaoInicialArquivo() throws IOException {
		//ler o arquivo da populacao inical ler linha por linha e passar cada conteudo da linha para o 
		//novo da classe individuo
		System.out.printf("\nGerando pop.inic.arquivo %s", objCentral.arquivoPopulacaoInicial);
		
		FileReader arq = new FileReader(objCentral.arquivoPopulacaoInicial);
		BufferedReader lerArq = new BufferedReader(arq);
	
		String linha = null;
		int contador = 0;
		linha = lerArq.readLine();		
		for (contador = 0; linha != null;) {		
			linha = linha.trim();
			
				if (linha !=("")) {
				objIndividuo.novo(linha);
				if (toPopulacao(contador, objIndividuo.representacao, objCentral.arquivoPopulacao) == true){
					contador++;
				}
			}
		} // fim for
		objCentral.setTamanhoPopulacao(contador);
		objCentral.recalculaPorcEvolucao();	
	}
	 

	/**Metodo usado para incluir um novo individuo no arquivo de populacao. Caso
	 * o individuo ja exista na populacao a insercao nao sera realizada. 
	 * @throws IOException */
	boolean toPopulacao(int nro, String strIndividuo, File arquivo) throws IOException {
		
		String saida = ""; 
		
		if ((strIndividuo.equals("")) || (strIndividuo.equals(216)))
			System.out
					.println(" to erro, tentando salvar individuo vazio ou 216,216");
		
		if (nro != 0) {
			if (inPopulacao(strIndividuo, arquivo) == true) {
				return false;
			}
		}		
		
		
		saida += saida.format("%5d : %s\n", nro , strIndividuo);
		objDiversos.escreverArquivo(arquivo, saida);
		
		
		return true;
	}

	/** Metodo usado para verificar se um individuo esta na populacao
	 * representada pelo arquivo passado por argumento. 
	 * @throws IOException */	
	public boolean inPopulacao(String strIndividuo, File arquivo) throws IOException{	  
		String linhaArquivo = null;
		String pegaQuebra = null;
		String [] quebraLinhaArq = null;
		
		FileReader fr = new FileReader(arquivo);
		BufferedReader br = new BufferedReader(fr);
		
		linhaArquivo = br.readLine();		
		
		while (linhaArquivo != null){
			quebraLinhaArq = linhaArquivo.split(":");
			pegaQuebra = quebraLinhaArq[1].trim();
						
			if(pegaQuebra.equals(strIndividuo)){
			return true;				
			}
			
			linhaArquivo = br.readLine();
		}
		return false;		
	}

	/** Metodo usado para avaliar a populacao do AG. Cada individuo eh executado e
	 * o fitness o calculado com base no numero de elementos requeridos
	 * satisfeitos pela execucao do mesmo.
	 * @throws IOException */
	public void avaliaPopulacao() throws IOException {
		
		 if(objCentral.geraLog != 0){
			 objDiversos.toFile("log_erro.log", "---avaliaPopulacao");
		 }
		 
		geraCoberturaIndividuo();
		objDiversos.toFile("log_alocacoes.tst", "0, 0, 0, PProva");
		objDiversos.toFile("log_alocacoes.tst", "1, 0, 0, PProva");
		geraBonusIneditismo();
		geraIneditismoPopulacao();

//		objCentral.geraLinhaPerda();
//		System.out.println("\n Linha de perda:\n" << objCentral.linhaPerda());

		geraFitness();
		if (objCentral.geraLog != 0){		
		objDiversos.toFile("log_erro.log", "---saindo avaliaPopulacao");
		}
	}// fim avaliaPopulacao()

	 
	/** Metodo usado para gerar a cobertura dos individuos da populacao. 
	 * @throws IOException */
	public void geraCoberturaIndividuo() throws IOException {

		if (objCentral.geraLog != 0 ){
					objDiversos.toFile("log_erro.log", "------geraCoberturaIndividuo");
		}
		
			System.out.printf("\nGerando cobertura para ValiMPI...");
			geraCoberturaIndividuoValiMPI();
		// Tanto geraCoberturaValiMPI como geraCoberturaProteum geram
		// objCentral.coberturaCriterio
			
		objCentral.setCoberturaAtual(objDiversos.numberOf(objCentral.linhaCoberturaAtual,
				'X') * 100 / objCentral.quantidadeElemento);

		System.out.println("\nCobertura Gerada...");
		System.out.println("coberturaGlobal - " + objCentral.coberturaGlobal
				+ "\nlinhaCobertura - " + objCentral.linhaCoberturaAtual);
		sobrepoe((objCentral.coberturaGlobal), objCentral.linhaCoberturaAtual);

		geraCoberturaElementos();

		if (objCentral.geraLog != 0) {
			objDiversos.toFile("log_erro.log", "------saindo geraCoberturaIndividuo");
		}
		
	}
 

	/**	 * Metodo usado para gerar a cobertura dos individuos da populacao com base
	 * em arquivos gerados pela utilizacao da ferramenta ValiMPI. 
	 * Para cada individuo da populacao, deve obter a cobertura. verifica se ja
	 * esta no repositorio, se estiver, recupera a cobertura/desempenho do
	 * repositorio. se nao estiver executa o programa instrumentado para cada
	 * individuo. obtem a cobertura alcancada. Documenta a cobertura no arquivo
	 * verifica se deve ser incluido na lista tabu. se tiver, substitui todos os
	 * individuos com cobertura coberta por esse individuo e insere na lista
	 * tabu senao nao faz nada.
	 */
	public void geraCoberturaIndividuoValiMPI(){
  
  // tabu * listaTabu = NULL; //verificar depois a lista tabu
		
   if ( objCentral.ativaTabu. )
      listaTabu = new tabu( & (*ctl) );

   String linhaCobertura = null;
   String linhaCoberturaCriterio = null;

   //linhaCoberturaCriterio[ (int) objCentral.quantidadeElemento ] = '\0';
   System.out.println( "\nAvaliando os Individuos:\n") ;
   //printf( "\nAvaliando os Individuos:\n" );
   sprintf(Comando, "rm %s -rf", objCentral.arquivoCoberturaIndividuo);
   objCentral.setComandPath(Comando);
   system( objCentral.comandPath );

   for (int contador = 0; contador < objCentral.tamanhoPopulacao; contador ++){
      //recupera individuo da populacao e inicializa a linha de cobertura.
      objIndividuo.representacaoload(contador); //ou contador+1);
    
      //linhaCobertura [(int) objCentral.quantidadeElemento] = '\0';
      //System.out.println( "\nIndiv�duo " << contador << "- ";

      //verifica necessidade de execucao
      if ( (objCentral.geracaoAtual == 0) || (objCentral.geracaoAtual >= objCentral.geracoesComRepositorio ) || (! objCentral.inRepositorio(objIndividuo.representacaorepresentacao, & linhaCobertura) ) )
      //if (true)
      {
         //deve executar o programa.
        objFerramenta.evaluateIndividual( contador );
        objFerramenta.obtemCoberturaValiMPI( linhaCobertura, (int) ( objCentral.quantidadeElemento + 20 ) );

         toRepositorio( contador, linhaCobertura );
      }  // fim if
      else{
         System.out.println( "R";
      }

      //atualiza a cobertura do criterio / sobrepoe.
      sobrepoe(&linhaCoberturaCriterio, linhaCobertura);

      if ( ! appendobjDiversos.toFile( objCentral.arquivoCoberturaIndividuo, contador, linhaCobertura ) ){
        sprintf(ErrorText, "nao gravou no arquivo : %s", objCentral.arquivoCoberturaIndividuo);
        objDiversos.erro(ErrorText,1);
        }

      //atualiza lista tabu se necessario
      if ( objCentral.ativaTabu ) {
        listaTabu->manutencaoTabu( linhaCobertura, contador);
        }
      //tabu->atualiza(indiv.representacao, linhaCobertura);
   }   // fim for contador

   objCentral.atualizaLinhaCoberturas(linhaCoberturaCriterio);
   //objCentral.setCoberturaAtual( 0);

   }  // fim geraCoberturaIndividuoValiMPI()

	 

	/**
	 * Metodo usado para armazenar desempenho de um individuo, assim não precisa
	 * executa-lo novamente para obter sua cobertura.	 
	 * @throws IOException */
	public void toRepositorio(int nro, String desempenho) throws IOException {
		String saida = "";
		
		if (nro >= objCentral.tamanhoPopulacao)
			objDiversos.erro("extrapolou tamanho da populacao", 1);

		objIndividuo.load(nro);
						
		saida += saida.format("%s : %s", objIndividuo.representacao, desempenho);
		objDiversos.escreverArquivo(objCentral.arquivoRepositorio, saida);
				
	}

	/** Metodo usado para sobrepor duas linhas de coberturas.	 */	
	public void sobrepoe(String cobertura, String desempenho) {
		int i = 0;
		String coberturaLocal = null;
		String mostrar = null;
		// alocaCharPtr(& coberturaLocal, ((int)objCentral.quantidadeElemento +
		// 2), "sobrepoe", "coberturaLocal");
		coberturaLocal = cobertura;
		// System.out.println( "\nCobertura: "<< coberturaLocal
		// <<"\nDesempenho: "<< desempenho;
		if (coberturaLocal.equals(null))
			coberturaLocal = desempenho;
		else {
			int tam = cobertura.length();

			for (i = 0; i < tam; i++)
				if (coberturaLocal.charAt(i) == '-') {
					mostrar = coberturaLocal.replace(coberturaLocal.charAt(i),
							desempenho.charAt(i));
				}
		}
		// fim else
		coberturaLocal = mostrar;
		cobertura = coberturaLocal;
		
		}// fim sobrepoe

	/** Metodo que evolui a populacao de individuos. */
	public void evoluiPopulacao() {
		
		if (objCentral.quantidadeFitness > 0)
			evolucaoPorFitness();

		if (objCentral.quantidadeElitismo > 0)
			evolucaoPorElitismo();

		if (objCentral.quantidadeIneditismo > 0)
			evolucaoPorIneditismo();

		/*
		 * Para recuperar individuos que foram perdidos da geracao passada e nao
		 * poderiam ser pois era um individuo que cobria um elemento nao coberto
		 * na nova populacao, deve-se manter uma copia da populacao anterior.
		 * Essa esta sendo guardada em ctl->arquivoPopulacaoTemporario...
		 */
		sprintf(Comando, "cp %s %s", objCentral.arquivoPopulacao,
				"popManejo.pop");
		objCentral.setComandPath(Comando);
		system(objCentral.comandPath);
		sprintf(Comando, "mv %s %s", objCentral.arquivoPopulacaoTemporario,
				objCentral.arquivoPopulacao);
		objCentral.setComandPath(Comando);
		system(objCentral.comandPath);
		sprintf(Comando, "mv %s %s", "popManejo.pop",
				objCentral.arquivoPopulacaoTemporario);
		objCentral.setComandPath(Comando);
		system(objCentral.comandPath);

		// rastro("saiu -  evolui");

		if (objCentral.geraLog != 0)
			objDiversos.toFile("log_erro.log", "---saindo EvoluiPopulacao");

	}

	/**Metodo usado para evoluir a populacao com base no fitness dos individuos.*/
	public void  evolucaoPorFitness(){
		if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------evolucaoFitness");
  		int cross = 0, mut = 0;
  		double sorteio = 0;
  		int contador = 0;

   //Apagar o arquivo evolucaio.fil caso seja a primeira evolucao da populacao, retirando assim,
  //informaces de execucoes anteriores.
  		if (objCentral.geracaoAtual == 0) system("rm evolucao.fil");
  /*pprova*/
  objDiversos.toFile("evolucao.fil", "");
  objDiversos.toFile("evolucao.fil", "##############################################################");
  sprintf(ErrorText, "Evolucao Geracao :%d", (int) objCentral.geracaoAtual);
  objDiversos.toFile("evolucao.fil", ErrorText);
  objDiversos.toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR FITNESS (%0.0f) / somatoriaFitness = %0.0f", objCentral.quantidadeFitness, objCentral.somatoriaFitness);
  objDiversos.toFile("evolucao.fil", ErrorText);
  /**/

  //contador possui a quantidade de individuos gerados e aceitos na proxima geracao.
  //Iteracao para gerar novo individuo enquanto contador for menr que a quantidade configurada.
  for(contador=0; contador < objCentral.quantidadeFitness; )
    {
      sorteio =  objCentral.geraSorteio( objCentral.somatoriaFitness );

      objIndividuo.load( (int) indiceIndividuoSorteado( sorteio ) );
      /*prova* /
      sprintf(ErrorText, "\n1 Sorteio : %f : <%s>", sorteio, indiv1.representacao);
      printf(ErrorText);
      /**/

      /*prova*/
      objDiversos.toFile("evolucao.fil", "--------------------------------------------------------------");
      sprintf(ErrorText, "1 Sorteio : %f : <%s>", sorteio, objIndividuo.representacao);
      objDiversos.toFile("evolucao.fil", ErrorText);
      /**/

      sorteio = objCentral.geraSorteio( objCentral.somatoriaFitness );
      objIndividuo.load( (int) indiceIndividuoSorteado ( sorteio ) );
      /*prova* /
      sprintf(ErrorText, "\n2 Sorteio : %f : <%s>", sorteio, indiv2.representacao);
      printf(ErrorText);
      /**/

      /*prova*/
      sprintf(ErrorText, "2 Sorteio : %f : <%s>", sorteio, objIndividuo.representacao);
      objDiversos.toFile("evolucao.fil", ErrorText);
      /**/

      cross = genrand() % 100;
      if(cross <= objCentral.taxaCrossover * 100){
        crossover( &(objIndividuo.representacao), &(objIndividuo.representacao) );
        /*prova*/
        sprintf(ErrorText, "    op CROSSOVER : %s / %s", objIndividuo.representacao, objIndividuo.representacao);
        objDiversos.toFile("evolucao.fil", ErrorText);
        /**/
        }
      mut   = genrand() % 100;
      if(mut <= objCentral.taxaMutacao * 100){
        mutacao(objIndividuo.representacao);
        /*prova*/
        sprintf(ErrorText, "    op MUTACAO 1  : %s", objIndividuo.representacao);
        objDiversos.toFile("evolucao.fil", ErrorText);
        /**/
        }
      if( toPopulacao( contador, objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
        contador ++;
        /*prova*/
        sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
        objDiversos.toFile("evolucao.fil", ErrorText);
        /**/
        }
      if(contador < objCentral.quantidadeFitness ){
        mut   = genrand() % 100;
        if(mut <= objCentral.taxaMutacao * 100){
          mutacao(objIndividuo.representacao);
          /*prova*/
          sprintf(ErrorText, "    op MUTACAO 2  : %s", objIndividuo.representacao);
          objDiversos.toFile("evolucao.fil", ErrorText);
          /**/
          }
        if( toPopulacao( contador, objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
          contador ++;
          /*prova*/
          sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
          objDiversos.toFile("evolucao.fil", ErrorText);
          /**/
          }
        }// fim if
    } // fim for fitness
  
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo evolucaoFitness");
  
}

	/** Metodo retorna o indice do individuo sorteado. Com base na somatoria do
	 * fitness e na ordem dos individuos, simulando o metodo de selecao da
	 * roleta. Retorna qual o individuo possui esta na faixa sorteada.*/
	public void indiceIndividuoSorteado(double sorteio){
		double superior = 0;
		int tamLinha = nroEspacos( (int) objCentral.tamanhoPopulacao ) + 30;
		String linha = null;
		File ptrFitness;
		ptrFitness = fopen( objCentral.arquivoFitness, "r" );
		
		if(ptrFitness == NULL){
      sprintf(ErrorText,"nao abriu o arquivo de Variacao de fitness : %s", objCentral.arquivoVariacaoFitness);
      objDiversos.erro(ErrorText,1);
    }

  for (int i=0; ( i < objCentral.tamanhoPopulacao) ; i++)
    {
      memset( linha, '\0', tamLinha );
      fgets(linha, tamLinha, ptrFitness);
      strcpy(linha, linha + objDiversos.indexOf(linha,':') + 1);
      objDiversos.trim(&linha);
      superior += atof(linha);
      if(sorteio <= superior){
        fclose(ptrFitness);
        desalocaCharPtr( &linha , tamLinha, " indiceIndividuoSorteado", "linha" );
        return i;
      } // fim if
    }// fim for
  fclose(ptrFitness);
  desalocaCharPtr( &linha , tamLinha, " indiceIndividuoSorteado", "linha" );
  return -1;
}

	/** Metodo usado para aplicar mutacao em um individuo. */
	int mutacao(String indiv) {
		int i = 0, mudou = 0, posMut = rand() % strlen(indiv);
		for (; mudou == 0;) {
			switch (indiv[posMut]) {
			case '+':
				indiv[posMut] = '-';
				mudou = 1;
				break;
			case '-':
				indiv[posMut] = '+';
				mudou = 1;
				break;
			// case '#': posMut = rand() % strlen( indiv ); break; //escolhe
			// outra posicao
			case ((char) 216):
				posMut = rand() % strlen(indiv);
				break; // escolhe outra posicao
			default: {
				int pos = 0;
				mudou = 1;
				for (i = 1; posMut >= objCentral.inicioTipo(i); i++)
					;
				if ((objCentral.formatoIndividuo[i - 1] == 'C')
						|| (objCentral.formatoIndividuo[i - 1] == 'S')) {
					indiv[posMut] = generateChar(objCentral.tipoString);
				} // fim if
				else {
					indiv[posMut] = generateChar("n");
				} // fim else
			}// fim default
			}// fim switch
		}// fim for
		return true;
	}

	/**
	 * Metodo que aplica operador crossover nos individuos representados por
	 * indiv1 e indiv2
	 */
public void	int crossover( String  indiv1, char  indiv2 ){
  int i=0, ocorre=0, posCross=0, tamTipo=0, inicTipo=0, tamFormat = 0;
  char * block = NULL, * indivAux = NULL;

  alocaCharPtr( &block , (int) (objCentral.tamanhoIndividuo + 5), " crossover", "block" );
  alocaCharPtr( &indivAux , (int) (objCentral.tamanhoIndividuo + 5), " crossover", "indivAux" );

  strcpy( indivAux, * indiv1);

  tamFormat = strlen( objCentral.formatoIndividuo );
  for(i=0; i<tamFormat; i++)
    {
      ocorre = rand() % 2;
      if(ocorre){    // ocorre crossover no tipo chance de 50%
        inicTipo = objCentral.inicioTipo(i);
        tamTipo =  objCentral.tamanhoTipo(i);
        posCross = (rand() % tamTipo);
        switch( objCentral.formatoIndividuo[i] )
          {
          case 'S':
            {
              memset( block, '\0', (int) (objCentral.tamanhoIndividuo + 5) );
              int maxTam=0, maxTam2=0;
              strncpy( block, * indiv1 + inicTipo, tamTipo );
              //maxTam = objDiversos.indexOf(block, '#');
              maxTam = objDiversos.indexOf(block, (char) 216);
              if(maxTam == -1)
                maxTam = tamTipo;
              memset( block, '\0', (int) (objCentral.tamanhoIndividuo + 5) );
              strncpy( block, * indiv2 + inicTipo, tamTipo );
              //maxTam2 = objDiversos.indexOf(block, '#');
              maxTam2 = objDiversos.indexOf(block, (char) 216);
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
  //  rastro("saiu -  crossover");
 
 
}

	/** Metodo usado para gerar o fitness da populacao */
	int geraFitness(){
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------geraFitness");

  char * linhaCobertura = NULL, * desempenho = NULL;
  double fitness = 0, somatoriaFitness = 0, cobertura=0;
  alocaCharPtr( &linhaCobertura , (int) (objCentral.quantidadeElemento + 20), " geraFitness", "linhaCobertura" );
  alocaCharPtr( &desempenho , (int) (objCentral.quantidadeElemento + 20), " geraFitness", "desempenho" );

  File ptrFitness, * ptrCobertura;
  ptrFitness = fopen(objCentral.arquivoFitness, "w");

  ptrCobertura = fopen(objCentral.arquivoCoberturaIndividuo, "r");
  if(ptrCobertura == NULL)
    {
      sprintf( ErrorText,"nao abriu o arquivo de cobertura/individuo : %s", objCentral.arquivoCoberturaIndividuo );
      objDiversos.erro( ErrorText, 1 );
    }

  for (int i=0; i < objCentral.tamanhoPopulacao; i++){
      memset(desempenho  , '\0', (int) ( objCentral.quantidadeElemento + 20 ) );
      fgets(desempenho, (int) ( objCentral.quantidadeElemento + 20 ), ptrCobertura);

      memcpy(desempenho, desempenho + objDiversos.indexOf(desempenho,':') + 1, strlen(desempenho) - objDiversos.indexOf(desempenho,':'
));
      objDiversos.trim(& desempenho);
      sobrepoe(& linhaCobertura, desempenho);

      fitness = (double)numberOf(desempenho, 'X') * 100 / (double) (objCentral.quantidadeElemento);

      fprintf(ptrFitness,"%5d : %10.2f\n", i, fitness);
      fflush(ptrFitness);
      somatoriaFitness +=fitness;
    }// fim for
  //rastro("PONTO1.7");*/
  fclose(ptrFitness);
  fclose(ptrCobertura);
  objCentral.setSomatoriaFitness( somatoriaFitness );

  toFile ( objCentral.arquivoObsCobertura, linhaCobertura);

  desalocaCharPtr( &linhaCobertura , (int) (objCentral.quantidadeElemento + 20), " geraFitness", "linhaCobertura" );
  desalocaCharPtr( &desempenho , (int) (objCentral.quantidadeElemento + 20), " geraFitness", "desempenho" );

  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo geraFitness");

  return true;
}

	/** Metodo usado para realizar evolucao por elitismo. */
	int evolucaoPorElitismo(){
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------evolucaoIneditismo");

  int contador = 0;
  double posicao = 0;

  individuo * indiv1 = new individuo( &(*ctl) );

  /*prova*/
  //objDiversos.toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR INEDITISMO (%0.0f)", objCentral.quantidadeIneditismo);
  //objDiversos.toFile("evolucao.fil", ErrorText);
  /**/
  for(contador = (int)( objCentral.quantidadeFitness /*+ objCentral.quantidadeElitismo*/ ); contador < (int) ( objCentral.quantidadeFitness + objCentral.quantidadeElitismo  ); )
    {
      posicao = melhorFitAntNaoEm( objCentral.arquivoPopulacaoTemporario );
      if (posicao != -1){
        objIndividuo.load( (int) posicao );
        /*prova*/
        sprintf(ErrorText, " Ineditismo do indiv pos %0.0f : %s", posicao, objIndividuo.representacao);
        //objDiversos.toFile("evolucao.fil", ErrorText);
        /**/
      }
      else{
        objIndividuo.novo();
        /*prova*/
	  sprintf(ErrorText, " Ineditismo do novo indiv : %s", objIndividuo.representacao);
	  //objDiversos.toFile("evolucao.fil", ErrorText);
	  /**/
	}
      if ( toPopulacao( contador , objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) )
	{
	  contador ++;
	  /*prova*/
	  sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
	  //objDiversos.toFile("evolucao.fil", ErrorText);
	  /**/
	}
    } // fim for ineditismo
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo evolucaoIneditismo");
  delete ( indiv1 );
  return true;

}

	/** Metodo usado para obter o indice do individuo a ser mantido */
	public double melhorInedAntNaoEm ( String arquivoAuxiliar ){
  File ptrIneditismo;
  individuo * indiv = new individuo( &(* ctl) );

  ptrIneditismo = fopen( objCentral.arquivoIneditismo, "r" );
  if(ptrIneditismo == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de Ineditismo corretamente : %s", objCentral.arquivoIneditismo);
    objDiversos.erro(ErrorText, 1);
  }
  int pos2p = 0;

  double posMelhor = -1, pos = 0, ineditismo = 0, ineditismoMelhor = -1;

  char * linha = NULL;
  int tamLinha = 100;
  alocaCharPtr( &linha , tamLinha, " melhorInedAntNaoEm", "linha" );
  //while(! feof(ptrIneditismo) )
  for( int cont = 0; cont < objCentral.tamanhoPopulacao; cont ++ ){
    memset(linha, '\0', 100);
    fgets(linha,  100, ptrIneditismo);
    pos2p = objDiversos.indexOf(linha, ':');
    if(pos2p != -1){
      strcpy( linha, linha + pos2p + 1);
      trim  ( & linha );
      ineditismo = atof( linha );
      objIndividuo.representacaoload( cont );
      if ( (ineditismo > ineditismoMelhor) && (!inPopulacao(objIndividuo.representacaorepresentacao, arquivoAuxiliar) ) ){
        posMelhor = cont;
        ineditismoMelhor = ineditismo;
      }
    } // fim if
  }// fim for
  fclose(ptrIneditismo);
  desalocaCharPtr( &linha , tamLinha, " melhorInedAntNaoEm", "linha" );
  delete ( indiv );
  return posMelhor;
}

	/** Metodo usado para obter o indice do individuo a ser mantido */
	public double melhorFitAntNaoEm( String arquivoAuxiliar ){
   File ptrFitness;
   individuo * indiv = new individuo( &(* ctl) );

   ptrFitness = fopen( objCentral.arquivoFitness, "r" );
   if(ptrFitness == NULL){
       sprintf(ErrorText, "nao abriu o arquivo de Fitness corretamente : %s", objCentral.arquivoFitness);
       objDiversos.erro(ErrorText, 1);
      }
   int pos2p = 0;
   double posMelhor = -1, pos = 0, fit = 0, fitMelhor = -1;

   char * linha = NULL;
   int tamLinha = 100;
   alocaCharPtr( &linha , tamLinha, " melhorFitAntNaoEm", "linha" );

   for( int cont = 0; cont < objCentral.tamanhoPopulacao; cont ++ ){
      memset(linha, '\0', tamLinha);
      fgets(linha,  tamLinha, ptrFitness);
      pos2p = objDiversos.indexOf(linha, ':');
      if(pos2p != -1){
         strcpy(linha, linha + pos2p + 1);
         objDiversos.trim( & linha);
         fit = atof( linha );
         objIndividuo.representacaoload( cont );
         if ( (fit > fitMelhor) && (!inPopulacao(objIndividuo.representacaorepresentacao, arquivoAuxiliar) ) ){
            posMelhor = cont;
            fitMelhor = fit;
            }
         } // fim if
      }// fim for
   fclose(ptrFitness);
   desalocaCharPtr( &linha , tamLinha, " melhorFitAntNaoEm", "linha" );
   return posMelhor;
}

	/** Metodo usado para calcular o ineditismo da populacao. */
	public void  geraBonusIneditismo(){

  if( (ctl)->geraLog) objDiversos.toFile("log_erro.log", "------geraIneditismo");
  char * elemCobertura = NULL;
  int contador=0, cont=0, lixo=0, ponto2=0, quantCob=0;
  double tamElCob = 0, bonificacao = 0;
  File ptrCobertura, * ptrBonusIneditismo;
  int pesoIneditismo = 2;
  tamElCob = objCentral.tamanhoPopulacao + 20;

  alocaCharPtr( &elemCobertura , (int)tamElCob, " geraIneditismo", "elemCobertura" );

  ptrBonusIneditismo = fopen( objCentral.arquivoBonusIneditismo,"w");
  ptrCobertura   = fopen( objCentral.arquivoCoberturaElemento ,"r");
  if ( ptrCobertura == NULL ){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura de Elementos corretamente : %s", objCentral.arquivoCoberturaElemento);
    objDiversos.erro(ErrorText,1);
  }
  System.out.printf("\n< geraIneditismo> Calculando ineditismo para os elementos\n");
  for (contador = 0; contador < objCentral.quantidadeElemento; contador++){
    System.out.printf("*");
    memset(elemCobertura, '\0', (int) tamElCob );
    fgets(elemCobertura, ( (int) tamElCob) -1, ptrCobertura);
    ponto2 = objDiversos.indexOf(elemCobertura,':');
    strcpy(elemCobertura, elemCobertura + ponto2 + 1);
    objDiversos.trim(&elemCobertura);
    
    if( strlen(elemCobertura) != objCentral.tamanhoPopulacao ){
      sprintf(ErrorText, "Erro no calculo da bonificacao p/Elemento %d\nTamanho da linha de cobertura do Elemento = %d, deveria ser %0.0f \n linha de cobertura : '%s'", contador, strlen(elemCobertura), objCentral.tamanhoPopulacao, elemCobertura);
      objDiversos.erro(ErrorText , 1);
    }

    bonificacao = 0;
    quantCob = numberOf(elemCobertura, 'X');
    if(quantCob)
      bonificacao = 100 * ( 1 - ( quantCob / objCentral.tamanhoPopulacao ) );
    fprintf(ptrBonusIneditismo,"%5d : %10.2f\n", contador, bonificacao);
    fflush(ptrBonusIneditismo);
  }// fim for

  fclose(ptrBonusIneditismo);
  fclose(ptrCobertura);

  desalocaCharPtr( &elemCobertura , tamElCob, " geraIneditismo", "elemCobertura" );

  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo geraIneditismo");
  
}

	/**
	 * Metodo usado para calcular a cobertura dos elementos, com base na
	 * cobertura dos individuos.
	 */
	int geraCoberturaElementos(){
//  Luciano Petinati Ferreira
//  data : 17/07/2002
//  hora : 22:00
//  Testado 1 vez
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "***------geraCoberturaElementos");
  char * linhaCobInd = NULL, * linhaCobElem = NULL;
  int contador=0, cont=0, lixo=0, ponto2=0;
  File ptrCobInd, * ptrCobElem;
  alocaCharPtr( &linhaCobInd , (int)(objCentral.quantidadeElemento + 20 ), " geraCoberturaElemento", "linhaCobInd" );
  alocaCharPtr( &linhaCobElem , (int)(objCentral.tamanhoPopulacao + 20 ), " geraCoberturaElemento", "linhaCobElem" );

  ptrCobElem = fopen(objCentral.arquivoCoberturaElemento  ,"w");
  ptrCobInd  = fopen(objCentral.arquivoCoberturaIndividuo ,"r");
  if (ptrCobInd == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura corretamente : %s", objCentral.arquivoCoberturaIndividuo);
    objDiversos.erro(ErrorText,1);
  }

  for (contador = 0; contador < objCentral.quantidadeElemento; contador++){
    rewind( ptrCobInd );
    memset(linhaCobElem , '\0', (int) (objCentral.tamanhoPopulacao + 20 ));

    for (cont = 0; cont < (int) (objCentral.tamanhoPopulacao); cont++){
      memset( linhaCobInd, '\0', (int) (objCentral.quantidadeElemento + 20 ) );
      fgets ( linhaCobInd, (int) (objCentral.quantidadeElemento + 20 ), ptrCobInd );
      ponto2 = objDiversos.indexOf(linhaCobInd,':');
      strcpy(linhaCobInd, linhaCobInd + ponto2 + 1);
      objDiversos.trim(&linhaCobInd);

      if( strlen(linhaCobInd) == objCentral.quantidadeElemento ){
        objDiversos.trim(& linhaCobInd);
        linhaCobElem[cont] = linhaCobInd[contador];
      }
    }// fim for
    /** /
    if (ctl->pausaGeracao)
    {
    System.out.printf("\n Vai gravar no arquivo ce cobertura do elemento:");
    pprova(linhaCobElem);
    }
/**/
    if( strlen(linhaCobElem) != objCentral.tamanhoPopulacao ){
      sprintf(ErrorText, " geraCoberturaElementos - Cobertura do elemento gerada errada para o elm %d - ", contador);
      objDiversos.erro(ErrorText, 1);
      }
    fprintf( ptrCobElem,"%5d : %s\n", contador, linhaCobElem );
    fflush( ptrCobElem );
  }// fim for

  fclose( ptrCobElem );
  fclose( ptrCobInd  );
  desalocaCharPtr( &linhaCobInd , (int)(objCentral.quantidadeElemento + 20 ), " geraCoberturaElemento", "linhaCobInd" );
  desalocaCharPtr( &linhaCobElem , (int)(objCentral.tamanhoPopulacao + 20 ), " geraCoberturaElemento", "linhaCobElem" );

  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "***------saindo geraCoberturaElementos");
  
}

	/**
	 * Metodo usado para evoluir populacao com base no indice de ineditismo do
	 * individuo.
	 */
	int evolucaoPorIneditismo(){
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------evolucaoIneditismo");

  int contador = 0;
  double posicao = 0;
  individuo * indiv1 = new individuo( & (*ctl) );
  /*prova*/
  //objDiversos.toFile("evolucao.fil", "==============================================================");
  sprintf(ErrorText, "EVOLUCAO POR INEDITISMO (%0.0f)", objCentral.quantidadeIneditismo);
  //objDiversos.toFile("evolucao.fil", ErrorText);
  /**/
  for(contador = (int)( objCentral.quantidadeFitness + objCentral.quantidadeElitismo ); contador < (int) ( objCentral.quantidadeFitness + objCentral.quantidadeElitismo + objCentral.quantidadeIneditismo ); ){
    posicao = melhorInedAntNaoEm( objCentral.arquivoPopulacaoTemporario );
    if (posicao != -1){
      objIndividuo.load( (int) posicao );
      /*prova*/
      sprintf(ErrorText, " Ineditismo do indiv pos %0.0f : %s", posicao, objIndividuo.representacao);
      //objDiversos.toFile("evolucao.fil", ErrorText);
      /**/
    }
    else{
      objIndividuo.novo();
      /*prova*/
      sprintf(ErrorText, " Ineditismo do novo indiv : %s", objIndividuo.representacao);
      //objDiversos.toFile("evolucao.fil", ErrorText);
      /**/
    }
    if ( toPopulacao( contador , objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
      contador ++;
      /*prova*/
      sprintf(ErrorText, " ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
      //objDiversos.toFile("evolucao.fil", ErrorText);
      /**/
    }
  } // fim for ineditismo
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo evolucaoIneditismo");
  delete(indiv1);
  return true;
}

	/**
	 * Metodo usado para gerar um arquivo que reflita os dados de uma populacao
	 * de forma entendivel/decodificada.
	 */
	public int decodificaPopulacao(File  origem, String  destino){
   //if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "---decodificaPopulacao");
   File ptrPopulacao,  ptrPopRes;
   String    block = "",  block_aux = "",  gene = "";
 

  int    tamFormato = objCentral.formatoIndividuo.length(),
		  inicBlock,
		  pos;
  int    geneTam = 0, tamBloco = 30;

  geneTam = (int) ( objCentral.tamanhoIndividuo + 20 );

  if(objCentral.tamanhoMaximoString > tamBloco)
    tamBloco = (int) objCentral.tamanhoMaximoString;

  ptrPopulacao = fopen(origem, "r");
  if (ptrPopulacao == NULL){
      sprintf(ErrorText,"nao abriu o arquivo de populacao corretamente : %s", origem);
      objDiversos.erro(ErrorText,1);
    }
  ptrPopRes = fopen(destino, "w");
  alocaCharPtr( &block , tamBloco, "decodificaPopulacao", "block");
  alocaCharPtr( &block_aux , tamBloco, "decodificaPopulacao", "block_aux");
  alocaCharPtr( &gene , geneTam, "decodificaPopulacao", "gene");

  for (int contador = 1; !feof(ptrPopulacao); contador++){
      memset(gene, '\0', geneTam);
      fgets(gene, geneTam, ptrPopulacao);
      objDiversos.trim(gene);
      if( strcmp(gene,"") != 0 ){
         strcpy(gene, gene + objDiversos.indexOf(gene, ':')+1);
         objDiversos.trim(gene);
         for (int i = 0; i < tamFormato ; i++){
            inicBlock = objCentral.inicioTipo(i);
            memset( block,     '\0', tamBloco );
            memset( block_aux, '\0', tamBloco );
            memcpy( block, gene+inicBlock, objCentral.tamanhoTipo(i) );
            switch( objCentral.formatoIndividuo[i] ){
               case 'I': sprintf(block_aux,"%d", objIndividuo.representacaodecode_block_int(block) ); break;
               case 'D': sprintf(block_aux,"%f", objIndividuo.representacaodecode_block_double(block) ); break;
               case 'F': sprintf(block_aux,"%f", objIndividuo.representacaodecode_block_float(block) ); break;
               case 'S':
               {
                  //pos = objDiversos.indexOf(block,'#');
                  pos = objDiversos.indexOf(block, (char) 216);
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
  
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "---decodificaPopulacao");
  return true;
}


	/**
	 * Este m�todo retorna o valor do bonus para os indiv�duos que cobriram o
	 * elemento informado por pos.
	 */
	double getBonusElemento(int pos){

   int i = 0;
   char * gene = NULL, * bonificacaoStr = NULL;
   File ptrBonusIneditismo = NULL;
   double bonificacao = 0;

   ptrBonusIneditismo = fopen( objCentral.arquivoBonusIneditismo, "r");
   if(ptrBonusIneditismo == NULL){
      sprintf( ErrorText," getBonusElemento - Nao abriu corretamente o arquivo  : %s", objCentral.arquivoCoberturaIndividuo );
      objDiversos.erro( ErrorText, 1 );
    }
    if(pos >= objCentral.quantidadeElemento){
      sprintf(ErrorText,"Pos, %d, extrapolou o indice do elemento buscado %f", pos, objCentral.quantidadeElemento);
      objDiversos.erro(ErrorText ,1);
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
         objDiversos.erro("Estouro de memoria ao tentar recuperar bonus do arquivo de populacao para var gene, metodo load",1);
      }

   }// fim for

   trim ( & gene);
   try{
      i = objDiversos.indexOf(gene, ':') + 1;
      strcpy(bonificacaoStr, gene + i );
      trim ( & bonificacaoStr);
      bonificacao = atof( bonificacaoStr);
   }
   catch(...){
      objDiversos.erro("Estouro de memoria ao tentar recuperar individuo da linha do arquivo de populacao , metodo load",1);
   }

   desalocaCharPtr( &gene, tamLinha, "getBonusElemento", "gene");
   desalocaCharPtr( &bonificacaoStr, tamLinha, "getBonusElemento", "bonificacaoStr");

   fclose(ptrBonusIneditismo);
   return bonificacao;

}

	/** Gera o arquivo com a bonificacao final por ineditismo. */
	int geraIneditismoPopulacao(){
//  Luciano Petinati Ferreira
//  data : 17/07/2002
//  hora : 22:00
//  Testado 1 vez
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "---------geraIneditismoPopulacao");
  char * linhaCobInd = NULL;
  int cont=0, ponto2=0;
  double ineditismo = 0;
  File ptrCobInd,  ptrIneditismo;

  alocaCharPtr( &linhaCobInd , (int)(objCentral.quantidadeElemento + 20 ), " geraIneditismoPopulacao", "linhaCobInd" );

  ptrIneditismo = fopen(objCentral.arquivoIneditismo  ,"w");
  ptrCobInd  = fopen(objCentral.arquivoCoberturaIndividuo ,"r");

  if (ptrCobInd == NULL){
    sprintf(ErrorText, "nao abriu o arquivo de cobertura corretamente : %s", objCentral.arquivoCoberturaIndividuo);
    objDiversos.erro(ErrorText,1);
  }
  for (cont = 0; cont < (int) (objCentral.tamanhoPopulacao); cont++){
     memset( linhaCobInd, '\0', (int) (objCentral.quantidadeElemento + 20 ) );
     fgets ( linhaCobInd, (int) (objCentral.quantidadeElemento + 20 ), ptrCobInd );
     ponto2 = objDiversos.indexOf(linhaCobInd,':');
     strcpy(linhaCobInd, linhaCobInd + ponto2 + 1);
     objDiversos.trim(&linhaCobInd);
     ineditismo = 0;

     if( strlen(linhaCobInd) != objCentral.quantidadeElemento ){
        sprintf(ErrorText, " geraIneditismoPopulacao - Cobertura do individuo gerada errada para o individuo %d - ", cont);
        objDiversos.erro(ErrorText, 1);
        }

     for (int i = 0; i < objCentral.quantidadeElemento; i++){
        if ( *( linhaCobInd +i) == 'X')
            ineditismo += getBonusElemento( i );
     }// fim for

     fprintf( ptrIneditismo, "%5d : %f\n", cont, ineditismo );
     fflush( ptrIneditismo );

     }// fim for
  fclose( ptrIneditismo );
  fclose( ptrCobInd  );

  desalocaCharPtr( &linhaCobInd , (int)(objCentral.quantidadeElemento + 20 ), " geraIneditismoPopulacao", "linhaCobInd" );
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "---------saindo geraIneditismoPopulacao");

  return true;
}
}
