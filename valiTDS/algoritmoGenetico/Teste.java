package algoritmoGenetico;

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

import main.Diversos;
import ferramenta.Central;
import ferramenta.Ferramenta;
import ferramenta.ValiMPI;

public class Teste {
	static Central objCentral;
	static Diversos objDiversos;
	static Ferramenta objFerramenta;
	static ValiMPI objUsaValiMPI;

	public static void main(String[] args) throws IOException, InterruptedException {
		objFerramenta = new Ferramenta();
		objCentral = new Central();
		objUsaValiMPI = new ValiMPI();
	//	objCentral.interpretaArquivoConfiguracao();
		//objFerramenta.obtemElementosRequeridosValiMPI();
		
		//objUsaValiMPI.exeVali_inst("gcd.c");
		//objUsaValiMPI.exeVali_elem("4", "\"Master(0)\" \"Slave(1,2,3)\"");
		//objCentral.setDiretorio("gcd");
		//objCentral.setArquivoVali_EvalOut("vali_out");
	//	objUsaValiMPI.exeVali_eval("todos-nos","4", "\"Master(0)\" \"Escravo(1,2,3)\"");
		//System.out.println(objCentral.arquivoVali_EvalOut.getPath());
		}
		
	
		
		
		 
		
		
		
		
	}

