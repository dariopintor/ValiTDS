package algoritmoGenetico;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.rmi.server.ObjID;
import java.util.Formattable;

import main.Mersenne;
import main.Diversos;
import ferramenta.*;

public class Individuo{
	/***************************************************************************
	 * individuo.cpp - description ------------------- begin : Dom Jul 6 2003
	 * copyright : (C) 2003 by Luciano Petinati Ferreira email :
	 * petinat@inf.ufpr.br
	 ***************************************************************************/

	/***************************************************************************
	 * * This program is free software; you can redistribute it and/or modify *
	 * it under the terms of the GNU General Public License as published by *
	 * the Free Software Foundation; either version 2 of the License, or * (at
	 * your option) any later version. * *
	 ***************************************************************************/
	/** Atributo que contem a representacao dos individuos. */
	
	public String representacao;
	Central objCentral;
	Diversos objDiversos;
	Mersenne objMersenne;

	public Individuo() {
		// cout << "\nConstruindo individuo...";
		objCentral = new Central();
		objDiversos = new Diversos();
		objMersenne = new Mersenne();
		representacao = null;

	}

	/** Metodo para criar um novo individuo aleatorio. */
	public void novo() {
		String bloco = null;
		int nroBloco = objCentral.formatoIndividuo.length();
		int blocoTam = (int) objCentral.tamanhoIndividuo;

		for (int i = 0; i < nroBloco; i++) {

			switch (objCentral.formatoIndividuo.charAt(i)) {
			case 'I': {
				forma_block_int_random(bloco, blocoTam);
				break;
			}
			case 'D': {
				forma_block_double_random(bloco, blocoTam);
				break;
			}
			case 'F': {
				forma_block_float_random(bloco, blocoTam);
				break;
			}
			case 'S': {
				forma_block_string_random(bloco, blocoTam);
				break;
			}
			case 'C': {
				// bloco.charAt(0) = generateChar( objCentral.tipoString );
				// bloco[1] = '\0';
			}
			default: {
				System.out.printf(
						"\nFormato : %c\nFormato de tipo invalido\n\r",
						objCentral.formatoIndividuo.charAt(i));
			}
			}// fim switch
			representacao = bloco;
		} // fim for

	}

	// _________________________________________________________________

	/**
	 * * Metodo para criar um novo individuo baseado na linha do arquivo e na
	 * configuracao fornecida ao framework.
	 */

	public void novo(String linha) {
		int numArgumentos = objCentral.formatoIndividuo.length();
		int virg = -1;
		String blocoLinha = null, bloco = null;
		
		for (int cont = 0; cont < numArgumentos; cont++) {
			if ((virg = objDiversos.indexOf(linha, ',')) != -1){		
				blocoLinha = linha;
			}
				else{
					blocoLinha = linha;
				}			
			linha = linha.trim() + virg + 1;
			
			switch (objCentral.formatoIndividuo.charAt(cont)) {
			case 'I': {
				forma_block_int(bloco, objCentral.tamanhoTipo(cont) + 1,
						blocoLinha);
				// printf("\nRecuperado Arg %d - Integer '%s'", cont, bloco);
				break;
			}

			case 'D': {
				forma_block_double(bloco, objCentral.tamanhoTipo(cont) + 1,
						blocoLinha);
				// printf("\nRecuperado Arg %d - Double '%s'", cont, bloco);
				break;
			}
			case 'F': {
				forma_block_float(bloco, objCentral.tamanhoTipo(cont) + 1,
						blocoLinha);
				// printf("\nRecuperado Arg %d - Float '%s'", cont, bloco);
				break;
			}
			case 'S': {
				forma_block_string(bloco, objCentral.tamanhoTipo(cont) + 1,
						blocoLinha);
				// printf("\nRecuperado Arg %d - String '%s'", cont, bloco);
				break;
			}
			case 'C': {
				bloco = blocoLinha;
				break;
			}
			}// fim switch
			representacao = bloco;
		}

	}

	/**
	 * * Metodo para recuperar o pos-esimo individuo da populacao. pos deve
	 * variar de 0 ate tamanho da populacao - 1.
	 * @throws IOException 
	 */
	public void load(int pos) throws IOException {
		int i = 0;
		String gene = null, geneAux = null;
		String saida = null, linha = null;
		
		FileReader fr = new FileReader(objCentral.arquivoPopulacao);
		BufferedReader br = new BufferedReader(fr);
		
		if (br == null) {
			 saida = String.format("aqui nao abriu o arquivo de populacao : %s", objCentral.arquivoPopulacao);
		     objDiversos.erro(saida,1);
		}
		
		if (pos >= objCentral.tamanhoPopulacao) {
			 saida = String.format("Pos, %d, extrapolou tamanho da populacao %f", pos, objCentral.tamanhoPopulacao);
			 objDiversos.erro(saida,1);
		}

		linha = br.readLine();
		for (i = 0; i <= pos; i++) {
			// cout << "\n ind nro " << i;
			if (pos == 14){
				pos += 0;
			}	
			gene = linha;
			linha = br.readLine();	
		}// fim for	
		br.close();
		
		i = objDiversos.indexOf(gene.trim(), ':') + 1;
		geneAux = gene + i;
		setRepresentacao(geneAux.trim());		
	}

	// _________________________________________________________________

	/** Metodo que atribui valor para a representacao de um individuo. */
	public void setRepresentacao(String valor) {
		int tam = valor.length();
		if (tam < 0)
			objDiversos.erro(
					"setRepresentacao, erro no valor passado, tam<0...", 1);
		if (tam > (objCentral.tamanhoIndividuo))
			objDiversos
					.erro("Novo valor p/representacao de indiv estrapolou a padrao...",
							1);
		representacao = valor;

	}

	// _________________________________________________________________

	/** Metodo que recupera o respectivo valor do bloco passado como argumento. */
	public int decode_block_int(String bloco) {

		return Integer.parseInt(bloco);
	}

	// _________________________________________________________________

	/**
	 * Metodo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	public void forma_block_int(String res, int limite, String lido) {
		int tam = 0;
		String aux=null, numero=null;
		if ((lido.charAt(0) == '-') || (lido.charAt(0) == '+')) {
			aux = aux.replace(aux.charAt(0), lido.charAt(0));
			//lido++;
		}
		
		numero = lido.trim();
		tam = numero.length();

		if (limite > (int) aux.length()){
			res = aux;
		}
			else{
				objDiversos.erro(
					"Estouro de tamanho gerando inteiro randomicamente", 1);
			}

	}

	// _________________________________________________________________

	/** Metodo usado para formatar um bloco aleatoriamente. */
	public int  forma_block_int_random(String res, int limite){
		int tam = 0;
		String aux = null,  numero = null;
		 aux = "+00000";
		 int num = 0;
		 if (objCentral.tamanhoMinimoInteiro < 0){
			 int sinal = objMersenne.genrand()*2;                    //[0+,1-]
			 	if(sinal == 1){
			 		num = ( objMersenne.genrand() % ( ( -1 * (objCentral.tamanhoMinimoInteiro ) +1 ) ));
			 		aux = aux.replace(aux.charAt(0), '-');
			 	}
			 		else //+
			 			num = (  objMersenne.genrand() % ( (objCentral.tamanhoMaximoInteiro + 1 ) ));
		 }
		 	else{
		 		num = (  objMersenne.genrand() % (int)(objCentral.variacaoInteiro) ) + objCentral.tamanhoMinimoInteiro;
		 	}
		 numero = String.format("%d", num);

		//strcpy(aux + (6-tam), numero);
		 aux = numero.trim();
		
		 if (limite >= (int) aux.length())
			 res = aux;
		 	else 
		 		objDiversos.erro("Estouro de tamanho gerando inteiro randomicamente",1);

return 1;
}// fim forma_block_int_random

	// _________________________________________________________________

	/** Metodo que recupera o respectivo valor do bloco passado como argumento. */
	public double  decode_block_double (String bloco){
		double res = 0;
		int pos_E  = -1, mant = 1;
		String mantissa = null,  numero = null;
		
		pos_E = objDiversos.indexOf(bloco.trim(), 'E');
		numero = bloco;
		if(pos_E != -1){
			numero = bloco;
			mantissa = bloco + pos_E + 1;
			mant = Integer.parseInt(mantissa);
		}// fim pos_E
		
		res = Double.parseDouble(numero);
		res *= Math.pow(10, mant );
		
		return res;
	}

	// _________________________________________________________________

	/**
	 * Metodo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	public void  forma_block_double (String res, int limite, String lido){
		int tam = 0;
		int pos_E = -1;
		String aux=  null,
				mantissa = null, 
				aux_mant = null, 
				numero = null;
		 
		aux = "+00000";
		aux_mant = "+000";
		mantissa = "000";
			
		if ( (lido.charAt(0) == '-') || (lido.charAt(0) == '+') )	{
			aux = aux.replace(aux.charAt(0), lido.charAt(0));
			//lido++;
		}
	
		pos_E = objDiversos.indexOf(lido.trim(), 'E');
		if( pos_E != -1){                                            //existe mantissa
			numero = lido;
			lido += pos_E;
			if ( (lido.charAt(0) == '-') || (lido.charAt(0) == '+') ){
				aux_mant = aux_mant.replace(aux_mant.charAt(0), lido.charAt(0));
				//lido++;
			}
		
			mantissa = lido;
		}// fim if tem E
		else numero = lido;
		
		tam = numero.length();
		//aux      + (6-tam) = numero;
		tam = mantissa.length();
		//aux_mant + (4-tam) = mantissa;
		
		aux = aux_mant;
	
		if (limite > (int) aux.length())
			res = aux;
		else
		objDiversos.erro("Estouro de tamanho recuperando double",1);
		
}// fim forma_block_double

	// _________________________________________________________________

	/** Metodo usado para formatar um bloco double aleatoriamente. */

	public void  forma_block_double_random(String res, int limite){
		int tam = 0, num = 0, mant = 0, sinal = objMersenne.genrand()%4;         //[0++,1+-,2-+,3--]
		String aux=  null, mantissa = null, aux_mant = null, numero = null;

		switch (sinal){
		case 0: {    aux = "+00000" ;   aux_mant = "+000" ; break; }
		case 1: {    aux = "+00000" ;  aux_mant = "-000" ; break; }
		case 2: {    aux = "-00000" ;   aux_mant = "+000" ; break; }
		case 3: {    aux = "-00000" ;   aux_mant = "-000" ; break; }
		} // fim switch sinal

		num  = objMersenne.genrand() * 32768;        //obtendo string numero
		numero   = String.format("%d", num);
		mant = objMersenne.genrand() * 309;          //obtendo string mantissa
		mantissa   = String.format("%d", mant);
		
		tam = numero.length();
		//aux      + (6-tam) = numero;
		tam = mantissa.length();
	//	aux_mant  + (4-tam) = mantissa;
		
		aux = aux_mant;
		
		
		if (limite > (int) aux.length())
		res = aux;
		else objDiversos.erro("Estouro de tamanho gerando double randomicamente",1);


} // fim forma_block_double_random

	// _________________________________________________________________

	/** Metodo que recupera o respectivo valor do bloco passado como argumento. */
	public double  decode_block_float ( String bloco ){
		double res = 0;
		int pos_E  = -1, mant = 1;
		String mantissa = null,  numero = null;

		pos_E = objDiversos.indexOf(bloco.trim(), 'E');
		numero = bloco;
		if(pos_E != -1)	{
			numero = bloco;
			mantissa = (bloco + pos_E + 1);
			mant = Integer.parseInt(mantissa);
		}// fim pos_E
		res = Double.parseDouble(numero);
		res *= Math.pow(10, mant );

		return res;
}

	// _________________________________________________________________

	/**
	 * Metodo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	public void   forma_block_float (String res, int limite, String lido){
		int tam = 0;
		int pos_E = -1;
		String aux=  null,
				mantissa = null, 
				aux_mant = null, 
				numero = null;
		 
		aux = "+00000";
		aux_mant = "+000";
		mantissa = "000";
			
		if ( (lido.charAt(0) == '-') || (lido.charAt(0) == '+') )	{
			aux = aux.replace(aux.charAt(0), lido.charAt(0));
			//lido++;
		}
	
		pos_E = objDiversos.indexOf(lido.trim(), 'E');
		if( pos_E != -1){                                            //existe mantissa
			numero = lido;
			lido += pos_E;
			if ( (lido.charAt(0) == '-') || (lido.charAt(0) == '+') ){
				aux_mant = aux_mant.replace(aux_mant.charAt(0), lido.charAt(0));
				//lido++;
			}
		
			mantissa = lido;
		}// fim if tem E
		else numero = lido;
		
		tam = numero.length();
		//aux      + (6-tam) = numero;
		tam = mantissa.length();
		//aux_mant + (3-tam) = mantissa;
		
		aux = aux_mant;
		
		if (limite > (int) aux.length())
		res = aux;
	else
	objDiversos.erro("Estouro de tamanho recuperando float",1);
	
}

	// _________________________________________________________________
	/** Metodo usado para formatar um bloco float aleatoriamente. */
	public void  forma_block_float_random(String res, int limite){
		int tam = 0, num = 0, mant = 0, sinal = objMersenne.genrand()%4;         //[0++,1+-,2-+,3--]
		String aux=  null, mantissa = null, aux_mant = null, numero = null;

		switch (sinal){
		case 0: {    aux = "+00000" ;   aux_mant = "+00" ; break; }
		case 1: {    aux = "+00000" ;  aux_mant = "-00" ; break; }
		case 2: {    aux = "-00000" ;   aux_mant = "+00" ; break; }
		case 3: {    aux = "-00000" ;   aux_mant = "-00" ; break; }
		} // fim switch sinal

		num  = objMersenne.genrand() * 32768;        //obtendo string numero
		numero   = String.format("%d", num);
		mant = objMersenne.genrand() * 309;          //obtendo string mantissa
		mantissa   = String.format("%d", mant);
		
		tam = numero.length();
		//aux      + (6-tam) = numero;
		tam = mantissa.length();
	//	aux_mant  + (3-tam) = mantissa;
		
		aux = aux_mant;
		
		if (limite > (int) aux.length())
			res = aux;
			else objDiversos.erro("Estouro de tamanho gerando float randomicamente",1);


} // fim forma_block_float_random

	// _________________________________________________________________
	/**
	 * Metodo usado para formatar um bloco string a partir de um valor passado
	 * por argumento.
	 */
	public void  forma_block_string(String res, int limite, String lido){
		int blocoTam = lido.length();
		String aux = null;
		aux = lido;
		//   for (int j = blocoTam; j < limite - 1; j++) aux[j] = '#';
		for (int j = blocoTam; j < limite - 1; j++) aux = aux.replace(aux.charAt(j), (char) 216);
		if (limite > (int) aux.length())
		res = aux;
		else objDiversos.erro("Estouro de tamanho recuperando string",1);
		
} // fim forma_block_string

	// _________________________________________________________________
	/** Metodo usado para formatar um bloco string aleatoriamente. */
	public void forma_block_string_random(String res, int limite){
		//int carac = 0, tam_alfanumerico = strlen(alfanumerico);
		int blocoTam = (objMersenne.genrand() * (int) ( objCentral.tamanhoMaximoString - objCentral.tamanhoMinimoString + 1 ) ) + (int)objCentral.tamanhoMinimoString;
		String aux = null;
		
		
		for (int i=0; i<blocoTam;i++){
	//	(aux+i) = generateChar( objCentral.tipoString );
		}
		for (int j = blocoTam; j < objCentral.tamanhoMaximoString ; j++)
	//	(aux+j) = 216;
		//for (int j = blocoTam; j < objCentral.tamanhoMaximoString ; j++) aux[j] ='#';
		//(aux + (int) objCentral.tamanhoMaximoString) = '\0';
		
		
		if (limite >= (int) aux.length())
		res = aux;
		else objDiversos.erro("Estouro de tamanho gerando string randomicamente",1);
		
		
		} // fim forma_block_string_random
}
