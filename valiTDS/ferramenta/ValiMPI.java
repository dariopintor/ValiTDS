package ferramenta;

import java.io.IOException;
/**
 * Nessa classe ainda funcionar corretamente dois m�todos: exeVali_inst( ) e exeVali_cc( )
 * o metodo vali_reduce n�o foi implementado
 * 
 * @throws IOException
 */
public class ValiMPI {

	/**
	 * Metodo utilizado para executar a instrumentacao de um codigo pela ValiMPI
	 * 
	 * @throws IOException
	 * @throws InterruptedException 
	 */
	public void exeVali_inst(String nomeArqFonte) throws IOException, InterruptedException {
		String cmd[] = {
				"gnome-terminal",
				"-x",
				"bash",
				"-c",
				"/home/labs/Software/ValiMPI_mmr/vali_inst/vali_inst "
						+ nomeArqFonte + ";  echo '<enter>'; read" };
				
		Process proc =	Runtime.getRuntime().exec(cmd, null, null);
		proc.waitFor();
	}

	/**
	 * metod apra executar a vali reduce
	 * @throws IOException
	 */
	public void exeVali_reduce(String nomeArqFonte) {

	}

	/**
	 * metodo usado para executar a vali elem
	 * @throws IOException
	 * @throws InterruptedException 
	 */
	public void exeVali_elem(String nProcess, String nomefuncoes)
			throws IOException, InterruptedException {
		String cmd[] = {
				"gnome-terminal",
				"-x",
				"bash",
				"-c",
				"/home/labs/Software/ValiMPI/vali_elem/vali_elem "
						+ nProcess + " " + nomefuncoes
						+ ";  echo '<enter>'; read" };

		Process proc =	Runtime.getRuntime().exec(cmd, null, null);
		proc.waitFor();
	}

	/** metodos usado para executar o executavel a partir do arquivo instrumentado
	 * @throws IOException
	 * @throws InterruptedException */
	public void exeVali_cc(String nomePrograma) throws IOException, InterruptedException {
		String cmd[] = {
				"gnome-terminal",
				"-x",
				"bash",
				"-c",
				"/home/labs/Software/ValiMPI/vali_exec/vali_cc -o "
						+ nomePrograma + " " + nomePrograma
						+ ".c_instrumentado.c " + ";  echo '<enter>'; read" };

		Process proc =	Runtime.getRuntime().exec(cmd, null, null);
		proc.waitFor();
	}

	/**
	 * metodo usado para executar um dado de teste na ferramenta
	 * @throws IOException
	 * @throws InterruptedException 
	 */
	public void exeVali_exec(String ndadoTeste, String nProcessos,
			String nomeFuncao, String dadoTeste) throws IOException, InterruptedException {

		String cmd[] = {
				"gnome-terminal",
				"-x",
				"bash",
				"-c",
				"/home/labs/Software/ValiMPI/vali_exec/vali_exec "
						+ ndadoTeste + " run " + nProcessos + " " + nomeFuncao
						+ " " + dadoTeste + ";  echo '<enter>'; read" };

		Process proc =	Runtime.getRuntime().exec(cmd, null, null);
		proc.waitFor();

	}

	/**
	 * metodo usado para obter a cobertura do dado de teste
	 * @throws IOException
	 * @throws InterruptedException 
	 */
	public void exeVali_eval(String criterio, String nProcess,
			String nomefuncoes) throws IOException, InterruptedException {
		String cmd[] = {
				"gnome-terminal",
				"-x",
				"bash",
				"-c",
				"/home/labs/Software/ValiMPI/vali_eval/vali_eval "
						+ criterio + " " + nProcess + " " + nomefuncoes
						+ " > vali_eval.out;  echo '<enter>'; read" };

		Process proc =	Runtime.getRuntime().exec(cmd, null, null);
		proc.waitFor();

	}
}
