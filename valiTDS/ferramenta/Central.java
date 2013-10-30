package ferramenta;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Formatter;
import java.util.TimeZone;
import java.util.zip.Deflater;
import java.util.zip.ZipOutputStream;

import javax.print.attribute.IntegerSyntax;

import main.Diversos;
import main.Mersenne;

public class Central {
	/***************************************************************************
	 * central.cpp - description ------------------- begin : Dom Jul 6 2003
	 * copyright : (C) 2003 by Luciano Petinati Ferreira email :
	 * petinat@inf.ufpr.br * This program is free software; you can redistribute
	 * it and/or modify * it under the terms of the GNU General Public License
	 * as published by * the Free Software Foundation; either version 2 of the
	 * License, or * (at your option) any later version. * *
	 ***************************************************************************/

	/** Variavel de controle para pausar a execucao a cada geracao. */
	public int pausaGeracao;
	/** Variavel de controle para gerar log da execucao. */
	public int geraLog;
	/**
	 * Variavel de controle para indicar quantos argumentos o programa em teste
	 * necessita
	 */
	public int numeroArgumentos;
	/**
	 * Variavel de controle para indicar o tamanho manimo para o tipo string (*
	 * String ).
	 */
	public double tamanhoMinimoString;
	/**
	 * Variavel de controle para indicar o tamanho maximo para o tipo string (*
	 * String ).
	 */
	public double tamanhoMaximoString;
	/**
	 * Variavel de controle para indicar o tamanho manimo para o tipo inteiro.
	 */
	public int tamanhoMinimoInteiro;
	/**
	 * Variavel de controle para indicar o tamanho maximo para o tipo inteiro.
	 */
	public int tamanhoMaximoInteiro;
	/**
	 * Variavel de controle para indicar o tamanho maximo que um argumento
	 * podeassumir para o programa em teste, desconsiderando seu tipo.
	 */
	public double tamanhoMaximoArgumento;
	/** Variavel de controle para indicar a variacao do tipo inteiro. */
	public int variacaoInteiro;
	/**
	 * Variavel de controle para indicar a quantidade de elementos requeridos
	 * para o programa em teste.
	 */
	public double quantidadeElemento;
	/**
	 * Variavel de controle para conter a cobertura de elementos requeridos da
	 * populacao atual.
	 */
	public double coberturaAtual;
	/**
	 * Variavel de controle para conter a somataria do fitness de todos os
	 * indivaduos para auxiliar a selecao por roleta.
	 */
	public double somatoriaFitness;
	/**
	 * Variavel de controle para indicar o critario de teste a ser usado na
	 * execucao do framework.
	 */
	public String criterioTeste;
	/**
	 * Variavel de controle para indicar a funcao a ser testada do programa em
	 * este.
	 */
	public String funcaoATestar;
	/**
	 * Variavel de controle para indicar o critario de teste da valiMPI a ser
	 * usado na execucao do framework.
	 */
	public String criterioTesteValiMPI;
	/**  */
	public File diretorio;
	/**
	 * Variavel de controle para indicar o diretario pool, usado para entrada de
	 * dados na execucao do programa ja instrumentado.
	 */
	public String diretorioPool;
	/**
	 * Variavel de controle para indicar o namero maximo de geracaes a serem
	 * geradas caso a cobertura desejada nao seja alcanaada.
	 */
	public double maximoGeracoes;
	/** Variavel de controle para indicar a geracao atual. */
	public double geracaoAtual;
	/** Variavel de controle para indicar o andice da melhor geracao. */
	public double indiceMelhorGeracao;
	/**
	 * Variavel de controle para indicar o tamanho do indivaduo usado no AG.
	 */
	public double tamanhoIndividuo;
	/**
	 * Variavel de controle para indicar o tamanho da populacao usada no AG.
	 */
	public double tamanhoPopulacao;
	/**
	 * Variavel de controle para indicar a cobertura desejada para o critario
	 * selecionado.
	 */
	public double coberturaCriterio; // novo nome coberturaDesejada
	/**
	 * Variavel de controle para indicar a melhor cobertura possavel atravas de
	 * todo o processo. Usa informacaes da lista Tabu.
	 */
	public double melhorCobertura;
	/** Variavel de controle para indicar a taxa de mutacao usada no AG. */
	public double taxaMutacao;
	/** Variavel de controle para indicar a taxa de Crossover usada no AG */
	public double taxaCrossover;
	/**
	 * Variavel de controle para indicar a quantidade de indivaduos da nova
	 * geracao que devem ser gerados com base no elitismo (fitness).
	 */
	public double quantidadeElitismo;
	/**
	 * Variavel de controle para indicar a quantidade de indivaduos da nova
	 * geracao que devem ser gerados com base no score de ineditismo dos
	 * indivaduos.
	 */
	public double quantidadeIneditismo;
	/**
	 * Variavel de controle para indicar a quantidade de indivaduos da nova
	 * geracao que devem ser gerados com base na selecao e operadores genaticos.
	 */
	public double quantidadeFitness; // novo nome quantidadeSelecao
	/**
	 * * Variavel de controle para indicar o formato da entrada do programa,
	 * consequentemente o formato do indivaduo do AG.
	 */
	public String formatoIndividuo;
	/**
	 * * Variavel de controle para conter informacaes sobre perda de cobertura
	 * de elementos requeridos.
	 */
	public String linhaPerda;
	/**
	 * Variavel de controle para conter a cobertura atual de elementos
	 * requeridos ( X: para coberto, -: para nao coberto ).
	 */
	public String linhaCoberturaAtual;
	/**
	 * Variavel de controle para conter informacaes de cobertura de elementos
	 * requeridos da geracao anterior.
	 */
	public String linhaCoberturaAnterior;
	/**
	 * Variavel de controle para conter informacaes a cobertura global de
	 * elementos requeridos, independente de geracao.
	 */
	public String coberturaGlobal; // novo nome linhaCoberturaGlobal
	/** Variavel de controle para conter o nome do arquivo da lista Tabu. */
	public File arquivoTabu;
	/**
	 * Variavel de controle para conter o nome do arquivo temporario da lista
	 * Tabu.
	 */
	public File arquivoTabuAux;
	/**
	 * Variavel de controle para conter o nome do arquivo fonte do programa em
	 * teste.
	 */
	public String arquivoFonte;
	/**
	 * Variavel de controle que identifica o tipo de string que o framework
	 * suporta.
	 */
	public String tipoString;
	/**
	 * Variavel de controle que contera o comando a ser executado por chamada
	 * system com variavel de ambiente PATH corretamente configurada.
	 */
	public String comandPath;
	/**
	 * Variavel de controle que contera o PATH correto baseado na ferramenta de
	 * teste a ser usada.
	 */
	// String enviroment;
	public String enviroment;

	/** Atributos sem comentarios... */
	public File arquivoPopulacaoInicial;
	public File arquivoPopulacao;
	public File arquivoMelhorPopulacao;
	public File arquivoPopulacaoTemporario;
	public File arquivoFitness;
	public File arquivoVariacaoFitness;
	public File arquivoCoberturaIndividuo;
	public File arquivoCoberturaElemento;
	public File arquivoAvalCobIndividuos;
	public File arquivoSemelhancaIndividuos;
	public File arquivoObsCobertura;
	public File arquivoRepositorio;

	public long tamEnviroment;
	/** Variavel de controle para manter o tamanho de enviroment. */

	public long tamComandPath;
	/** Variavel de controle para manter o tamanho de comandPath. */
	public File arquivoPopulacaoTemporario2;
	/**
	 * Atributo usado para conter o nome para um arquivo temporario para a
	 * populacao.
	 */
	public int ativaTabu = 0;
	/** Atributo usado para controlar a ativacao do recurso de lista Tabu. */
	public File arquivoBonusIneditismo;
	public File arquivoIneditismo;
	/**
	 * Atributo usado para guardar quantas gercaes serao usadas/configuradas
	 * para verificar o repositario de execucao antes de executar um determinado
	 * caso de teste. Isto pode aumentar o desempenho do sistema.
	 */
	public double geracoesComRepositorio;
	/** Atributo com o tempo em segundos da execucao do sistema. */
	public int inicioExecucao;
	/** Atributo com o tempo em segundo do fim de execucao do sistema */
	public long fimExecucao;
	/**
	 * Atributo com o tempo em segundo do fim da primeira execucao do sistema
	 */
	public long fimPrimeiraExecucao;
	/** Atributo para manter a cobertura inicial do processo. */
	public double coberturaInicial;

	/** Atributo que diz quantos processos o programa usa. */
	public String nProcess;
	/** Atributo que diz qual processo sera qual namero */
	public String funcoes;
	public String ccargs;

	Diversos objDiversos; // declaracao do objeto diversos
	Mersenne objMersenne;
	String pegaDiretorio;
	File arquivoResumo;

	public Central() {

		objDiversos = new Diversos(); // instaciacao do objeto da classe
										// diversos
		objMersenne = new Mersenne();

		// cout << "\nConstruindo central...";
		int inicioExecucao;
		fimExecucao = 0;
		fimPrimeiraExecucao = 0;
		pausaGeracao = 0;
		ativaTabu = 0;
		geraLog = 0;
		numeroArgumentos = 0;
		tamanhoMinimoString = 1;
		tamanhoMaximoString = 30;
		tamanhoMinimoInteiro = 0;
		tamanhoMaximoInteiro = 10000;
		tamanhoMaximoArgumento = 30;
		variacaoInteiro = 10000;
		quantidadeElemento = 0;
		coberturaAtual = 0;
		somatoriaFitness = 0;
		criterioTeste = null;
		funcaoATestar = null;
		// criterioTestePoketool = null;
		// diretorio = null;
		// diretorioPool = null;
		maximoGeracoes = 0;
		geracaoAtual = 0;
		indiceMelhorGeracao = 0;
		tamanhoIndividuo = 0;
		tamanhoPopulacao = 0;
		coberturaCriterio = 0; // novo nome coberturaDesejada
		coberturaInicial = 0;
		melhorCobertura = 0;
		taxaMutacao = 0;
		taxaCrossover = 0;
		quantidadeElitismo = 0;
		quantidadeIneditismo = 0;
		quantidadeFitness = 0; // novo nome quantidadeSelecao
		geracoesComRepositorio = 50;

		formatoIndividuo = "";
		linhaPerda = "";
		linhaCoberturaAtual = "";
		linhaCoberturaAnterior = "";
		coberturaGlobal = "";
		arquivoTabu = null;
		arquivoTabuAux = null;
		arquivoFonte = "";
		arquivoPopulacaoInicial = null;
		arquivoPopulacao = null;
		arquivoMelhorPopulacao = null;
		arquivoPopulacaoTemporario = null;
		arquivoFitness = null;
		arquivoVariacaoFitness = null;
		arquivoCoberturaIndividuo = null;
		arquivoCoberturaElemento = null;
		arquivoAvalCobIndividuos = null;
		arquivoSemelhancaIndividuos = null;
		arquivoObsCobertura = null;
		arquivoRepositorio = null;
		arquivoBonusIneditismo = null;
		arquivoIneditismo = null;
		criterioTeste = "";
		funcaoATestar = "";
		criterioTesteValiMPI = "";
		diretorio = null;
		diretorioPool = "";
		tipoString = "";
		comandPath = "";
		enviroment = " ";
		arquivoPopulacaoTemporario2 = null;
		funcoes = "";
		ccargs = "";

		nProcess = "";

		tamEnviroment = 480;
		tamComandPath = 600;

	}

	/**
	 * Metodo que mostra na tela o valor de todas as variaveis de controle da
	 * classe central.
	 */
	public void printAll() {
		System.out.println("\n pausaGeracao  " + pausaGeracao);
		System.out.println("\n ativaTabu = " + ativaTabu);
		System.out.println("\n geraLog = " + geraLog);
		System.out.println("\n numeroArgumentos = " + numeroArgumentos);
		System.out.println("\n tamanhoMinimoString = " + tamanhoMinimoString);
		System.out.println("\n tamanhoMaximoString = " + tamanhoMaximoString);
		System.out.println("\n tamanhoMinimoInteiro = " + tamanhoMinimoInteiro);
		System.out.println("\n tamanhoMaximoInteiro = " + tamanhoMaximoInteiro);
		System.out.println("\n tamanhoMaximoArgumento = "
				+ tamanhoMaximoArgumento);
		System.out.println("\n variacaoInteiro = " + variacaoInteiro);
		System.out.println("\n quantidadeElemento = " + quantidadeElemento);
		System.out.println("\n coberturaAtual = " + coberturaAtual);
		System.out.println("\n somatoriaFitness = " + somatoriaFitness);
		System.out.println("\n maximoGeracoes = " + maximoGeracoes);
		System.out.println("\n geracaoAtual = " + geracaoAtual);
		System.out.println("\n indiceMelhorGeracao = " + indiceMelhorGeracao);
		System.out.println("\n tamanhoIndividuo = " + tamanhoIndividuo);
		System.out.println("\n tamanhoPopulacao = " + tamanhoPopulacao);
		System.out.println("\n coberturaCriterio = " + coberturaCriterio);
		System.out.println("\n melhorCobertura = " + melhorCobertura);
		System.out.println("\n taxaMutacao = " + taxaMutacao);
		System.out.println("\n taxaCrossover = " + taxaCrossover);
		System.out.println("\n quantidadeElitismo = " + quantidadeElitismo);
		System.out.println("\n quantidadeIneditismo = " + quantidadeIneditismo);
		System.out.println("\n quantidadeFitness = " + quantidadeFitness);
		System.out.println("\n geracoesComRepositorio = "
				+ geracoesComRepositorio);
		System.out.println("\n formatoIndividuo = " + formatoIndividuo);
		System.out.println("\n linhaPerda = " + linhaPerda);
		System.out.println("\n linhaCoberturaAtual = " + linhaCoberturaAtual);
		System.out.println("\n linhaCoberturaAnterior = "
				+ linhaCoberturaAnterior);
		System.out.println("\n coberturaGlobal = " + coberturaGlobal);
		System.out.println("\n arquivoTabu = " + arquivoTabu);
		System.out.println("\n arquivoTabuAux = " + arquivoTabuAux);
		System.out.println("\n arquivoFonte = " + arquivoFonte);
		System.out.println("\n arquivoPopulacaoInicial = "
				+ arquivoPopulacaoInicial);
		System.out.println("\n arquivoPopulacao = " + arquivoPopulacao);
		System.out.println("\n arquivoMelhorPopulacao = "
				+ arquivoMelhorPopulacao);
		System.out.println("\n arquivoPopulacaoTemporario = "
				+ arquivoPopulacaoTemporario);
		System.out.println("\n arquivoFitness = " + arquivoFitness);
		System.out.println("\n arquivoVariacaoFitness = "
				+ arquivoVariacaoFitness);
		System.out.println("\n arquivoCoberturaIndividuo = "
				+ arquivoCoberturaIndividuo);
		System.out.println("\n arquivoCoberturaElemento = "
				+ arquivoCoberturaElemento);
		System.out.println("\n arquivoAvalCobIndividuos = "
				+ arquivoAvalCobIndividuos);
		System.out.println("\n arquivoSemelhancaIndividuos = "
				+ arquivoSemelhancaIndividuos);
		System.out.println("\n arquivoObsCobertura = " + arquivoObsCobertura);
		System.out.println("\n arquivoRepositorio = " + arquivoRepositorio);
		System.out.println("\n arquivoBonusIneditismo = "
				+ arquivoBonusIneditismo);
		System.out.println("\n arquivoIneditismo = " + arquivoIneditismo);
		System.out.println("\n criterioTeste = " + criterioTeste);
		System.out.println("\n funcaoATestar = " + funcaoATestar);
		System.out.println("\n criterioTesteValiMPI = " + criterioTesteValiMPI);
		System.out.println("\n diretorio = " + diretorio);
		System.out.println("\n diretorioPool = " + diretorioPool);
		System.out.println("\n tipoString = " + tipoString);

		System.out.println("\n funcoes =" + funcoes);
		System.out.println("\n numero_processos =" + nProcess);

	}

	// _________________________________________________________________
	/**
	 * Metodo que carrega na classe central informacaes sobre a execucao da
	 * ferramenta.
	 * 
	 * @throws IOException
	 */
	public void interpretaArquivoConfiguracao() throws IOException {

		String nomeArq = "arqconfig.txt"; // Nome do arquivo,
		// pode ser absoluto, ou pastas /dir/teste.txt
		String linha = "", parametro = "", valorIntermediario = "", valor = "";
		String quebra[];
		String quebra2[];

		FileReader arq = new FileReader(nomeArq);
		BufferedReader lerArq = new BufferedReader(arq);

		if (lerArq == null) {
			objDiversos.erro(
					"nao abriu o arquivo corretamente : arqconfig.txt", 1);
		}
		setTipoString("alfabetico");

		linha = lerArq.readLine(); // la a primeira linha

		// a variavel "linha" recebe o valor "null" quando o processo
		// de repeticao atingir o final do arquivo texto
		while (linha != null) {

			if (linha.charAt(0) == '#') {
				// System.out.println("passei aqui");
				quebra = linha.split("=");
				parametro = quebra[0].trim(); // pega parametro
				valorIntermediario = quebra[1].trim(); // pega valor
				quebra2 = valorIntermediario.split(";");
				valor = quebra2[0].trim();

				if (parametro.equals("#NumeroArgumentos"))
					setNumeroArgumentos(Integer.parseInt(valor));
				else if (parametro.equals("#Log"))
					setGeraLog(1);
				else if (parametro.equals("#PausaGeracao"))
					setPausaGeracao(1);
				else if (parametro.equals("#Elitismo"))
					setQuantidadeElitismo(Integer.parseInt(valor));
				else if (parametro.equals("#Ineditismo"))
					setQuantidadeIneditismo(Integer.parseInt(valor));
				else if (parametro.equals("#Fitness"))
					setQuantidadeFitness(Integer.parseInt(valor));
				else if ((parametro.equals("#ArquivoFonte"))
						|| (parametro.equals("#SourceFile")))
					setArquivoFonte(valor);
				else if ((parametro.equals("#FormatoEntrada"))
						|| (parametro.equals("#InputFormat")))
					setFormatoIndividuo(valor);
				else if ((parametro.equals("#VariacaoString"))
						|| (parametro.equals("#StringRange")))
					setTamanhoString(valor);
				else if ((parametro.equals("#StringType"))
						|| (parametro.equals("#TipoString")))
					setTipoString(valor);
				else if ((parametro.equals("#ArquivoPopulacao"))
						|| (parametro.equals("#PopulationFile")))
					setArquivoPopulacaoInicial(valor);
				else if ((parametro.equals("#TamanhoPopulacao"))
						|| (parametro.equals("#PopulationSize")))
					setTamanhoPopulacao(Integer.parseInt(valor));
				else if ((parametro.equals("#NumeroGeracoes"))
						|| (parametro.equals("#GenerationNumber")))
					setMaximoGeracoes(Integer.parseInt(valor));
				else if ((parametro.equals("#CoberturaCriterio"))
						|| (parametro.equals("#CriterioCoverage")))
					setCoberturaCriterio(Integer.parseInt(valor));
				else if ((parametro.equals("#Criterio"))
						|| (parametro.equals("#Criterium")))
					setCriterioTeste(valor);
				else if ((parametro.equals("#TaxaMutacao"))
						|| (parametro.equals("#MutationRate")))
					setTaxaMutacao(Double.parseDouble(valor));
				else if ((parametro.equals("#TaxaCrossover"))
						|| (parametro.equals("#CrossOverRate")))
					setTaxaCrossover(Double.parseDouble(valor));
				else if ((parametro.equals("#VariacaoInt"))
						|| (parametro.equals("#IntRange")))
					setVariacaoInteiro(valor);

				else if (parametro.equals("#NomeFuncao")) {
					setFuncaoATestar(valor);
					setDiretorio(valor);
					setArquivoPopulacao(valor);
					setArquivoPopulacaoTemporario(valor);
					setArquivoFitness(valor);
					setArquivoIneditismo(valor);
					setArquivoBonusIneditismo(valor);
					setArquivoVariacaoFitness(valor);
				}// fim if-then
				else if ((parametro.equals("#AtivaTabu"))
						&& ((valor.equals("sim")) || (valor.equals("Sim")) || ((valor
								.equals("1"))))) {
					setArquivoTabu("tabu");
					setArquivoTabuAux("tabuAux");
				}

				else if (parametro.equals("#GeracoesComRepositorio"))
					setGeracoesComRepositorio(Integer.parseInt(valor));

				else if (parametro.equals("#NumeroProcessos"))
					setNProcess(valor);
				else if (parametro.equals("#Funcoes"))
					setFuncoes(valor);
				else if (parametro.equals("#CCArgs"))
					setCCArgs(valor);

				linha = lerArq.readLine();
			} else {
				System.out.printf("\n IGNORANDO: %s", linha);
				linha = lerArq.readLine();
			}
		}
		arq.close();

		setArquivoCoberturaElemento("cobXElemento");
		setArquivoCoberturaIndividuo("cobXIndividuo");
		setArquivoSemelhancaIndividuos("semelhancaIndividuos");
		setArquivoAvalCobIndividuos("avalCobIndividuos");
		setArquivoRepositorio("repositorio");
		// setDiretorioPool("pool");
		setArquivoObsCobertura("relCobertura");
		setTamanhoIndividuo();
		setArquivoMelhorPopulacao("melhorPop");
		if (tamanhoMaximoString > 15)
			tamanhoMaximoArgumento = tamanhoMaximoString;

	}

	// _________________________________________________________________
	/**
	 * Metodo usado para gerar arquivo tar com informacaes completas para cada
	 * geracao.
	 * 
	 * @throws IOException
	 */
	public void backup() throws IOException {
		/*
		 * sprintf(Comando, "tar -czf %s_GER_%0.0f.tgz %s*", funcaoATestar,
		 * geracaoAtual, diretorio); system(Comando);
		 */
		File arquivoBackup;

		arquivoBackup = new File(funcaoATestar + "_GER_" + geracaoAtual + (1)
				+ "_");

		arquivoBackup.mkdir();

		copyDirectory(diretorio, arquivoBackup);

	}

	/**
	 * Metodo usado copiar um diretorio ( na verdade faz um backup do diretorio
	 * atual, pois este vai ser sobscrito na proxima geracao
	 */
	public void copyDirectory(File sourceLocation, File targetLocation)
			throws IOException {
		if (sourceLocation.isDirectory()) {
			if (!targetLocation.exists()) {
				targetLocation.mkdir();
			}

			String[] children = sourceLocation.list();
			for (int i = 0; i < children.length; i++) {
				copyDirectory(new File(sourceLocation, children[i]), new File(
						targetLocation, children[i]));
			}
		} else {

			InputStream in = new FileInputStream(sourceLocation);
			OutputStream out = new FileOutputStream(targetLocation);

			// Copy the bits from instream to outstream
			byte[] buf = new byte[1024];
			int len;
			while ((len = in.read(buf)) > 0) {
				out.write(buf, 0, len);
			}
			in.close();
			out.close();
		}
	}

	// _________________________________________________________________
	/**
	 * Metodo usado para gerar informacaes do progresso do framework ( geracao,
	 * cobertura ).
	 * 
	 * @throws IOException
	 */
	public void status() throws IOException {

		System.out.printf("\n###########################################");
		System.out.printf("\nGERACAO: <%f>   COBERTURA: <%f>", geracaoAtual,
				coberturaAtual);

		if (arquivoResumo == null) {
			arquivoResumo = new File("resumo.tst");
			arquivoResumo.createNewFile();
		}

		FileWriter fw = new FileWriter(arquivoResumo.getPath(), true); // recebe
																		// um
																		// caminho
																		// de um
																		// arquivo
		BufferedWriter conexao = new BufferedWriter(fw); // da a permiss�o para
															// esse aquivo ser
															// escrito
		conexao.write("\nGERACAO:    COBERTURA: " + geracaoAtual
				+ coberturaAtual); // escreve no arquivo
		conexao.newLine();
		conexao.close();

		// arquivoResumo.close();

	}

	// _________________________________________________________________
	/** Metodo usado para apresentar o resultado da execucao do framework. */
	public void resultado() {
		long tempo = 0;
		java.text.DateFormat dfo = new java.text.SimpleDateFormat(
				"HH:mm:ss.SSS");
		dfo.setTimeZone(TimeZone.getTimeZone("UTC"));

		fimExecucao = objDiversos.getSecs();
		tempo = fimPrimeiraExecucao - inicioExecucao;
		String tempoFmt = null, tempoPrimAval = null;

		System.out.printf("\nResultado");
		System.out.printf("\nPopulacao gerada em Populacao.res");
		System.out.printf("\nCobertura Inicial: %0.2f", coberturaInicial);
		System.out.printf("\nTempo Avaliacao Inicial em segundos:",
				dfo.format(tempo));
		System.out.printf("\nMelhor Cobertura : %0.2f", melhorCobertura);
		System.out.printf("\nMelhor Geracao : %0.0f", indiceMelhorGeracao);
		System.out.printf("\nCobertura %0.0fa Populacao: %0.2f", geracaoAtual,
				coberturaAtual);

		tempo = fimExecucao - inicioExecucao;

		System.out.printf("\nTempo de execucao: %s - em segundos: %ld",
				tempoFmt, tempo);

		System.out.printf("\n\nCobertura Possivel: %0.2f\n<%s>",
				(double) objDiversos.numberOf(coberturaGlobal, 'X')
						/ quantidadeElemento, coberturaGlobal);

		System.out
				.printf("\nResultado\nCobertura Inicial: %0.2f\nTempo Avaliacao Inicial: %s  - em segundos: %ld\nMelhor Cobertura : %0.2f\nMelhor Geracao : %0.0f \nTempo de execucao : %s \nTempo em segundos : %ld",
						coberturaInicial, tempoPrimAval, tempo,
						melhorCobertura, indiceMelhorGeracao, tempoFmt, tempo);
		// objDiversos.toFile("resultado.tst", Comando);
		System.out
				.printf("\nCobertura %0.0fa Populacao: %0.2f\n\nCobertura Possivel: %0.2f\n<%s>",
						geracaoAtual, coberturaAtual,
						(double) objDiversos.numberOf(coberturaGlobal, 'X')
								/ quantidadeElemento, coberturaGlobal);
		// objDiversos.toFile("resultado.tst", Comando);

	}

	// _________________________________________________________________
	/**
	 * Metodo usado para atribuir valor a variavel de controle que identifica o
	 * tipo de string que o framework suporta.
	 */
	public void setTipoString(String valor) {
		int tam = valor.length();
		if (tam <= 0) {
			objDiversos.erro("setTipoString, erro no valor passado, tam<=0...",
					1);
		}

		tipoString = valor;
	}

	// _________________________________________________________________
	/**
	 * Metodo usado para atribuir valor a variavel de controle que possui o
	 * namero de entradas por argumentos necessario para execucao do programa em
	 * teste.
	 */
	public void setNumeroArgumentos(int valor) {
		numeroArgumentos = valor;
	}

	// _________________________________________________________________
	/**
	 * Metodo usado para atribuir valor a variavel de controle responsavel pela
	 * geracao de log de execucao do framework.
	 * 
	 * @throws IOException
	 */
	public void setGeraLog(int valor) throws IOException {
		geraLog = valor;
		File file = new File("log_erro.log");
		file.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * Metodo usado para atribuir valor a variavel de controle responsavel por
	 * pausa ao fim de cada geracao.
	 */
	public void setPausaGeracao(int valor) {
		pausaGeracao = valor;

	}

	// _________________________________________________________________
	/**
	 * Metodo usado para atribuir valor a variavel responsavel pela quantidade
	 * de indivaduos gerados por elitismo.
	 */
	public void setQuantidadeElitismo(double valor) {
		quantidadeElitismo = valor;

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setQuantidadeIneditismo(double valor) {
		quantidadeIneditismo = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setQuantidadeFitness(double valor) {
		quantidadeFitness = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setDiretorio(String valor) {

		diretorio = new File(valor);

		diretorio.mkdir();

		pegaDiretorio = diretorio.getPath() + "/"; // pega o diretario e adicona

	}

	// _________________________________________________________________
	/** No descriptions */

	public void setArquivoPopulacaoInicial(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoPopulacaoInicial, erro no valor passado, tam<=0...",
							1);
		arquivoPopulacaoInicial = new File(valor);

		arquivoPopulacaoInicial.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoPopulacao(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoPopulacao, erro no valor passado, tam<=0...", 1);
		arquivoPopulacao = new File((pegaDiretorio + valor + ".pop"));
		arquivoPopulacao.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoPopulacaoTemporario(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoPopulacaoTemporario, erro no valor passado, tam<=0...",
							1);

		arquivoPopulacaoTemporario = new File(pegaDiretorio + valor + ".tmp");
		arquivoPopulacaoTemporario.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoFitness(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoFitness, erro no valor passado, tam<=0...", 1);

		arquivoFitness = new File(pegaDiretorio + valor + ".fit");
		arquivoFitness.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoIneditismo(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoIneditismo, erro no valor passado, tam<=0...",
							1);

		arquivoIneditismo = new File(pegaDiretorio + valor + ".ine");
		arquivoIneditismo.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoBonusIneditismo(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivobonusIneditismo, erro no valor passado, tam<=0...",
							1);

		arquivoBonusIneditismo = new File(pegaDiretorio + valor + ".bon");
		arquivoBonusIneditismo.createNewFile();

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setArquivoFonte(String valor) {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoFonte, erro no valor passado, tam<=0...", 1);

		arquivoFonte = valor;

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoSemelhancaIndividuos(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoSemelhancaIndividuos, erro no valor passado, tam<=0...",
							1);

		arquivoBonusIneditismo = new File(pegaDiretorio + valor + ".cov");
		arquivoBonusIneditismo.createNewFile();

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setFormatoIndividuo(String valor) {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setFormatoIndividuo, erro no valor passado, tam<=0...", 1);

		formatoIndividuo = valor;

	}

	// _________________________________________________________________
	/** No descriptions */

	// public void geraLinhaPerda() {
	// if (geraLog == 1)
	// objDiversos.toFile("log_erro.log", "------geraLinhaPerda");
	//
	//
	// linhaPerda.replace(linhaPerda.charAt((int)quantidadeElemento),'\0');
	// for (int j = 0; j < quantidadeElemento; j++) {
	// if ((linhaCoberturaAnterior.charAt(j)== 'X')
	// && (linhaCoberturaAtual.charAt(j) != 'X'))
	// linhaPerda.replace(linhaPerda.charAt((int)linhaPerda + j),'P');
	// //(linhaPerda + j) = 'P';
	// }
	//
	// }

	// _________________________________________________________________

	public void setFuncaoATestar(String valor) {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setFuncaoATestar, erro no valor passado, tam<=0...", 1);
		funcaoATestar = valor;
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoVariacaoFitness(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoVariacaoFitness, erro no valor passado, tam<=0...",
							1);

		arquivoVariacaoFitness = new File(pegaDiretorio + valor + ".vfi");
		arquivoVariacaoFitness.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoCoberturaElemento(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoCoberturaElemento, erro no valor passado, tam<=0...",
							1);

		arquivoCoberturaElemento = new File(pegaDiretorio + valor + ".cov");
		arquivoCoberturaElemento.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoCoberturaIndividuo(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoCoberturaIndividuo, erro no valor passado, tam<=0...",
							1);

		arquivoCoberturaIndividuo = new File(pegaDiretorio + valor + ".cov");
		arquivoCoberturaIndividuo.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoRepositorio(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoRepositorio, erro no valor passado, tam<=0...",
					1);

		arquivoRepositorio = new File(valor + ".dep");
		arquivoRepositorio.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoAvalCobIndividuos(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoAvalCobIndividuos, erro no valor passado, tam<=0...",
							1);

		arquivoAvalCobIndividuos = new File(pegaDiretorio + valor + ".cov");
		arquivoAvalCobIndividuos.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoObsCobertura(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoObsCobertura, erro no valor passado, tam<=0...",
					1);

		arquivoObsCobertura = new File(valor + ".tst");
		arquivoObsCobertura.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoMelhorPopulacao(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setArquivoMelhorPopulacao, erro no valor passado, tam<=0...",
							1);

		arquivoMelhorPopulacao = new File(valor + ".pop");
		arquivoMelhorPopulacao.createNewFile();
	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoTabu(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoTabu, erro no valor passado, tam<=0...", 1);

		arquivoTabu = new File(valor + ".pop");
		arquivoTabu.createNewFile();

	}

	// _________________________________________________________________
	/**
	 * No descriptions
	 * 
	 * @throws IOException
	 */
	public void setArquivoTabuAux(String valor) throws IOException {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro(
					"setArquivoTabuAux, erro no valor passado, tam<=0...", 1);

		arquivoTabuAux = new File(valor + ".pop");
		arquivoTabuAux.createNewFile();

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setTamanhoString(String valor) {

		String quebra[];
		quebra = valor.split("/");
		tamanhoMinimoString = Integer.parseInt(quebra[0].trim());
		tamanhoMaximoString = Integer.parseInt(quebra[1].trim());

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setTamanhoPopulacao(double valor) {
		tamanhoPopulacao = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setMaximoGeracoes(double valor) {
		maximoGeracoes = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setCoberturaCriterio(double valor) {
		coberturaCriterio = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setCriterioTeste(String valor) {
		if (valor.length() <= 0)
			objDiversos.erro(
					"setCriterioTeste, erro no valor passado, tam<=0...", 1);

		criterioTeste = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setTaxaMutacao(double valor) {
		taxaMutacao = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setTaxaCrossover(double valor) {
		taxaCrossover = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setVariacaoInteiro(String valor) {
		String quebra[];
		quebra = valor.split("/");
		tamanhoMinimoInteiro = Integer.parseInt(quebra[0].trim());
		tamanhoMaximoInteiro = Integer.parseInt(quebra[1].trim());
		variacaoInteiro = tamanhoMaximoInteiro - tamanhoMinimoInteiro;

		/*
		 * System.out.println("\ntamanhoMinimoInteiro: " + tamanhoMinimoInteiro
		 * + "\ntamanhoMaximoInteiro:" + tamanhoMaximoInteiro +
		 * "\nvariacaoInteiro: " + variacaoInteiro);
		 */
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setMelhorCobertura(double valor) {
		melhorCobertura = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setIndiceMelhorGeracao(double valor) {
		indiceMelhorGeracao = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setTamanhoIndividuo() {
		int tam = formatoIndividuo.length();
		for (int pos = 0; pos < tam; pos++)
			tamanhoIndividuo += tamanhoTipo(pos);
	}

	// _________________________________________________________________
	/** No descriptions */
	public int tamanhoTipo(int pos) {
		switch (formatoIndividuo.charAt(pos)) {
		case 'I':
			return 6;
		case 'D':
			return 10;
		case 'F':
			return 9;
		case 'S':
			return (int) tamanhoMaximoString;
		case 'C':
			return 1;
		}
		return 0; // zero nao influencia no tamanho do outros tipos.
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setQuantidadeElemento(double valor) {
		quantidadeElemento = valor;

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setCoberturaAtual(double valor) {
		coberturaAtual = valor;
		if (geracaoAtual == 0)
			coberturaInicial = valor;

	}

	// _________________________________________________________________
	/** No descriptions */
	public void setSomatoriaFitness(double valor) {
		somatoriaFitness = valor;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void setCriterioTesteValiMPI(String valor) {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos
					.erro("setCriterioTesteValiMPI, erro no valor passado, tam<=0...",
							1);

		criterioTesteValiMPI = valor;

	}

	// _________________________________________________________________
	/** No descriptions */
	public int inicioTipo(int pos) {
		int res = 0;
		for (int i = 0; i != pos; i++)
			res += tamanhoTipo(i);
		return res;
	}

	// _________________________________________________________________
	/***
	 * Metodo usado para verificar se o framework deve encerrar execucao ou por
	 * ter alcanaado a cobertura desejada ou por alcanaar limite de geracaes.
	 */
	public boolean paraTeste() {
		if (geracaoAtual == (maximoGeracoes + 1))
			return true;
		if (coberturaCriterio != -1) {
			double x = objDiversos.numberOf(coberturaGlobal, 'X')
					* (100 / quantidadeElemento);
			if (x >= coberturaCriterio * 100)
				return true;
		}
		return false;
	}

	// _________________________________________________________________
	/** Metodo para calculo do madulo entre dois doubles. */
	public double modulo(double a, double b) {
		if (a < 0)
			a *= -1;
		if (b < 0)
			b *= -1;
		for (; a >= b; a -= b)
			;
		return a;
	}

	// _________________________________________________________________
	/**
	 * Metodo para geracao aleataria de um double, simulacao de sorteio.
	 */
	public double geraSorteio(double maximo) {
		/**/
		int num1 = (int) Math.random() * 100;
		return modulo(num1, maximo);

	}

	// _________________________________________________________________
	/**
	 * Metodo para avaliar a cobertura de cada indivaduo na populacao do AG.
	 */
	public void avaliacaoCobertura() throws IOException {

		if (geraLog == 1) {
			objDiversos.toFile("log_erro.log", "---avaliacaoCobertura");
		}

		String linha1 = null, linha = null;
		if (arquivoObsCobertura == null) {
			objDiversos.erro("avaliacaoCobertura: erro abrir arquivo :", 1);
		}
		FileReader arq = new FileReader(arquivoObsCobertura);
		BufferedReader lerArq = new BufferedReader(arq);

		linha = lerArq.readLine();
		for (int i = 0; (linha != null); i++) {
			System.out.printf("\n cont: %d, <%s>", i, linha);
			linha.trim();

			// pprova("PTO 2 ---avaliacaoCobertura");

			if (linha != "") {

				for (int j = 0; j < quantidadeElemento; j++) {
					if (linha.charAt(j) != linha1.charAt(j))
						if (linha.charAt(j) == 'X')
							linha.replace(linha.charAt(j), 'N');
						else if (i != 0)
							linha.replace(linha.charAt(j), 'p');
				}
				linha1 = linha;
				objDiversos.escreverArquivo("avalCoberturas.tst", linha);
			}
		}

		arq.close();
	}

	// _________________________________________________________________
	/** No descriptions */
	public void atualizaLinhaCoberturas(String novaCobertura) {

		if (novaCobertura.length() != quantidadeElemento)
			objDiversos
					.erro("atualizaLinhaCoberturas, erro no tamanho do valor passado, tam != quantidadeElemento...",
							1);

		if (linhaCoberturaAtual == null)
			objDiversos
					.erro("atualizaLinhaCoberturas, erro linhaCoberturaAtual == null...",
							1);

		if (linhaCoberturaAnterior == null)
			objDiversos
					.erro("atualizaLinhaCoberturas, erro linhaCoberturaAnterior == null...",
							1);

		setLinhaCoberturaAnterior(linhaCoberturaAtual);
		setLinhaCoberturaAnterior(linhaCoberturaAtual);
		setLinhaCoberturaAtual(novaCobertura);
		// setCoberturaAtual(0);
	}

	// _________________________________________________________________
	/**
	 * Metodo usado para verificar se um determinado individuo ja foi executado
	 * anteriormente, caso positivo, copia o desempenho armazenado no
	 * repositorio para a variavel desempenho.
	 */
	public String inRepositorio(String strIndiv, String desempenho)
			throws IOException {

		String linha = "";
		FileReader arq = new FileReader(arquivoRepositorio);
		BufferedReader lerArq = new BufferedReader(arq);

		linha = lerArq.readLine();
		while (linha != null) {
			if (linha.equals(strIndiv)) {
				desempenho = linha;
			}

		}

		lerArq.close();
		return desempenho;
	}

	// _________________________________________________________________
	/** No descriptions */
	public void atualizaPerda(String desempenho) {
		int indice = -1;
		String mostrar = "";
		while ((indice = objDiversos.indexOf(linhaPerda, 'P')) > 0) {
			if (desempenho.charAt(indice) == 'X')
				// linhaPerda.charAt('-') = '-';
				mostrar = linhaPerda.replace(linhaPerda.charAt(indice),
						linhaPerda.charAt('-'));
			linhaPerda = mostrar;
		}

	}

	// _________________________________________________________________
	/** No descriptions */
	public void manutencaoMelhorGeracao() {
		if (coberturaAtual > melhorCobertura) {
			setMelhorCobertura(coberturaAtual);
			setIndiceMelhorGeracao(geracaoAtual);
			arquivoMelhorPopulacao = arquivoPopulacao;
		}

	}

	// _________________________________________________________________
	/**
	 * Metodo para atribuir valores para variavel de controle correctPath, com
	 * recolocacao de memoria se necessario.
	 */
	public void setEnviroment(String valor) {
		int tam = valor.length();
		if (tam <= 0)
			objDiversos.erro("setEnviroment, erro no valor passado, tam<=0...",
					1);
		enviroment = valor;
	}

	/**
	 * Metodo usado para recalcular a quantidade de individuos gerados por
	 * elitismo, selecao e ineditismo.
	 */
	public void recalculaPorcEvolucao() {
		double total = (quantidadeElitismo + quantidadeIneditismo + quantidadeFitness);
		quantidadeElitismo = (int) (quantidadeElitismo * tamanhoPopulacao / total);
		quantidadeIneditismo = (int) (quantidadeIneditismo * tamanhoPopulacao / total);
		quantidadeFitness = tamanhoPopulacao
				- (quantidadeElitismo + quantidadeIneditismo);

	}

	/**
	 * Metodo usado para atribuir valor para variavel de controle
	 * linhaCoberturaAnterior
	 */
	public void setLinhaCoberturaAnterior(String valor) {
		int tam = valor.length();
		valor.length();
		if (tam <= 0) {
			objDiversos
					.erro("setLinhaCoberturaAnterior, erro no valor passado, tam<=0...",
							1);
		}
		linhaCoberturaAnterior = valor;

	}

	/**
	 * Metodo usado para atribuir valor para variavel de controle
	 * linhaCoberturaAtual.
	 */
	public void setLinhaCoberturaAtual(String valor) {
		int tam = valor.length();
		if (tam <= 0) {
			objDiversos.erro(
					"setLinhaCoberturaAtual, erro no valor passado, tam<=0...",
					1);
		}

		linhaCoberturaAtual = valor;

	}

	/** Metodo usado para configurar o valor de ativaTabu. */
	public void setAtivaTabu(int valor) {
		ativaTabu = valor;
	}

	/** Metodo usado para configurar o atributo geracoesComRepositorio. */
	public void setGeracoesComRepositorio(int valor) {
		geracoesComRepositorio = valor;
	}

	/** Atualiza a coberturaGlobal com a cobertura passada por argumento. */
	public void atualizaCoberturaGlobal(String novaCobertura) {
		int tam = (int) quantidadeElemento;
		if (novaCobertura.length() != tam) {

			objDiversos
					.erro("central:atualizaCoberturaGlobal - Tamanho da novaCobertura  incorreto",
							1);
		}
		if (coberturaGlobal.length() != tam) {

			objDiversos
					.erro("central:atualizaCoberturaGlobal - Tamanho da coberturaAtual ( %d) incorreto",
							1);
		}

		for (int i = 0; i < tam; i++)
			if ((novaCobertura + i).equals('X')) {
				// coberturaGlobal.replace(coberturaGlobal + i), 'X');
			}

	}

	/** Metodo que configura o final da primeira execucao. */
	public void setFimPrimeiraExecucao() {
		fimPrimeiraExecucao = objDiversos.getSecs();
	}

	/** Metodo que seta o namero de processos. */
	public void setNProcess(String n) {
		nProcess = n;
	}

	/** Metodo que seta o argumento de funcoes necessario para ValiMPI. */
	public void setFuncoes(String valor) {
		int tam = valor.length();

		if (tam <= 0)
			objDiversos.erro("Nao pode alocar para Funcoes", 1);

		try {

			funcoes = valor;
			funcoes.charAt('\0');
		} catch (Exception E) {
			objDiversos.erro("Erro ao setar funcoes. Provavel estouro", 1);
		}

	}

	public void setCCArgs(String valor) {
		int tam = valor.length();

		if (tam <= 0)
			objDiversos.erro("Nao pode alocar para CCArgs", 1);

		try {

			ccargs = valor;
			ccargs.charAt('\0');
		} catch (Exception E) {
			objDiversos.erro("Erro ao setar ccargs. Provavel estouro", 1);
		}

	}
}
