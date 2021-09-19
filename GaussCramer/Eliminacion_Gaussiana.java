package gauss;

import java.util.Scanner;

public class Eliminacion_Gaussiana {

	Scanner teclado;
	double matriz[][];
	double cambio[];
	int n;

	public Eliminacion_Gaussiana() {
		teclado = new Scanner(System.in);
		System.out.println("Numero de Variables:");
		n = teclado.nextInt();
		matriz = new double[n][n + 1];
		cambio = new double[n + 1];
	}

	public void Llenar() {
		System.out.println("Llenando matriz:");
		for (int i = 0; i < matriz.length; i++) {
			System.out.println("Ecuacion " + (i + 1));
			for (int j = 0; j < matriz[i].length - 1; j++) {
				System.out.print("X" + (j + 1) + ":");
				matriz[i][j] = teclado.nextInt();
			}
			System.out.print("= ");
			matriz[i][n] = teclado.nextInt();
		}
	}

	public void Resolver() {
		double aux = 0;
		System.out.println("original");
		Imprimir();
		for (int x = 0; x < n; x++) {
			for (int i = x; i < n; i++) {
				if (matriz[i][x] < 0) {
					for (int j = x; j < matriz[i].length; j++) {
						matriz[i][j] = matriz[i][j] * -1;
					}
				}
				System.out.println("sin negativos");
				Imprimir();
				if (matriz[i][x] > 0) {
					aux = matriz[i][x];
					for (int j = x; j < matriz[i].length; j++) {
						matriz[i][j] = matriz[i][j] / aux;
					}
				}
			}
			System.out.println("Todos 1");
			Imprimir();
			for (int i = x; i < matriz[x].length; i++) {
				for (int j = x +1; j < matriz.length; j++) {
					System.out.println(matriz[x][i]+" "+matriz[j][i]);
					matriz[j][i] = (matriz[x][i] * -1) + matriz[j][i];

				}
			}
			System.out.println("con ceros");
			Imprimir();
		}
	}

	public void Imprimir() {
		for (int i = 0; i < matriz.length; i++) {
			for (int j = 0; j < matriz[i].length - 1; j++) {
				if (matriz[i][j] >= 0 && j > 0) {
					System.out.print(" + " + matriz[i][j] + "X" + (j + 1));
				} else {
					System.out.print(matriz[i][j] + "X" + (j + 1));
				}
			}
			System.out.println(" = " + matriz[i][n]);
		}
		System.out.println();
	}

	public static void main(String[] args) {
		Eliminacion_Gaussiana eg = new Eliminacion_Gaussiana();
		eg.Llenar();
		eg.Resolver();
		eg.Imprimir();
	}

}
