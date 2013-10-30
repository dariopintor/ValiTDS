/***************************************************************************
                          central.h  -  description
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
#include "diversos.h"
#ifndef CENTRAL_H
#define CENTRAL_H

#define TDS_PATH "/home/asano/IC/ValiPAR/vali_tds/tdsgen/"


/**Classe de controle. Interpreta arquivo de configuração obtendo informações sobre execução.
  *@author Luciano Petinati Ferreira
  */
//#include"diversos.h"
#include"l_string.h"

class central {
public:
	central();
	~central();
  /** Metodo que mostra na tela o valor de todas as variáveis de controle da classe central. */
  void printAll();

  /** No descriptions */
  int setMelhorCobertura(double valor);
  /** No descriptions */
  int setIndiceMelhorGeracao(int valor);
  /** No descriptions */
  int geraLinhaPerda ();
  /** No descriptions */
  int alocaLinhaPerda ();
  /** No descriptions */
  int alocaLinhaCoberturaAtual ();
  /** No descriptions */
  int alocaCoberturaGlobal ();
  /** No descriptions */
  int alocaLinhaCoberturaAnterior ();
  /** Método para cálculo do módulo entre dois doubles. */
  double modulo(double a, double b);
  /** Método para geração aleatória de um double, simulação de sorteio. */
  double geraSorteio(double maximo);
  /** Método para avaliar a cobertura de cada indivíduo na população do AG. */
  int avaliacaoCobertura();
  /** No descriptions */
  int atualizaLinhaCoberturas(char * novaCobertura);
  /** No descriptions */
  int inRepositorio(char * strIndiv, char ** desempenho);
  /** No descriptions */
  int atualizaPerda(char * desempenho);
  /** No descriptions */
  int manutencaoMelhorGeracao();
  /** Metodo que carrega na classe central informações sobre a execução da ferramenta. */
  int interpretaArquivoConfiguracao();
  /** Método usado para gerar arquivo tar com informações completas para cada geração. */
  void backup();
  /** Método usado para gerar informações do progresso do framework ( geração, cobertura ). */
  void status();
  /** Método usado para apresentar o resultado da execução do framework. */
  void resultado();
  /** Método usado para atribuir valor à variável de controle responsável por pausa ao fim de cada geração. */
  int setPausaGeracao (int valor);
  /** Método usado para atribuir valor à variável de controle responsável pela geração de log de execução do framework. */
  int setGeraLog (int valor);
  /** Método usado para atribuir valor à variável de controle que possui o número de entradas por argumentos necessário para execução do programa em teste. */
  int setNumeroArgumentos (int valor);
  /** Método usado para atribuir valor a variável de controle que identifica o tipo de string que o framework suporta. */
  int setTipoString(char * valor);
  /** No descriptions */
  int setQuantidadeFitness (double valor);
  /** No descriptions */
  int setQuantidadeIneditismo(double valor);
  /** Método usado para atribuir valor à variável responsável pela quantidade de indivíduos gerados por elitismo. */
  int setQuantidadeElitismo (double valor);
  /** No descriptions */
  int setArquivoBonusIneditismo (char * valor);
  /** No descriptions */
  int setArquivoIneditismo (char * valor);
  /** No descriptions */
  int setArquivoFitness (char * valor);
  /** No descriptions */
  int setArquivoPopulacaoTemporario (char * valor);
  /** No descriptions */
  int setArquivoPopulacao (char * valor);
  /** No descriptions */
  int setArquivoPopulacaoInicial (char * valor);
  /** No descriptions */
  int setDiretorioPool (char * valor);
  /** No descriptions */
  int setDiretorio (char * valor);
  /** No descriptions */
  int setFormatoIndividuo (char * valor);
  /** No descriptions */
  int setArquivoFonte (char * valor);
  /** No descriptions */
  int setArquivoSemelhancaIndividuos (char * valor);
  /** No descriptions */
  int setArquivoCoberturaIndividuo (char * valor);
  /** No descriptions */
  int setArquivoCoberturaElemento (char * valor);
  /** No descriptions */
  int setArquivoVariacaoFitness (char * valor);
  /** No descriptions */
  int setFuncaoATestar (char * valor);
  /** No descriptions */
  int setArquivoRepositorio (char * valor);
  /** No descriptions */
  int setArquivoAvalCobIndividuos (char * valor);
  /** No descriptions */
  int setArquivoObsCobertura (char * valor);
  /** No descriptions */
  int setArquivoMelhorPopulacao (char * valor);
  /** No descriptions */
  int setArquivoTabu (char * valor);
  /** No descriptions */
  int setArquivoTabuAux (char * valor);
  /** No descriptions */
  int setCoberturaCriterio (double valor);
  /** No descriptions */
  int setMaximoGeracoes (double valor);
  /** No descriptions */
  int setTamanhoPopulacao (double valor);
  /** No descriptions */
  int setTamanhoString (char * valor);
  /** No descriptions */
  int setCriterioTeste (char * valor);
  /** No descriptions */
  int setTamanhoIndividuo ();
  /** No descriptions */
  int setVariacaoInteiro (char * valor);
  /** No descriptions */
  int setTaxaCrossover (double valor);
  /** No descriptions */
  int setTaxaMutacao (double valor);
  /** No descriptions */
  int tamanhoTipo(int pos);
  /** No descriptions */
  int setCriterioTesteValiMPI (char * valor);
  /** No descriptions */
  int setSomatoriaFitness ( double valor );
  /** No descriptions */
  int setCoberturaAtual (double valor);
  /** No descriptions */
  int setQuantidadeElemento (double valor);
  /** No descriptions */
  int inicioTipo (int pos);
  /** Método usado para verificar se o framework deve encerrar execução ou por ter alcançado a cobertura desejada ou por alcançar limite de gerações. */
  int paraTeste();
  /** Método usado para iniciar a execução da ferramenta.
  Apagar diretórios e arquivos que possam ter sidos gerados por execuções anteriores. */
  int prepareExecution();
  /** Método para atribuir valores para variável de controle comandPath, com realocação de memória se necessário. */
  int setComandPath (char * valor);
  /** No descriptions */
  int setEnviroment(char * valor);
  /** Método usado para recalcular a quantidade de individuos gerados por elitismo, seleção e ineditismo. */
  int recalculaPorcEvolucao();
  /** Método usado para atribuir valor para variável de controle linhaCoberturaAnterior */
  int setLinhaCoberturaAnterior( char * valor );
  /** Método usado para atribuir valor para variável de controle linhaCoberturaAtual. */
  int setLinhaCoberturaAtual (char * valor);
  /** Método usado para configurar o valor de ativaTabu. */
  int setAtivaTabu(int valor);
  /** Método usado para configurar o atributo geracoesComRepositorio. */
  int setGeracoesComRepositorio(double valor);
  /** Atualiza a coberturaGlobal com a cobertura passada por argumento. */
  int atualizaCoberturaGlobal( char * novaCobertura );
  /** Método que configura o final da primeira execução. */
  int setFimPrimeiraExecucao();

	int setNProcess(int);
	int setFuncoes(char *);
	int setCCArgs(char *);

public: // Public attributes
  /** Variavel de controle para pausar a execucao a cada geracao. */
  int pausaGeracao;
  /** Variavel de controle para gerar log da execucao. */
  int geraLog;
  /** Variavel de controle para indicar quantos argumentos o programa em teste necessita */
  int numeroArgumentos;
  /** Variavel de controle para indicar o tamanho mínimo para o tipo string ( char * ). */
  double tamanhoMinimoString;
  /** Variavel de controle para indicar o tamanho máximo para o tipo string ( char * ). */
  double tamanhoMaximoString;
  /** Variavel de controle para indicar o tamanho mínimo para o tipo inteiro. */
  int tamanhoMinimoInteiro;
  /** Variavel de controle para indicar o tamanho máximo para o tipo inteiro. */
  int tamanhoMaximoInteiro;
  /** Variavel de controle para indicar o tamanho máximo que um argumento pode assumir para o programa em teste, desconsiderando seu tipo. */
  double tamanhoMaximoArgumento;
  /** Variavel de controle para indicar a variação do tipo inteiro. */
  int variacaoInteiro;
  /** Variavel de controle para indicar a quantidade de elementos requeridos para o programa em teste. */
  double quantidadeElemento;
  /** Variavel de controle para conter a cobertura de elementos requeridos da população atual. */
  double coberturaAtual;
  /** Variavel de controle para conter a somatória do fitness de todos os indivíduos para auxiliar a seleção por roleta. */
  double somatoriaFitness;
  /** Variavel de controle para indicar o critério de teste a ser usado na execução do framework. */
  char * criterioTeste;
  /** Variavel de controle para indicar a função a ser testada do programa em teste. */
  char * funcaoATestar;
  /** Variavel de controle para indicar o critério de teste da valiMPI a ser usado na execução do framework. */
  char * criterioTesteValiMPI;
  /**  */
  char * diretorio;
  /** Variavel de controle para indicar o diretório pool, usado para entrada de dados na execução do programa já instrumentado. */
  char * diretorioPool;
  /** Variavel de controle para indicar o número máximo de gerações a serem geradas caso a cobertura desejada não seja alcançada. */
  double maximoGeracoes;
  /** Variavel de controle para indicar a geração atual. */
  double geracaoAtual;
  /** Variável de controle para indicar o índice da melhor geração. */
  double indiceMelhorGeracao;
  /** Variável de controle para indicar o tamanho do indivíduo usado no AG. */
  double tamanhoIndividuo;
  /** Variável de controle para indicar o tamanho da população usada no AG. */
  double tamanhoPopulacao;
  /** Variável de controle para indicar a cobertura desejada para o critério selecionado. */
  double coberturaCriterio;     //novo nome coberturaDesejada
  /** Variável de controle para indicar a melhor cobertura possível através de todo o processo. Usa informações da lista Tabu. */
  double melhorCobertura;
  /** Variável de controle para indicar a taxa de mutação usada no AG. */
  double taxaMutacao;
  /** Variável de controle para indicar a taxa de Crossover usada no AG */
  double taxaCrossover;
  /** Variável de controle para indicar a quantidade de indivíduos da nova geração que devem ser gerados com base no elitismo (fitness). */
  double quantidadeElitismo;
  /** Variável de controle para indicar a quantidade de indivíduos da nova geração que devem ser gerados com base no score de ineditismo dos indivíduos. */
  double quantidadeIneditismo;
  /** Variável de controle para indicar a quantidade de indivíduos da nova geração que devem ser gerados com base na seleção e operadores genéticos. */
  double quantidadeFitness;        //novo nome quantidadeSelecao
  /** Variável de controle para indicar o formato da entrada do programa, consequentemente o formato do indivíduo do AG. */
  char * formatoIndividuo;
  /** Variável de controle para conter informações sobre perda de cobertura de elementos requeridos. */
  char * linhaPerda;
  /** Variável de controle para conter a cobertura atual de elementos requeridos ( X: para coberto, -: para não coberto ). */
  char * linhaCoberturaAtual;
  /** Variável de controle para conter informações de cobertura de elementos requeridos da geração anterior. */
  char * linhaCoberturaAnterior;
  /** Variável de controle para conter informações a cobertura global de elementos requeridos, independente de geração. */
  char * coberturaGlobal;         // novo nome linhaCoberturaGlobal
  /** Variável de controle para conter o nome do arquivo da lista Tabu. */
  char * arquivoTabu;
  /** Variável de controle para conter o nome do arquivo temporário da lista Tabu. */
  char * arquivoTabuAux;
  /** Variável de controle para conter o nome do arquivo fonte do programa em teste. */
  char * arquivoFonte;
    /** Variável de controle que identifica o tipo de string que o framework suporta. */
  char * tipoString;
  /**  Variável de controle que conterá o comando a ser executado por chamada system com
  variável de ambiente PATH corretamente configurada. */
  char * comandPath;
  /** Variável de controle que conterá o PATH correto baseado na ferramenta de teste a ser usada. */
  //char * enviroment;
  l_string enviroment;

  /** Atributos sem comentários...*/
  char    * arquivoPopulacaoInicial;
  char    * arquivoPopulacao;
  char    * arquivoMelhorPopulacao;	
  char    * arquivoPopulacaoTemporario;
  char    * arquivoFitness;
  char    * arquivoVariacaoFitness;
  char    * arquivoCoberturaIndividuo;
  char    * arquivoCoberturaElemento;	
  char    * arquivoAvalCobIndividuos;
  char    * arquivoSemelhancaIndividuos;
  char    * arquivoObsCobertura;
  char    * arquivoRepositorio;	
  /** Variável de controle para manter o tamanho de enviroment. */
  long tamEnviroment;
  /** Variavel de controle para manter o tamanho de comandPath. */
  long tamComandPath;
  /** Atributo usado para conter o nome para um arquivo temporário para a população. */
  l_string arquivoPopulacaoTemporario2;
  /** Atributo usado para controlar a ativação do recurso de lista Tabu. */
  int ativaTabu;
  char    * arquivoBonusIneditismo;
  char    * arquivoIneditismo;
  /** Atributo usado para guardar quantas gerções serão usadas/configuradas para verificar o repositório de execução antes de executar um determinado caso de teste. Isto pode aumentar o desempenho do sistema. */
  double geracoesComRepositorio;
  /** Atributo com o tempo em segundos da execução do sistema. */
  time_t inicioExecucao;
  /** Atributo com o tempo em segundo do fim de execução do sistema */
  time_t fimExecucao;
  /** Atributo com o tempo em segundo do fim da primeira execução do sistema */
  time_t fimPrimeiraExecucao;
  /** Atributo para manter a cobertura inicial do processo. */
  double coberturaInicial;

	/** Atributo que diz quantos processos o programa usa.*/
	int nProcess;
	/** Atributo que diz qual processo será qual número*/
	char *funcoes;
	char *ccargs;

};


#endif
