package algoritmoGenetico;

import java.io.File;
import java.rmi.server.ObjID;
import java.util.Formattable;

import main.Mersenne;
import main.Diversos;
import ferramenta.Central;
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

	public int novo(String linha) {
		int numArgumentos = objCentral.formatoIndividuo.length();
		int virg = -1;
		String blocoLinha = null, bloco = null;
		
		for (int cont = 0; cont < numArgumentos; cont++) {
			
			if ((virg = objDiversos.indexOf(linha, ',')) != -1)
				strncpy(blocoLinha, linha, virg);
			else
				strcpy(blocoLinha, linha);
			objDiversos.trim(blocoLinha);
			strcpy(linha, linha + virg + 1);

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
				strncpy(bloco, blocoLinha, 1);
				break;
			}
			}// fim switch
			representacao = bloco;
		}

	}

	/**
	 * * M�todo para recuperar o pos-esimo indiv�duo da popula��o. pos deve
	 * variar de 0 at� tamanho da popula��o - 1.
	 */
	public int load(int pos) {
		int i = 0;
		String gene = null, geneAux = null;
		File ptrPopulation = null;

		// ptrPopulation = fopen(objCentral.arquivoPopulacao, "r");
		if (ptrPopulation == null) {
			System.out.printf("aqui nao abriu o arquivo de populacao : %s");
		}
		if (pos >= objCentral.tamanhoPopulacao) {
			System.out.printf("Pos, %d, extrapolou tamanho da populacao %f");
		}

		for (i = 0; i <= pos; i++) {
			// cout << "\n ind nro " << i;
			if (pos == 14)
				pos += 0;

			fgets(gene, (int) (objCentral.tamanhoIndividuo + 10), ptrPopulation);

		}// fim for

		objDiversos.trim(gene);

		i = objDiversos.indexOf(gene, ':') + 1;
		geneAux = gene + i;
		objDiversos.trim(geneAux);
		setRepresentacao(geneAux);
	}

	// _________________________________________________________________

	/** M�todo que atribui valor para a representa��o de um indiv�duo. */
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

	/** M�todo que recupera o respectivo valor do bloco passado como argumento. */
	public int decode_block_int(String bloco) {

		return Integer.parseInt(bloco);
	}

	// _________________________________________________________________

	/**
	 * M�todo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	public void forma_block_int(String res, int limite, String lido) {
		int tam = 0;
		String aux, numero;
		objDiversos.trim(lido);
		if ((lido.charAt(0) == '-') || (lido.charAt(0) == '+')) {
		String resposta = aux.replace(aux.charAt(0), lido.charAt(0));
		aux = resposta;
			lido++;
		}

		objDiversos.trim(lido);
		numero = lido;
		tam = numero.length();

		// strcpy(aux + (6-tam), numero); em c++

		if (limite > (int) aux.length())
			res = aux;
		else
			objDiversos.erro(
					"Estouro de tamanho gerando inteiro randomicamente", 1);

	}

	// _________________________________________________________________

	/** M�todo usado para formatar um bloco aleatoriamente. */
	public int  forma_block_int_random(String res, int limite)
{
int tam = 0;
String aux = null,  numero = null;


 aux = "+00000";
int num = 0;
if (objCentral.tamanhoMinimoInteiro < 0)
{
int sinal = objMersenne.genrand()%2;                    //[0+,1-]
if(sinal == 1) // -
{
num = ( objMersenne.genrand() % ( ( -1 * (objCentral.tamanhoMinimoInteiro ) +1 ) );
aux[0] = '-';
}
else //+
num = (  objMersenne.genrand() % ( (objCentral.tamanhoMaximoInteiro + 1 ) );
}
else
num = (  objMersenne.genrand() % (int)(objCentral.variacaoInteiro) ) + objCentral.tamanhoMinimoInteiro;
//printf("dados - %d %d %d %d\n",num,objCentral.tamanhoMinimoInteiro,objCentral.tamanhoMaximoInteiro,objCentral.variacaoInteiro);
sprintf(numero, "%d", num);
objDiversos.trim (numero);
tam = strlen(numero);
strcpy(aux + (6-tam), numero);
memset( * res, '\0', limite);
if (limite >= (int) strlen(aux))
strcpy( * res, aux);
else erro("Estouro de tamanho gerando inteiro randomicamente",1);

return 1;
}// fim forma_block_int_random

	// _________________________________________________________________

	/** M�todo que recupera o respectivo valor do bloco passado como argumento. */
	public double  decode_block_double (String bloco){
double res = 0;
int pos_E  = -1, mant = 1;
String mantissa = null, * numero = null;

objDiversos.trim ( bloco);
pos_E = objDiversos.indexOf(bloco, 'E');
strcpy( numero, bloco );
if(pos_E != -1)
{
strncpy(numero, bloco, pos_E);
strcpy(mantissa, bloco + pos_E + 1);
mant = atoi(mantissa);

}// fim pos_E

res = atoi(numero);
res *= pow(10, mant );

alocaCharPtr( & numero  , 20, "decode_block_double", "numero");
alocaCharPtr( & mantissa, 10, "decode_block_double", "mantissa");
return res;
}

	// _________________________________________________________________

	/**
	 * M�todo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	int  forma_block_double (String res, int limite, String lido){
int tam = 0;
int pos_E = -1;
char aux[20], mantissa[10], aux_mant[10], numero[10];
memset(aux     , '\0', 20);
memset(mantissa, '\0', 10);
memset(aux_mant, '\0', 10);
memset(numero  , '\0', 10);
strcpy( aux, "+00000");
strcpy( aux_mant, "+000");
strcpy( mantissa, "000");

objDiversos.trim ( & lido);
if ( (lido[0] == '-') || (lido[0] == '+') )
{
aux[0] = lido[0];
lido++;
}
objDiversos.trim ( & lido);
pos_E = objDiversos.indexOf(lido, 'E');
if( pos_E != -1)
{                                            //existe mantissa
strncpy(numero  , lido,  pos_E);
lido += pos_E;
if ( (lido[0] == '-') || (lido[0] == '+') )
{
aux_mant[0] = lido[0];
lido++;
}
objDiversos.trim ( & lido);
strcpy (mantissa, lido);
}// fim if tem E
else strcpy (numero, lido);
tam = strlen(numero);
strcpy(aux      + (6-tam), numero);
tam = strlen(mantissa);
strcpy(aux_mant + (4-tam), mantissa);

strcat(aux, aux_mant);
memset( * res, '\0', limite);
if (limite > (int) strlen(aux))
strcpy( * res, aux);
else
erro("Estouro de tamanho recuperando double",1);
return true;
}// fim forma_block_double

	// _________________________________________________________________

	/** M�todo usado para formatar um bloco double aleatoriamente. */

	int  forma_block_double_random(String res, int limite)
{
int tam = 0, num = 0, mant = 0, sinal = objMersenne.genrand()%4;         //[0++,1+-,2-+,3--]
char aux[20], mantissa[10], aux_mant[10], numero[10];
memset(aux     , '\0', 20);
memset(mantissa, '\0', 10);
memset(aux_mant, '\0', 10);
memset(numero  , '\0', 10);

switch (sinal)//obtendo sinais
{
case 0: { strcpy( aux, "+00000"); strcpy( aux_mant, "+000"); break; }
case 1: { strcpy( aux, "+00000"); strcpy( aux_mant, "-000"); break; }
case 2: { strcpy( aux, "-00000"); strcpy( aux_mant, "+000"); break; }
case 3: { strcpy( aux, "-00000"); strcpy( aux_mant, "-000"); break; }
} // fim switch sinal

num  = objMersenne.genrand() % 32768;        //obtendo string numero
sprintf(numero   , "%d",num);
mant = objMersenne.genrand() % 309;          //obtendo string mantissa
sprintf(mantissa , "%d", mant);

tam = strlen(numero);
strcpy(aux      + (6-tam), numero);
tam = strlen(mantissa);
strcpy(aux_mant + (4-tam), mantissa);

strcat(aux, aux_mant);

memset( * res, '\0', limite);
if (limite > (int) strlen(aux))
strcpy( * res, aux);
else erro("Estouro de tamanho gerando double randomicamente",1);
return 1;

} // fim forma_block_double_random

	// _________________________________________________________________

	/** M�todo que recupera o respectivo valor do bloco passado como argumento. */
	public double  decode_block_float ( String bloco ){
double res = 0;
int pos_E  = -1, mant = 1;
String mantissa = null, * numero = null;
alocaCharPtr( & numero  , 20, "decode_block_float", "numero");
alocaCharPtr( & mantissa, 10, "decode_block_float", "mantissa");
objDiversos.trim ( & bloco);
pos_E = objDiversos.indexOf(bloco, 'E');
strcpy( numero, bloco );
if(pos_E != -1)
{
strncpy(numero, bloco, pos_E);
strcpy(mantissa, bloco + pos_E + 1);
mant = atoi(mantissa);

}// fim pos_E
res = atoi(numero);
res *= pow(10, mant );

alocaCharPtr( & numero  , 20, "decode_block_float", "numero");
alocaCharPtr( & mantissa, 10, "decode_block_float", "mantissa");
return res;
}

	// _________________________________________________________________

	/**
	 * M�todo usado para formatar um bloco a partir de um valor passado por
	 * argumento.
	 */
	int  forma_block_float (String res, int limite, String lido){
int tam = 0;
int pos_E = -1;
char aux[20], mantissa[10], aux_mant[10], numero[10];
memset(aux     , '\0', 20);
memset(mantissa, '\0', 10);
memset(aux_mant, '\0', 10);
memset(numero  , '\0', 10);
strcpy( aux, "+00000");
strcpy( aux_mant, "+00");
strcpy( mantissa, "00");

objDiversos.trim ( & lido);
if ( (lido[0] == '-') || (lido[0] == '+') )
{
aux[0] = lido[0];
lido++;
}
objDiversos.trim (lido);
pos_E = objDiversos.indexOf(lido, 'E');
if( pos_E != -1)
{                                            //existe mantissa
strncpy(numero  , lido,  pos_E);
lido += pos_E;
if ( (lido[0] == '-') || (lido[0] == '+') )
{
aux_mant[0] = lido[0];
lido++;
}
objDiversos.trim ( & lido);
strcpy (mantissa, lido);
}// fim if tem E
else strcpy (numero, lido);
tam = strlen(numero);
strcpy(aux      + (6-tam), numero);
tam = strlen(mantissa);
strcpy(aux_mant + (3-tam), mantissa);

strcat(aux, aux_mant);
memset(*res, '\0', limite);
if (limite > (int) strlen(aux))
strcpy(*res, aux);
else
erro("Estouro de tamanho recuperando float",1);
return true;
}

	// _________________________________________________________________
	/** M�todo usado para formatar um bloco float aleatoriamente. */
	int  forma_block_float_random(String res, int limite)
{
int tam = 0, num = 0, mant = 0, sinal = objMersenne.genrand()%4;         //[0++,1+-,2-+,3--]

String aux[20], mantissa[10], aux_mant[10], numero[10];
memset(aux     , '\0', 20);
memset(mantissa, '\0', 10);
memset(aux_mant, '\0', 10);
memset(numero  , '\0', 10);

switch (sinal)//obtendo sinais
{
case 0: { strcpy( aux, "+00000"); strcpy( aux_mant, "+00"); break; }
case 1: { strcpy( aux, "+00000"); strcpy( aux_mant, "-00"); break; }
case 2: { strcpy( aux, "-00000"); strcpy( aux_mant, "+00"); break; }
case 3: { strcpy( aux, "-00000"); strcpy( aux_mant, "-00"); break; }
} // fim switch sinal

num  = objMersenne.genrand() % 32768;        //obtendo string numero
sprintf(numero   , "%d",num);
mant = objMersenne.genrand() % 39;          //obtendo string mantissa
sprintf(mantissa , "%d", mant);
tam = strlen(numero);
strcpy(aux      + (6-tam), numero);
tam = strlen(mantissa);
strcpy(aux_mant + (3-tam), mantissa);

strcat(aux, aux_mant);

memset( *res, '\0', limite);
if (limite > (int) strlen(aux))
strcpy( *res, aux);
else erro("Estouro de tamanho gerando float randomicamente",1);
return 1;

} // fim forma_block_float_random

	// _________________________________________________________________
	/**
	 * M�todo usado para formatar um bloco string a partir de um valor passado
	 * por argumento.
	 */
	int  forma_block_string(String res, int limite, String lido)
{
int blocoTam = strlen(lido);
String aux = null;
alocaCharPtr( & aux , limite, "forma_block_string", "aux");
strcpy(aux, lido);
//   for (int j = blocoTam; j < limite - 1; j++) aux[j] = '#';
for (int j = blocoTam; j < limite - 1; j++) aux[j] = 216;
aux[limite - 1] = '\0';
memset( * res, '\0', limite);
if (limite > (int) strlen(aux))
strcpy( * res, aux);
else erro("Estouro de tamanho recuperando string",1);
desalocaCharPtr( & aux , limite, "forma_block_string", "aux");
return true;
} // fim forma_block_string

	// _________________________________________________________________
	/** M�todo usado para formatar um bloco string aleatoriamente. */
	int  forma_block_string_random(String res, int limite)
{
//int carac = 0, tam_alfanumerico = strlen(alfanumerico);
int blocoTam = (objMersenne.genrand() % (int) ( objCentral.tamanhoMaximoString - objCentral.tamanhoMinimoString + 1 ) ) + (int)objCentral.tamanhoMinimoString;
String aux = null;
alocaCharPtr( & aux , limite + 1, " forma_block_string", "aux");

for (int i=0; i<blocoTam;i++){
*(aux+i) = generateChar( objCentral.tipoString );
}
for (int j = blocoTam; j < objCentral.tamanhoMaximoString ; j++)
*(aux+j) = 216;
//for (int j = blocoTam; j < objCentral.tamanhoMaximoString ; j++) aux[j] ='#';
*(aux + (int) objCentral.tamanhoMaximoString) = '\0';

//memset( * res, '\0', limite);
//cout << "\nValor de limite= " << limite;
//cout << "\nValor de blocoTam= " << blocoTam;
//cout << "\nValor de aux= " << aux;
//cout << "\nValor strlen(aux)= " << strlen(aux);

if (limite >= (int) strlen(aux))
strcpy( * res, aux);
else erro("Estouro de tamanho gerando string randomicamente",1);
desalocaCharPtr( & aux , limite + 1, "forma_block_string", "aux");
return true;
} // fim forma_block_string_random
}
