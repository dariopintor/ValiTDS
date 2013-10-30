package algoritmoGenetico;

public interface populacao {
	/***************************************************************************
	 * populacao.h - description ------------------- begin : Dom Jul 6 2003
	 * copyright : (C) 2003 by Luciano Petinati Ferreira email :
	 * petinat@inf.ufpr.br
	 ***************************************************************************/

	/***************************************************************************
	 * * This program is free software; you can redistribute it and/or modify *
	 * it under the terms of the GNU General Public License as published by *
	 * the Free Software Foundation; either version 2 of the License, or * (at
	 * your option) any later version. * *
	 ***************************************************************************/

	/**
	 * @author Luciano Petinati Ferreira
	 * 
	 *         //#include "diversos.h" //#include "central.h" //#include
	 *         "individuo.h" //#include "ferramenta.h" //#include "tabu.h"
	 */

	/** No descriptions */

	/**
	 * Método usado para gerar população inicial para o AG. Cria a população
	 * inicial aleatória, com base nas configurações fornecidas ou Cria a
	 * população inicial baseado em um arquivo fornecido.
	 */
	int geraPopulacaoInicial();

	/** Cria a população inicial baseado em arquivo fornecido. */
	int geraPopulacaoInicialArquivo();

	/**
	 * Cria a população inicial aleatória, com base nas configurações fornecidas
	 */
	int geraPopulacaoInicialAleatoria();

	/**
	 * Método usado para verificar se um individuo está na população
	 * representada pelo arquivo passado por argumento.
	 */
	int inPopulacao(String strIndividuo, String arquivo);

	/**
	 * Método usado para incluir um novo indivíduo no arquivo de população. Caso
	 * o indivíduo já exista na população a inserção não será realizada.
	 */
	int toPopulacao(int nro, String strIndividuo, String arquivo);

	/**
	 * Método usado para avaliar a população do AG. Cada individuo é executado e
	 * o fitness é calculado com base no número de elementos requeridos
	 * satisfeitos pela execução do mesmo.
	 */
	int avaliaPopulacao();

	/** Método usado para gerar a cobertura dos indivíduos da população. */
	int geraCoberturaIndividuo();

	/**
	 * Método usado para gerar a cobertura dos indivíduos da população com base
	 * em arquivos gerados pela utilização da ferramenta ValiMPI.
	 */
	int geraCoberturaIndividuoValiMPI();

	/**
	 * Método usado para gerar a cobertura dos indivíduos da população com base
	 * em arquivos gerados pela utilização da ferramenta Proteum.
	 */
	int geraCoberturaIndividuoProteum();

	/**
	 * Método usado para armazenar desempenho de um indivíduo, assim não precisa
	 * executa-lo novamente para obter sua cobertura.
	 */
	int toRepositorio(int nro, String desempenho);

	/** Método usado para sobrepor duas linhas de coberturas. */
	int sobrepoe(String cobertura, String desempenho);

	/** Método que evolui a população de indivíduos. */
	int evoluiPopulacao();

	/**
	 * Método usado para evoluir a população com base no fitness dos indivíduos.
	 */
	int evolucaoPorFitness();

	/**
	 * Método retorna o índice do indivíduo sorteado. Com base na somatória do
	 * fitness e na ordem dos indivíduos, simulando o método de seleção da
	 * roleta. Retorna qual o indivíduo possui está na faixa sorteada.
	 */
	int indiceIndividuoSorteado(double sorteio);

	/** Método usado para aplicar mutação em um indivíduo. */
	int mutacao(String indiv);

	/**
	 * Método que aplica operador crossover nos indivíduos representados por
	 * indiv1 e indiv2
	 */
	int crossover(String indiv1, String indiv2);

	/** Método usado para gerar o fitness da população */
	int geraFitness();

	/** Método usado para realizar evolução por elitismo. */
	int evolucaoPorElitismo();

	/** Metodo usado para obter o indice do individuo a ser mantido */
	double melhorInedAntNaoEm(String arquivoAuxiliar);

	/** Metodo usado para obter o indice do individuo a ser mantido */
	double melhorFitAntNaoEm(String arquivoAuxiliar);

	/** Método usado para calcular o ineditismo da população. */
	int geraBonusIneditismo();

	/**
	 * Método usado para calcular a cobertura dos elementos, com base na
	 * cobertura dos indivíduos.
	 */
	int geraCoberturaElementos();

	/**
	 * Método usado para evoluir população com base no índice de ineditismo do
	 * indivíduo.
	 */
	int evolucaoPorIneditismo();

	/**
	 * Método usado para gerar um arquivo que reflita os dados de uma população
	 * de forma entendível/decodificada.
	 */
	int decodificaPopulacao(String origem, String destino);

	/**
	 * Este método é usado para limpar e regerar o diretório de pool e seus
	 * arquivos. Os arquivos são gerados para serem importados e executados para
	 * serem avaliados
	 */
	int geraPool();

	/**
	 * Este método retorna o valor do bonus para os indivíduos que cobriram o
	 * elemento informado por pos.
	 */
	double getBonusElemento(int pos);

	/** Gera o arquivo com a bonificação final por ineditismo. */
	int geraIneditismoPopulacao();
	// public: // Public attributes
	/**
	 * Ponteiro para objeto tipo central, e serve para controlar a execução do
	 * framework.
	 */
	// central ** ctl;
	// };

}
