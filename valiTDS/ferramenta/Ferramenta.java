package ferramenta;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import main.Diversos;
import algoritmoGenetico.*;

public class Ferramenta {
	/***************************************************************************
	 * ferramenta.cpp - description ------------------- begin : Dom Jul 6 2003
	 * copyright : (C) 2003 by Luciano Petinati Ferreira email :
	 * petinat@inf.ufpr.br
	   This program is free software; you can redistribute it and/or modify *
	 * it under the terms of the GNU General Public License as published by *
	 * the Free Software Foundation; either version 2 of the License, or * (at
	 * your option) any later version. * *
	 ***************************************************************************/

	Central objCentral;
	Diversos objDiversos;
	ValiMPI objUsaValiMPI;
	Individuo objIndividuo;

	public Ferramenta() {
		 System.out.println( "\nConstruindo ferramenta...");
		objCentral = new Central();
		objDiversos = new Diversos();
		objUsaValiMPI = new ValiMPI();
		objIndividuo = new Individuo();
		
	}

	
	/**Metodo usado para inicar a ferramenta adequada baseado nas informacoes de
	 * controle contidas em ctl.
	 * @throws IOException
	 * @throws InterruptedException */
	public void prepareTool() throws IOException, InterruptedException {
		String mpi_root;

		System.out.println("\nUtilizando ValiMPI.");

		objUsaValiMPI.exeVali_inst(objCentral.arquivoFonte);
		objUsaValiMPI.exeVali_reduce(null); // ainda nao implementadotado
		objUsaValiMPI.exeVali_elem(objCentral.nProcess, objCentral.funcoes);
		objUsaValiMPI.exeVali_cc(objCentral.funcaoATestar);

		System.out.println("Termina uso da ValiMPI.");
	}
 

	/*** Metodo usado para obter a quantidade de elementos requeridos pelo
	 * criterio configurado. 
	 * @throws IOException */
	public double obtemElementosRequeridos() throws IOException {
		System.out.println("\n\nObtendo elementos requeridos");
		return obtemElementosRequeridosValiMPI();
	}

	 
	/** Metodo usado para obter a quantidade de elementos requeridos para
	 * criterios suportados pela ferramenta ValiMPI. 
	 * @throws IOException */
	public double obtemElementosRequeridosValiMPI() throws IOException {
		System.out.println("\n---obtemElementosValiMPI");

		double quantidadeElemReq = 0;
		String dir_elem_req = "valimpi/res/";

		File arquivoElementos;
		arquivoElementos = new File("arquivoElementos.elem");
		arquivoElementos.createNewFile();
		
		objCentral.criterioTeste = "Todos os Arcos";
		
		if (objCentral.criterioTeste.equals("Todos os Arcos")) {
			objDiversos.copyFile((dir_elem_req + "todas-arestas.req"),
					arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todas-arestas");
		}

		else if (objCentral.criterioTeste.equals("Todos os Nos")) {
			objDiversos.copyFile((dir_elem_req + "todos-nos.req"), arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-nos");
			
		} else if (objCentral.criterioTeste.equals("Todos os Potenciais Usos")) {
			objDiversos.copyFile((dir_elem_req + "todos-p-usos.req"), arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-p-usos");
			
		} else if (objCentral.criterioTeste	.equals("Todos os Usos Computacionais")) {
			objDiversos.copyFile((dir_elem_req + "todos-c-usos.req"), arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-c-usos");
			
		} else if (objCentral.criterioTeste	.equals("Todos os Usos de Sincronismo")) {
			objDiversos.copyFile((dir_elem_req + "todos-s-usos.req"), arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-s-usos");
			
		} else if (objCentral.criterioTeste.equals("Todos os Nos S")) {
			objDiversos.copyFile((dir_elem_req + "todos-nosS.req"),	arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-nosS");
			
		} else if (objCentral.criterioTeste.equals("Todos os Nos R")) {
			objDiversos.copyFile((dir_elem_req + "todos-nosR.req"),	arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todos-nosR");
			
		} else if (objCentral.criterioTeste.equals("Todos as Arestas S")) {
			objDiversos.copyFile((dir_elem_req + "todas-arestasS.req"),
					arquivoElementos);
			objCentral.setCriterioTesteValiMPI("todas-arestasS");
		}

		objDiversos.copyFile((dir_elem_req + "todos-nos.req"),
		 arquivoElementos);

		if (arquivoElementos.length() == 0) {
			objDiversos
					.erro("nao abriu o arquivo dos elementos requeridos da ValiMPI corretamente",
							1);
		}

		//menos 2 são as duas primeiras linhas do arq. que n se refere aos elementos
		quantidadeElemReq = objDiversos.quantidadeLinhas(arquivoElementos)- 2; 
		System.out.print("\n--- Saindo de obtemElementosValiMPI");
				
		return quantidadeElemReq;

	}

	
	/**Metodo usado para avaliar o nro-esimo individuo da populacao. Recupera o
	 * nro-esimo individuo da populacao; Recupera os argumentos/entradas que
	 * este representa; Separa os argumentos (argumento de chamada ou entrada de
	 * teclado) conforme necessidade do programa; Executa o programa e avalia o
	 * resultado da execucao.
	 * @throws IOException 
	 * @throws InterruptedException 
	 */
	public void evaluateIndividual(int nro) throws IOException, InterruptedException {
		int tamFormato = objCentral.formatoIndividuo.length();

		String argMascarado = "";
		String argPuroStr = "";
		String linhaArgumento = "";
		int inicBlock = -1;
		objIndividuo.load(nro);

		//laco usado para recuperar cada individeo da populacao e decodificalo 
		for (int argCont = 0; argCont < tamFormato; argCont++) {
			
			// para cada argumento/tipo do individuo
			inicBlock = objCentral.inicioTipo(argCont);
			argMascarado = objIndividuo.representacao + inicBlock;

			switch (objCentral.formatoIndividuo.charAt(argCont)) {
			
			case 'I':argPuroStr = String.valueOf(objIndividuo.decode_block_int(argMascarado));
				break;
				
			case 'D':argPuroStr = String.valueOf(objIndividuo.decode_block_double(argMascarado));
				break;
				
			case 'F':argPuroStr = String.valueOf(objIndividuo.decode_block_float(argMascarado));
				break;
				
			case 'C':argPuroStr = argMascarado;
				break;
				
			case 'S': {	int pos = objDiversos.indexOf(argMascarado, (char) 216);
			
				if (pos == 0){
					System.out.println("Valor do argumento string eh vazio...ignorando... avaliar impacto");
				}
				
				if (pos != -1){
					argMascarado = argMascarado.replace(argMascarado.charAt(pos), '\0');
				}
				
					argPuroStr = argMascarado;
				break;
			}
			}// fim switch

				//bloco que recupera o dado e coloca em uma única varia
		         if ( argCont == 0 ){
		            linhaArgumento = argPuroStr;
		         }
		         else {
		        	 linhaArgumento = linhaArgumento.concat(argPuroStr);
		         }
		         linhaArgumento = linhaArgumento.concat(" ");
		         
		      } // fim for    
		
		//executa dado na valimpi
		objUsaValiMPI.exeVali_exec("1", objCentral.nProcess, objCentral.funcaoATestar, linhaArgumento);
		// avalia dado recem executado na valimpi
		objUsaValiMPI.exeVali_eval(objCentral.criterioTeste, objCentral.nProcess, objCentral.funcoes);      
	}


	/** Metodo usado para obter linha de cobertura que contem o desempenho do
	 * individuo perante aos elementos requeridos.
	 * @throws IOException */
	public void obtemCoberturaValiMPI() throws IOException{
		
		String[] vetorPegaElementos;
		vetorPegaElementos = pegaElementos("arquivoElementos.elem");

		String[] vetorPegaElementosCobertos;
		vetorPegaElementosCobertos = pegaElementosCobertos("gcd/vali_eval.out");		
		int [] saida = new int [vetorPegaElementos.length];
		String linhaCoberturaAtual = "";
		
		for (int i = 0; i < vetorPegaElementos.length; i++) {
		for (int j = 0; j < vetorPegaElementosCobertos.length; j++) {
			if (vetorPegaElementos[i].equals(vetorPegaElementosCobertos[j])) {
				saida [i] = 1 ;						
			}								
		}// termina for para i
		}// termina for para j			
		}
	
	
	/**Pega os elementos requiridos presente em "arquivoElementos.elem" e c
	 *coloca em um vetor	 
	 * @throws IOException */
	public  String [] pegaElementos (String arquivo) throws IOException{
		
		
		String [] vetor = new String [(int) objCentral.quantidadeElemento];
		String linhaArqElementos = null;
		int contLinhaElementos = 0;
		
		// permissoes de leitura do arquivo de elementos
		FileReader arqElemementos = new FileReader(arquivo);
		BufferedReader lerArqElemementos = new BufferedReader(arqElemementos);
		
		// le a primeira linah do arquivo 
		linhaArqElementos = lerArqElemementos.readLine();
			for( int i = 0; linhaArqElementos != null; ){
				contLinhaElementos++;				
				//pega os elementos a partir da segunda linha do arquivo
				if(contLinhaElementos>2){
					vetor[i]=linhaArqElementos.trim();
					i++;
				}				
				linhaArqElementos = lerArqElemementos.readLine();		
			}				
			lerArqElemementos.close();		
		return vetor;
	}
	
	/**Pega os elementos requiridos cobertos presente em "gcd/vali_eval.out" e 
	 * coloca em um vetor
	 * @throws IOException */
	public  String[] pegaElementosCobertos(String arquivo)	throws IOException {
		String[] vetor = new String[62];
		String linhaArqElemcobertos = null;
		int contLinhaElementos = 0;
		String[] quebraLinha = null;
		// permissoes de leitura do arquivo que contém os elem cobertos
		FileReader arqElemCobertos = new FileReader(arquivo);
		BufferedReader lerElemCobertos = new BufferedReader(arqElemCobertos);

		linhaArqElemcobertos = lerElemCobertos.readLine();
		for (int i = 0; linhaArqElemcobertos != null; ) {
			contLinhaElementos++;			
			//para quando alcaçar a linha elementos nao cobertos
			if(linhaArqElemcobertos.equals("-- ELEMENTOS REQUERIDOS NÃO COBERTOS --")){
						break;
			}			
			//iniccia a partir da segunda linha
			if(objCentral.criterioTeste.equals("Todos os Usos de Sincronismo")
				|| objCentral.criterioTeste.equals("Todos os Usos Computacionais")
				||objCentral.criterioTeste.equals("Todos os Potenciais Usos")){
				
				quebraLinha = linhaArqElemcobertos.split("> c");
				vetor[i] = quebraLinha[0].trim();		
			}else{
			quebraLinha = linhaArqElemcobertos.split(",");
			vetor[i] = quebraLinha[0].trim();				
			}
			linhaArqElemcobertos = lerElemCobertos.readLine();
		}// fim while
		
		lerElemCobertos.close();
		return vetor;
	}
}