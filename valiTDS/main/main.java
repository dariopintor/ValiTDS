package main;

import java.io.IOException;

import algoritmoGenetico.Individuo;
import algoritmoGenetico.Populacao;
import ferramenta.Central;
import ferramenta.Ferramenta;


public class main {
	
	/***************************************************************************
	 * * This program is free software; you can redistribute it and/or modify *
	 * it under the terms of the GNU General Public License as published by *
	 * the Free Software Foundation; either version 2 of the License, or * (at
	 * your option) any later version. * *
	 ***************************************************************************/

	 /*
	 * #ifdef HAVE_CONFIG_H #include <config.h> #endif
	 * 
	 * #include <stdlib.h> #include <iostream> #include <stdlib.h> #include
	 * <stdio.h> #include <string.h> #include "diversos.h" #include "central.h"
	 * #include "ferramenta.h" #include "populacao.h" #include <time.h>
	 */

	static Diversos objDiversos; // declara��o do objeto diversos
	static Mersenne objMersenne;
	static Central objCentral;
	static Populacao objPopulacao;
	static Individuo objInviduo;
	static Ferramenta objFerramenta;
	
	public static void main(String[] args) throws IOException {

		

		objDiversos = new Diversos(); // instacia��o do objeto da classe //
										// diversos
		objMersenne = new Mersenne();
		objCentral = new Central();
		objInviduo = new Individuo();
		objFerramenta = new Ferramenta();
		objPopulacao = new Populacao();

		long inic = 0, fim = 0;
		inic = objDiversos.getSecs();
		// objMersenne.initGenRand();
		System.out.print("Iniciando a Execucao da Ferramenta");
		objCentral.interpretaArquivoConfiguracao();
		//objCentral.prepareExecution();

		objFerramenta.prepareTool();
		objCentral.setQuantidadeElemento(objFerramenta.obtemElementosRequeridos());

		objPopulacao.geraPopulacaoInicial();
		objPopulacao.avaliaPopulacao();
		objCentral.backup();
		objCentral.status();
		objCentral.setFimPrimeiraExecucao();

		for (objCentral.geracaoAtual = 1; !objCentral.paraTeste(); objCentral.geracaoAtual++) {
			objPopulacao.evoluiPopulacao();
			objPopulacao.avaliaPopulacao();
			objCentral.backup();
			objCentral.manutencaoMelhorGeracao();

			objCentral.status();
		}// fim for
		fim = objDiversos.getSecs();
		System.out.print(" \nFim do processo de evolucao...");
		objCentral.resultado();
		if (objCentral.geracaoAtual > 1)
			objPopulacao.decodificaPopulacao(objCentral.arquivoMelhorPopulacao,
					"Populacao.res");
		if (objCentral.ativaTabu==1)
			objPopulacao
					.decodificaPopulacao(objCentral.arquivoTabu, "Tabu.res");

		System.out.print("\nFim de execu��o...\n");

	}
}
