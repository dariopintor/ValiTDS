package main;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.TimeZone;

public class Diversos {
	/***************************************************************************
	 * diversos.cpp - description ------------------- begin : Dom Jul 6 2003
	 * copyright : (C) 2003 by Luciano Petinati Ferreira email :
	 * petinat@inf.ufpr.br
	 * 
	 * http://openv2dge.googlecode.com/svn-history/r56/trunk/TiledMapEditor/src/
	 * tiled/util/MersenneTwister.java
	 ***************************************************************************/
	/***************************************************************************
	 * * This program is free software; you can redistribute it and/or modify *
	 * it under the terms of the GNU General Public License as published by *
	 * the Free Software Foundation; either version 2 of the License, or * (at
	 * your option) any later version. * *
	 ***************************************************************************/

	Mersenne objMersenne;

	public Diversos() {

		objMersenne = new Mersenne();
	}

	/** Funçço usada para apresentar mensagem de erro e finalizar o programa caso
	 * necessçrio.	 */
	public void erro(String str, int fim) {
		System.out
				.println("\n\n######################################################\n\nERRO - "
						+ str + "\nFinalizando programa.\n");
		if (fim == 1)
			System.exit(0);
	}
 

	/** Funcao usada para obter segundos referentes a data e hora atuais. */
	public long getSecs() {

		Calendar dataFinal = Calendar.getInstance();
		long hora = dataFinal.getTimeInMillis();
		return hora;

	}

 
	/**	 * Funçço usada para enviar conteudo no final de um arquivo com informacao
	 * da hora.
	 */
	public  void toFile(String caminho, String conteudo) throws IOException {
		
		Calendar dataFinal = Calendar.getInstance();
		long hora = dataFinal.getTimeInMillis();
		DateFormat formato = new SimpleDateFormat("HH:mm:ss");
		String formattedDate = formato.format(hora);
		
		File arquivo = new File(caminho);	
		
		//cria o arquivo caso n exista
		if(arquivo.exists() == false)	{
			arquivo.createNewFile();
		}
		
		FileWriter fw = new FileWriter(arquivo, true);  //recebe um caminho de um arquivo
        BufferedWriter conexao = new BufferedWriter(fw);  //da a permissço para esse aquivo ser escrito
        conexao.write(conteudo + "\t" + formattedDate);   //escreve no arquivo
        conexao.newLine();  
        conexao.close();  
	}
	 

	/**	 metodo usado pra escrever no final de um arquivo
	 * caso o arquivo nao existe então é criado
	 */
	public  void escreverArquivo(String caminho, String conteudo) throws IOException {
		
		File arquivo = new File(caminho);	
		
		//cria o arquivo caso n exista
		if(arquivo.exists() == false)	{
			arquivo.createNewFile();
		}
		
		FileWriter fw = new FileWriter(arquivo, true);  //recebe um caminho de um arquivo
        BufferedWriter conexao = new BufferedWriter(fw);  //da a permissço para esse aquivo ser escrito
        conexao.write(conteudo);   //escreve no arquivo
        conexao.newLine();  
        conexao.close(); 
	}	
	
 	/** Funcao usada para retornar o numero de ocorrencias de um caracter em um
	 * string.*/
	public int numberOf(String str, char busca) {
		int tam = str.length();
		int res = 0;
		for (int i = 0; i < tam; i++) {
			if (str.charAt(i) == busca)
				res++;
		}// fim for
		return res;
	}// fim indexOf

	
	/** Funçao usada para retornar a posiçço de um caracter em um string. */
	public int indexOf(String str, char busca) {
		int tam = str.length();
		for (int i = 0; i < tam; i++) {
			if (str.charAt(i) == busca)
				return i;
		}// fim for
		return -1;
	}// fim indexOf

	
	/** Funcao usada para retornar a posicao de um substring em um string. */
	int indexOf(String str, String busca) {
		int tamStr = str.length(), tamBusca = busca.length(), res = -1;
		if (tamBusca > tamStr)
			return -1;
		for (int i = 0; i <= tamStr - tamBusca; i++) {
			if (str.charAt(i) == busca.charAt(0)) {
				res = i;
				for (int j = 1; j < tamBusca; j++) {
					if (str.charAt(i + j) != busca.charAt(j))
						res = -1;
				}// fim for
				if (res != -1)
					return res;
			} // fim if
		}// fim for
		return -1;

	}// fim indexOf


	/** Funcaoo usada para gerar um caracter aleatoriamente, com base no string
	 * seletivo.*/
	char generateChar(String seletivo) {
		int somatoria = 0, sorteio = 0;
		int entraEspaco = 0, entraLETRA = 0, entraLetra = 0, entraNumero = 0;
		for (int i = 0; i < (int) seletivo.length(); i++) {
			switch ((seletivo + i)) {
			case "s":
				somatoria++;
				entraEspaco = 1;
				break;
			case "L":
				somatoria += 26;
				entraLETRA = 1;
				break;
			case "l":
				somatoria += 26;
				entraLetra = 1;
				break;
			case "n":
				somatoria += 10;
				entraNumero = 1;
				break;
			} 
		}
		// Obtive quantos podem ser os numeros a serem sorteados.
		sorteio = (objMersenne.genrand() % somatoria);
		// Tirar caracteres invalidos, joga para espaço
		sorteio += 32;
		// Se espaço fora soma 1
		if (entraEspaco == 0)
			sorteio += 1;
		// Tira espaços invalidos entre espaço e numeros, joga para numeros
		if (sorteio > 32)
			sorteio += 15;
		// Se numeros fora soma 10
		if ((entraNumero == 0) && (sorteio >= 48))
			sorteio += 10;
		// Tira espaços invalidos entre espaço e numeros, joga para LETRAS
		if (sorteio > 57)
			sorteio += 7;
		// Se LETRAS fora soma 26
		if ((entraLETRA == 0) && (sorteio >= 65))
			sorteio += 26;
		// Tira espaços invalidos entre LETRAS e letras, joga para letras
		if (sorteio > 90)
			sorteio += 6;
		// Se letras fora soma 26
		if ((entraLetra == 0) && (sorteio >= 97))
			sorteio += 26;

		return (char) sorteio;
	} // fim generateChar

	
	/**
	 * Funcao usada para calcular tamanho usado pelos numeros na linha do
	 * arquivo*/
	int nroEspacos(int tamPopulacao) {
		int nroEspacos = 0;
		for (int base = 10; tamPopulacao >= base; base *= 10, nroEspacos++);
		return nroEspacos + 10;
	}

	boolean cobre(String cobertura1, String cobertura2) {
		int tam = cobertura2.length();
		for (int i = 0; i < tam; i++) {
			if ((cobertura2.charAt(i) == 'X') && (cobertura1.charAt(i) != 'X'))
				return false;
		}// fim for
		return true;
	}
	
	
	/*** Metodo usado para contar a quantidade de linhas dentro de um aquivo
	 * @throws IOException	 */
	public int quantidadeLinhas(File arquivo) throws IOException {
		String linha = "";
		int quantidadeDeLinhas = 0;
		FileReader arq = new FileReader(arquivo);
		BufferedReader lerArq = new BufferedReader(arq);

		linha = lerArq.readLine();
		while (linha != null) {
			quantidadeDeLinhas++;
			linha = lerArq.readLine();
		}
		
		lerArq.close();
		return quantidadeDeLinhas;
	}

	
	/** Metodo usado para copiar um arquivo de outro
	 *  @throws IOException*/
	public void copyFile(String source, File target) throws IOException {
		InputStream in = new FileInputStream(source);
		OutputStream out = new FileOutputStream(target); // Transferindo bytes
															// de entrada para
															// saçda
		byte[] buf = new byte[1024];
		int len;
		while ((len = in.read(buf)) > 0) {
			out.write(buf, 0, len);
		}
		in.close();
		out.close();
	}

	
	/** Metodo usado copiar um diretorio ( na verdade faz um backup do diretorio
	 * atual, pois este vai ser sobscrito na proxima geracao*/
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

}
