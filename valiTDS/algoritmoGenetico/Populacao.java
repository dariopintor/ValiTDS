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
import main.Mersenne;
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
	Mersenne objMersenne;

	
	public Populacao() {
		System.out.println("\nConstruindo populacao...");
		objCentral = new Central();
		objIndividuo = new Individuo();
		objDiversos = new Diversos();
		objFerramenta = new Ferramenta();
		objMersenne = new Mersenne();
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
			if (inPopulacao(strIndividuo, arquivo)) {
				return false;
			}
		}		
		
		
		saida += String.format("%5d : %s\n", nro , strIndividuo);
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
			br.close();
			return true;				
			}
			
			linhaArquivo = br.readLine();
		}
		
		br.close();
		return false;		
	}

	/** Metodo usado para avaliar a populacao do AG. Cada individuo eh executado e
	 * o fitness o calculado com base no numero de elementos requeridos
	 * satisfeitos pela execucao do mesmo.
	 * @throws IOException 
	 * @throws InterruptedException */
	public void avaliaPopulacao() throws IOException, InterruptedException {
		
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
	 * @throws IOException 
	 * @throws InterruptedException */
	public void geraCoberturaIndividuo() throws IOException, InterruptedException {

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
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public void geraCoberturaIndividuoValiMPI() throws IOException, InterruptedException{
      
   String linhaCobertura = null;
   String linhaCoberturaCriterio = null;

    System.out.println( "\nAvaliando os Individuos:\n") ;   
    
    //sprintf(Comando, "rm %s -rf", (*ctl)->arquivoCoberturaIndividuo);
    objDiversos.limpaArquivo(objCentral.arquivoCoberturaIndividuo.getPath());
    
   for (int contador = 0; contador < objCentral.tamanhoPopulacao; contador ++){
      //recupera individuo da populacao e inicializa a linha de cobertura.
      objIndividuo.load(contador); //ou contador+1);
    
           //verifica necessidade de execucao
      if ( (objCentral.geracaoAtual == 0) ||
    		  (objCentral.geracaoAtual >= objCentral.geracoesComRepositorio )
    		  || (objCentral.inRepositorio(objIndividuo.representacao,  linhaCobertura) == linhaCobertura) ) {   //if (true)     {
         //deve executar o programa.
        objFerramenta.evaluateIndividual( contador );
        objFerramenta.obtemCoberturaValiMPI( linhaCobertura, (int) ( objCentral.quantidadeElemento + 20 ) );

         toRepositorio( contador, linhaCobertura );
      }  // fim if
      else{
         System.out.println( "R");
      }

      //atualiza a cobertura do criterio / sobrepoe.
      sobrepoe(linhaCoberturaCriterio, linhaCobertura);

//      if ( !objDiversos.toFile( objCentral.arquivoCoberturaIndividuo, contador, linhaCobertura ) ){
//       String saida = saida.format("nao gravou no arquivo : %s", objCentral.arquivoCoberturaIndividuo);
//        objDiversos.erro(saida,1);
//        }
     
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
						
		saida += String.format("%s : %s", objIndividuo.representacao, desempenho);
		objDiversos.escreverArquivo(objCentral.arquivoRepositorio, saida);
				
	}

	/** Metodo usado para sobrepor duas linhas de coberturas.	 */	
	public void sobrepoe(String cobertura, String desempenho) {
		int i = 0;
		String coberturaLocal = null;
		String mostrar = null;
		coberturaLocal = cobertura;
		
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

	/** Metodo que evolui a populacao de individuos. 
	 * @throws IOException */
	public void evoluiPopulacao() throws IOException {
		
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
		
		//copia de objCentral.arquivoPopulacao para "popManejo.pop"
		objDiversos.copyFile(objCentral.arquivoPopulacao.getPath(), "popManejo.pop");
		
		
		//move de "objCentral.arquivoPopulacaoTemporario" para "objCentral.arquivoPopulacao" 
		objDiversos.copyFile(objCentral.arquivoPopulacaoTemporario.getPath(),
				objCentral.arquivoPopulacao);
						
		// move de "popManejo.pop" para objCentral.arquivoPopulacaoTemporario
		objDiversos.copyFile("popManejo.pop",objCentral.arquivoPopulacaoTemporario);
		
		if (objCentral.geraLog != 0)
			objDiversos.toFile("log_erro.log", "---saindo EvoluiPopulacao");

	}

	/**Metodo usado para evoluir a populacao com base no fitness dos individuos.
	 * @throws IOException */
	public void  evolucaoPorFitness() throws IOException{
	 objDiversos.toFile("log_erro.log", "------evolucaoFitness");
  		int cross = 0, mut = 0;
  		double sorteio = 0;
  		int contador = 0;

   //Apagar o arquivo evolucaio.fil caso seja a primeira evolucao da populacao, retirando assim,
  //informaces de execucoes anteriores.
  		if (objCentral.geracaoAtual == 0) {
  			objDiversos.limpaArquivo("evolucao.fil");
  		}
  objDiversos.toFile("evolucao.fil", "");
  objDiversos.toFile("evolucao.fil", "##############################################################");
  String saida = null;
  objDiversos.toFile("evolucao.fil", 
		  String.format("Evolucao Geracao :%d", (int) objCentral.geracaoAtual));
  
  objDiversos.toFile("evolucao.fil", 
		  "==============================================================");
  
  saida =  String.format("EVOLUCAO POR FITNESS (%.0f) / somatoriaFitness = %.0f", (int)objCentral.quantidadeFitness , objCentral.somatoriaFitness);
  objDiversos.toFile("evolucao.fil", saida);
  /**/

  //contador possui a quantidade de individuos gerados e aceitos na proxima geracao.
  //Iteracao para gerar novo individuo enquanto contador for menr que a quantidade configurada.
  for(contador=0; contador < objCentral.quantidadeFitness; )
    {
      sorteio =  objCentral.geraSorteio( objCentral.somatoriaFitness );

      objIndividuo.load((int)indiceIndividuoSorteado(sorteio ));
     
      objDiversos.toFile("evolucao.fil", 
    		  "--------------------------------------------------------------");
      saida = String.format("1 Sorteio : %f : %s", sorteio, objIndividuo.representacao);
      objDiversos.toFile("evolucao.fil", saida);
      /**/

      sorteio = objCentral.geraSorteio( objCentral.somatoriaFitness );
      objIndividuo.load( (int) indiceIndividuoSorteado ( sorteio ) );
      saida = String.format("2 Sorteio : %f : %s", sorteio, objIndividuo.representacao);
      objDiversos.toFile("evolucao.fil", saida);
      /**/

      cross = objMersenne.genrand() % 100;
      
      if(cross <= objCentral.taxaCrossover * 100){
        crossover( (objIndividuo.representacao), (objIndividuo.representacao) );   
        saida = String.format("  op CROSSOVER : %s / %s", 
        		objIndividuo.representacao, objIndividuo.representacao);
        
        objDiversos.toFile("evolucao.fil", saida);    
        }
      
      mut   = objMersenne.genrand() % 100;
      
      if(mut <= objCentral.taxaMutacao * 100){
        mutacao(objIndividuo.representacao);
        saida = String.format(" op MUTACAO 1  : %s", objIndividuo.representacao);
        objDiversos.toFile("evolucao.fil", saida);   
        }
      
      if( toPopulacao( contador, objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
        contador ++;
        saida = String.format(" ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
        objDiversos.toFile("evolucao.fil", saida);        
        }
      
      if(contador < objCentral.quantidadeFitness ){
    	  mut   = objMersenne.genrand() % 100;
        if(mut <= objCentral.taxaMutacao * 100){
          mutacao(objIndividuo.representacao);
          /*prova*/
          saida = String.format("    op MUTACAO 2  : %s", objIndividuo.representacao);
          objDiversos.toFile("evolucao.fil", saida);
          /**/
          }
        if( toPopulacao( contador, objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
          contador ++;
          /*prova*/
          saida = String.format( " ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
          objDiversos.toFile("evolucao.fil", saida);
          /**/
          }
        }// fim if
    } // fim for fitness
  
  if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo evolucaoFitness");
  
}

	/** Metodo retorna o indice do individuo sorteado. Com base na somatoria do
	 * fitness e na ordem dos individuos, simulando o metodo de selecao da
	 * roleta. Retorna qual o individuo possui esta na faixa sorteada.
	 * @throws IOException */
	@SuppressWarnings("unused")
	public int indiceIndividuoSorteado(double sorteio) throws IOException{
		double superior = 0;
		String saida = null;
		//int tamLinha = nroEspacos( (int) objCentral.tamanhoPopulacao ) + 30;
		String linha = null;
		String [] quebra = null;
		FileReader fr = new FileReader(objCentral.arquivoFitness);
		BufferedReader br = new BufferedReader(fr);
				
		if(br == null){
			 saida = String.format("nao abriu o arquivo de Variacao de fitness : %s", objCentral.arquivoVariacaoFitness);
			objDiversos.erro(saida, 1);
		}
		
		linha = br.readLine();
		for (int i=0; ( i < objCentral.tamanhoPopulacao) ; i++)	{
			quebra = linha.split(":");
			linha = quebra [0].trim();
     		superior += Double.parseDouble(linha);
     			if(sorteio <= superior){
     			br.close();        
     			return i;
     		} // fim if
		}// fim for
		
		br.close(); 
		return -1;
	}

	/** Metodo usado para aplicar mutacao em um individuo. */
	public void mutacao(String indiv) {
		int i = 0, mudou = 0, posMut = (int)(Math.random() * indiv.length());
		for (; mudou == 0;) {
			switch (indiv.charAt(posMut)) {
			case '+':
				indiv = indiv.replace(indiv.charAt(posMut), '-');
				mudou = 1;
				break;
			case '-':
				indiv = indiv.replace(indiv.charAt(posMut), '+');
				mudou = 1;
				break;
			// case '#': posMut = rand() % strlen( indiv ); break; //escolhe
			// outra posicao
			case ((char) 216):
				posMut = (int)(Math.random()* indiv.length());
				break; // escolhe outra posicao
			default: {
				int pos = 0;
				mudou = 1;
				for (i = 1; posMut >= objCentral.inicioTipo(i); i++)
					;
				if ((objCentral.formatoIndividuo.charAt(i - 1) == 'C')
						|| (objCentral.formatoIndividuo.charAt(i - 1) == 'S')) {
					indiv = indiv.replace(indiv.charAt(posMut), objDiversos.generateChar(objCentral.tipoString));
				} // fim if
				else {
					indiv = indiv.replace(indiv.charAt(posMut), objDiversos.generateChar("n"));
				} // fim else
			}// fim default
			}// fim switch
		}// fim for
		
	}

	/**
	 * Metodo que aplica operador crossover nos individuos representados por
	 * indiv1 e indiv2
	 */
public void crossover( String  indiv1, String  indiv2 ){
  int i=0, ocorre=0, posCross=0, tamTipo=0, inicTipo=0, tamFormat = 0;
  String block = null,  indivAux = null;

  
   indivAux = indiv1;

  tamFormat =  objCentral.formatoIndividuo.length();
  for(i=0; i<tamFormat; i++)
    {
      ocorre = (int)(Math.random() * 2);
      if(ocorre != 0){    // ocorre crossover no tipo chance de 50%
        inicTipo = objCentral.inicioTipo(i);
        tamTipo =  objCentral.tamanhoTipo(i);
        posCross = ((int)(Math.random() * tamTipo));
        switch( objCentral.formatoIndividuo.charAt(i))
          {
          case 'S':
            {
            
              int maxTam=0, maxTam2=0;
               block = indiv1 + inicTipo;
              //maxTam = objDiversos.indexOf(block, '#');
              maxTam = objDiversos.indexOf(block, (char) 216);
              if(maxTam == -1)
                maxTam = tamTipo;
             block = indiv2 + inicTipo;
              //maxTam2 = objDiversos.indexOf(block, '#');
              maxTam2 = objDiversos.indexOf(block, (char) 216);
              if(maxTam2 == -1)
                maxTam2 = tamTipo;
              if(maxTam > maxTam2)
                maxTam = maxTam2;
              if(maxTam == 0)
                posCross = 0;
              else
                posCross = ((int)(Math.random() * maxTam));
              break;
            }// case
          case 'C':
            {
              posCross = 0;
              break;
            }// case
          }// fim switch
       indiv1 = indiv2+(posCross+inicTipo);
       indiv2 =  indivAux+(posCross+inicTipo);
      }// fim if
    }// fim for
  //  rastro("saiu -  crossover");
 
 
}

	/** Metodo usado para gerar o fitness da populacao 
	 * @throws IOException */
	public void geraFitness() throws IOException{
		
		String saida = null;
		if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------geraFitness");

		String linhaCobertura = null,desempenho = null;
		double fitness = 0, somatoriaFitness = 0, cobertura=0;
				 
		if(objCentral.arquivoCoberturaIndividuo == null) {
      	saida = String.format("nao abriu o arquivo de cobertura/individuo : %s", objCentral.arquivoCoberturaIndividuo );
      	objDiversos.erro(saida, 1 );
		}

		for (int i=0; i < objCentral.tamanhoPopulacao; i++){
			desempenho = desempenho + objDiversos.indexOf(desempenho,':');
			desempenho = desempenho.trim();
			sobrepoe(linhaCobertura, desempenho);

			fitness = (double)objDiversos.numberOf(desempenho, 'X') * 100 / (double) (objCentral.quantidadeElemento);
			saida = String.format("%5d : %10.2f\n", i, fitness);
			objDiversos.escreverArquivo(objCentral.arquivoFitness, saida);
    
		}// fim for
		//rastro("PONTO1.7");*/
 
		objCentral.setSomatoriaFitness(somatoriaFitness );
		objDiversos.toFile( objCentral.arquivoObsCobertura.getPath(), linhaCobertura); 
		objDiversos.toFile("log_erro.log", "------saindo geraFitness");
}

	/** Metodo usado para realizar evolucao por elitismo. 
	 * @throws IOException */
	public void evolucaoPorElitismo() throws IOException{
		 objDiversos.toFile("log_erro.log", "------evolucaoIneditismo");
		 int contador = 0;
		 double posicao = 0;
		 String saida = null;

		 System.out.printf("EVOLUCAO POR INEDITISMO (%.0f)", objCentral.quantidadeIneditismo);
		 
		 for(contador = (int)( objCentral.quantidadeFitness); contador < (int) ( objCentral.quantidadeFitness + objCentral.quantidadeElitismo  ); )  {
			 posicao = melhorFitAntNaoEm( objCentral.arquivoPopulacaoTemporario);
			 if (posicao != -1){
				 objIndividuo.load( (int) posicao );        
				 System.out.printf(" Ineditismo do indiv pos %0.0f : %s", posicao, objIndividuo.representacao);
			 }
			 	else{
			 		objIndividuo.novo();
			 		System.out.printf("Ineditismo do novo indiv : %s", objIndividuo.representacao);
			 	}
			 
			 if ( toPopulacao( contador , objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) )	{
				 contador ++;	  
				 System.out.printf(" ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
	  
			 }
		 } // fim for ineditismo
		 objDiversos.toFile("log_erro.log", "------saindo evolucaoIneditismo");
  }

	/** Metodo usado para obter o indice do individuo a ser mantido 
	 * @throws IOException 
	 * @throws NumberFormatException */
	public double melhorInedAntNaoEm ( File arquivoAuxiliar ) throws NumberFormatException, IOException{
		String saida = null;
		String linha = null;
		FileReader fr = new FileReader(objCentral.arquivoIneditismo);
		BufferedReader br = new BufferedReader(fr);
		
		if(br == null){
			saida = String.format("nao abriu o arquivo de Ineditismo corretamente : %s", objCentral.arquivoIneditismo);
			objDiversos.erro(saida, 1);
		}
		
		int pos2p = 0;
		double posMelhor = -1, pos = 0, ineditismo = 0, ineditismoMelhor = -1;
		int tamLinha = 100;
		
		linha = br.readLine();
		for( int cont = 0; cont < objCentral.tamanhoPopulacao; cont ++ ){
			pos2p = objDiversos.indexOf(linha, ':');
			if(pos2p != -1){
				linha = linha + pos2p + 1;
				linha = linha.trim();
				ineditismo = Double.parseDouble(linha);
				objIndividuo.load(cont);
				if ( (ineditismo > ineditismoMelhor) && (inPopulacao(objIndividuo.representacao, arquivoAuxiliar)) ){
					posMelhor = cont;
					ineditismoMelhor = ineditismo;
				}
			} // fim if
			linha = br.readLine();
		}// fim for
  
		br.close();
  return posMelhor;
}

	/** Metodo usado para obter o indice do individuo a ser mantido 
	 * @throws IOException */
	public double melhorFitAntNaoEm( File arquivoAuxiliar ) throws IOException{
		String saida = null;
		String linha = null;
		int pos2p = 0;
		double posMelhor = -1, pos = 0, fit = 0, fitMelhor = -1;
		  
		FileReader fr = new FileReader(objCentral.arquivoFitness);
		BufferedReader br = new BufferedReader(fr);
		if(br == null){
			saida = String.format("nao abriu o arquivo de Fitness corretamente : %s", objCentral.arquivoFitness);
			objDiversos.erro(saida, 1);
		}
		
		linha  = br.readLine();
		for( int cont = 0; cont < objCentral.tamanhoPopulacao; cont ++ ){
			pos2p = objDiversos.indexOf(linha, ':');
			if(pos2p != -1){
				linha = linha + pos2p + 1;
				linha = linha.trim();
				fit = Double.parseDouble(linha);
				objIndividuo.load(cont);
				if ( (fit > fitMelhor) && (!inPopulacao(objIndividuo.representacao, arquivoAuxiliar) ) ){
					posMelhor = cont;
					fitMelhor = fit;
				}
			} // fim if
			linha  = br.readLine();
		}// fim for   
		br.close();
		return posMelhor;
	}

	/** Metodo usado para calcular o ineditismo da populacao. 
	 * @throws IOException */
	public void  geraBonusIneditismo() throws IOException{
		
		objDiversos.toFile("log_erro.log", "------geraIneditismo");
		String saida = null,  linhaBrPtrCobertura = null;
		String elemCobertura = null;
		int contador=0, cont=0, lixo=0, ponto2=0, quantCob=0;
		double tamElCob = 0, bonificacao = 0;
		int pesoIneditismo = 2;
		tamElCob = objCentral.tamanhoPopulacao + 20;	
		
		FileReader frPtrCobertura = new FileReader( objCentral.arquivoCoberturaElemento);
		BufferedReader brPtrCobertura = new BufferedReader(frPtrCobertura);
 
		if ( brPtrCobertura == null ){
			saida = String.format("nao abriu o arquivo de cobertura de Elementos corretamente : %s", objCentral.arquivoCoberturaElemento);
			objDiversos.erro(saida,1);
		}
		System.out.printf("\n< geraIneditismo> Calculando ineditismo para os elementos\n");
		
		linhaBrPtrCobertura = brPtrCobertura.readLine();
		for (contador = 0; contador < objCentral.quantidadeElemento; contador++){
   			ponto2 = objDiversos.indexOf(linhaBrPtrCobertura,':');
			elemCobertura = elemCobertura + ponto2 + 1;
			elemCobertura = elemCobertura.trim();
    
			if( elemCobertura.length() != objCentral.tamanhoPopulacao ){
			saida = String.format("Erro no calculo da bonificacao p/Elemento %d\nTamanho da linha de cobertura do Elemento = %d, deveria ser %0.0f \n linha de cobertura : '%s'", contador, elemCobertura.length(), objCentral.tamanhoPopulacao, elemCobertura);
			objDiversos.erro(saida , 1);
			}

			bonificacao = 0;
			quantCob = objDiversos.numberOf(elemCobertura, 'X');
			
			if(quantCob!=0)
				bonificacao = 100 * ( 1 - ( quantCob / objCentral.tamanhoPopulacao ) );		
				saida = String.format("%5d : %10.2f\n", contador, bonificacao);
				objDiversos.escreverArquivo(objCentral.arquivoBonusIneditismo, saida);
   
		linhaBrPtrCobertura = brPtrCobertura.readLine();
		}// fim for
		
		brPtrCobertura.close();

	if(objCentral.geraLog != 0) objDiversos.toFile("log_erro.log", "------saindo geraIneditismo");
  }

	/**
	 * Metodo usado para calcular a cobertura dos elementos, com base na
	 * cobertura dos individuos.
	 * @throws IOException 
	 */
	public void geraCoberturaElementos() throws IOException{
		
		if(objCentral.geraLog != 0){ 
			objDiversos.toFile("log_erro.log", "***------geraCoberturaElementos");
		}
		
		String saida = null;
		String linhaCobInd = null,  linhaCobElem = null;
		int contador=0, cont=0, lixo=0, ponto2=0;
				
		FileReader frPtrCobElem = new FileReader(objCentral.arquivoCoberturaElemento);
		BufferedReader brPtrCobertura = new BufferedReader(frPtrCobElem);
		
		FileReader frPtrCobInd = new FileReader( objCentral.arquivoCoberturaElemento);
		BufferedReader brPtrCobInd = new BufferedReader(frPtrCobInd);
		
		if (brPtrCobInd == null){
			saida = String.format("nao abriu o arquivo de cobertura corretamente : %s", objCentral.arquivoCoberturaIndividuo);
			objDiversos.erro(saida ,1);
		}

		linhaCobInd = brPtrCobertura.readLine();
		for (contador = 0; contador < objCentral.quantidadeElemento; contador++){
			
			linhaCobElem = brPtrCobInd.readLine();
			for (cont = 0; cont < (int) (objCentral.tamanhoPopulacao); cont++){
				ponto2 = objDiversos.indexOf(linhaCobInd,':');
				linhaCobInd = linhaCobInd + ponto2 + 1;
				
				if( linhaCobInd.length() == objCentral.quantidadeElemento ){
					linhaCobInd = linhaCobInd.trim();
					linhaCobElem = linhaCobElem.replace(linhaCobElem.charAt(cont), linhaCobInd.charAt(contador));
				}
				linhaCobInd = brPtrCobertura.readLine();
			}// fim for
    
			if(linhaCobElem.length() != objCentral.tamanhoPopulacao ){
				saida = String.format(" geraCoberturaElementos - Cobertura do elemento gerada errada para o elm %d - ", contador);
				objDiversos.erro(saida, 1);
			}
			saida = String.format("%5d : %s\n", contador, linhaCobElem );
			objDiversos.escreverArquivo(objCentral.arquivoCoberturaElemento, saida);
		
			linhaCobInd = brPtrCobertura.readLine();
		}// fim for
		
		brPtrCobInd.close();
		brPtrCobertura.close();
		
		if(objCentral.geraLog != 0){
			objDiversos.toFile("log_erro.log", "***------saindo geraCoberturaElementos");
		}
  
}

	/**
	 * Metodo usado para evoluir populacao com base no indice de ineditismo do
	 * individuo.
	 * @throws IOException 
	 */
	public void evolucaoPorIneditismo() throws IOException{
		
		if(objCentral.geraLog != 0){
			objDiversos.toFile("log_erro.log", "------evolucaoIneditismo");
		}
		int contador = 0;
		double posicao = 0;
				
		System.out.printf("EVOLUCAO POR INEDITISMO (%.0f)", objCentral.quantidadeIneditismo);
  
		for(contador = (int)( objCentral.quantidadeFitness + objCentral.quantidadeElitismo ); contador < (int) ( objCentral.quantidadeFitness + objCentral.quantidadeElitismo + objCentral.quantidadeIneditismo ); ){
			posicao = melhorInedAntNaoEm( objCentral.arquivoPopulacaoTemporario );			
			if (posicao != -1){
				objIndividuo.load( (int) posicao );
      			System.out.printf("Ineditismo do indiv pos %0.0f : %s", posicao, objIndividuo.representacao);
			}			
			else{
				objIndividuo.novo();
				System.out.printf(" Ineditismo do novo indiv : %s", objIndividuo.representacao);
     		}
			
			if ( toPopulacao( contador , objIndividuo.representacao, objCentral.arquivoPopulacaoTemporario ) ){
				contador ++;
				System.out.printf(" ** %d INDIVIDUO   : %s", contador, objIndividuo.representacao);
			}
		} // fim for ineditismo
		
		if(objCentral.geraLog != 0){
			objDiversos.toFile("log_erro.log", "------saindo evolucaoIneditismo");
		}
	}

	/**
	 * Metodo usado para gerar um arquivo que reflita os dados de uma populacao
	 * de forma entendivel/decodificada.
	 * @throws IOException 
	 */
	public void  decodificaPopulacao(File  origem, String  destino) throws IOException{
   
		
		String    block = "",  block_aux = "",  gene = "", saida = null;
		String linhaPtrPopulacao = null;
		int  tamFormato = objCentral.formatoIndividuo.length();
		int  inicBlock,  pos;
		
		int geneTam = 0, tamBloco = 30;
		geneTam = (int) ( objCentral.tamanhoIndividuo + 20 );

		if(objCentral.tamanhoMaximoString > tamBloco){
			tamBloco = (int) objCentral.tamanhoMaximoString;
		}
		
		FileReader frPtrPopulacao = new FileReader(origem);
		BufferedReader brPtrPopulacao = new BufferedReader(frPtrPopulacao);
		  
		if (brPtrPopulacao == null){
			saida =  String.format("nao abriu o arquivo de populacao corretamente : %s", origem);
			objDiversos.erro(saida,1);
		}		
   		  		
  		linhaPtrPopulacao = brPtrPopulacao.readLine();
  		for (int contador = 1; brPtrPopulacao!= null; contador++){
  			gene = linhaPtrPopulacao.trim();
  			if( gene != ""){
  				gene = (gene + objDiversos.indexOf(gene, ':') + 1).trim(); //errado
  				for (int i = 0; i < tamFormato ; i++){
  					inicBlock = objCentral.inicioTipo(i);
  					block = gene + inicBlock;
  					switch( objCentral.formatoIndividuo.charAt(i)){
  						case 'I': block_aux = String.format("%d", objIndividuo.decode_block_int(block) ); break;
  						case 'D': block_aux = String.format("%f", objIndividuo.decode_block_double(block) ); break;
  						case 'F': block_aux = String.format("%f", objIndividuo.decode_block_float(block) ); break;
  						case 'S':{
  							pos = objDiversos.indexOf(block, (char) 216);
  							if(pos == 0) System.out.println("Valor do argumento string eh vazio... avaliar impacto");
  							if(pos != -1) block = block.replace(block.charAt(pos), '\0');
  							block_aux = block ;
  							break;
  						}
  						case 'C': {  							
  							block_aux = block ;
  							break;
  						}
  					}// fim switch
  					objDiversos.escreverArquivo(destino,  block_aux);		
  					if( i != tamFormato - 1 ){
  						objDiversos.escreverArquivo(destino,  ", ");
  					}
  				}//fim for  		
  			} // fim if gene == ""
  			linhaPtrPopulacao = brPtrPopulacao.readLine();
  		} // fim for
  
  		brPtrPopulacao.close();
  		if(objCentral.geraLog != 0){
  			objDiversos.toFile("log_erro.log", "---decodificaPopulacao");  
  		}
	}


	/**
	 * Este metodo retorna o valor do bonus para os individuos que cobriram o
	 * elemento informado por pos.
	 * @throws IOException 
	 */
	public double  getBonusElemento(int pos) throws IOException{

		int i = 0;
		String gene = null,  bonificacaoStr = null, saida = null, linha = null;
		File ptrBonusIneditismo = null;
		double bonificacao = 0;
		
		FileReader fr = new FileReader(objCentral.arquivoBonusIneditismo);
		BufferedReader br = new BufferedReader(fr);
		
		if(ptrBonusIneditismo == null){
			saida = String.format("getBonusElemento - Nao abriu corretamente o arquivo  : %s"
					, objCentral.arquivoCoberturaIndividuo );
			objDiversos.erro( saida, 1 );
		}
		
		if(pos >= objCentral.quantidadeElemento){
			saida = String.format("Pos, %d, extrapolou o indice do elemento buscado %f", pos, objCentral.quantidadeElemento);
			objDiversos.erro(saida ,1);
		}
 		
		linha = br.readLine();
		for (i = 0; i <= pos; i++){
			gene = linha;     
			linha = br.readLine();
		}// fim for
		br.close();
  
      i = objDiversos.indexOf(gene.trim(), ':') + 1;
      bonificacaoStr = gene + i ;      
      bonificacao = Double.parseDouble(bonificacaoStr.trim()); 
 
      return bonificacao;
	}

	/** Gera o arquivo com a bonificacao final por ineditismo. 
	 * @throws IOException */
	public void geraIneditismoPopulacao() throws IOException{

		if(objCentral.geraLog != 0){
			objDiversos.toFile("log_erro.log", "---------geraIneditismoPopulacao");
		}
		
		String linhaCobInd = null, saida = null;
		int cont=0, ponto2=0;
		double ineditismo = 0;		
		
		FileReader fr = new FileReader(objCentral.arquivoCoberturaIndividuo);
		BufferedReader brPtrCobInd = new BufferedReader(fr);
		
		if (brPtrCobInd == null){
			saida = String.format("nao abriu o arquivo de cobertura corretamente : %s", objCentral.arquivoCoberturaIndividuo);
			objDiversos.erro(saida,1);
		}
		
		linhaCobInd = brPtrCobInd.readLine();
		for (cont = 0; cont < (int) (objCentral.tamanhoPopulacao); cont++){
			ponto2 = objDiversos.indexOf(linhaCobInd,':');
			linhaCobInd = linhaCobInd + ponto2 + 1;
			ineditismo = 0;
			if( linhaCobInd.length() != objCentral.quantidadeElemento ){
				saida = String.format(" geraIneditismoPopulacao - Cobertura do individuo gerada errada para o individuo %d - ", cont);
				objDiversos.erro(saida, 1);
			}

			for (int i = 0; i < objCentral.quantidadeElemento; i++){
				if ( linhaCobInd.charAt(i)== 'X')
				ineditismo += getBonusElemento( i );
			}// fim for
			
			saida = String.format( "%5d : %f\n", cont, ineditismo);
			objDiversos.escreverArquivo(saida, objCentral.arquivoIneditismo.getPath());   
			linhaCobInd = brPtrCobInd.readLine();	
     }// fim for 
		brPtrCobInd.close();

  if(objCentral.geraLog != 0){
	  objDiversos.toFile("log_erro.log", "---------saindo geraIneditismoPopulacao");
  }

}
}
