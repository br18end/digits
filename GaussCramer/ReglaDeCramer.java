package cramer;

import java.util.Scanner;

public class ReglaDeCramer {

	Scanner teclado;
	int n;
	int A[][];
	int det[][][];
	int detA;

	public ReglaDeCramer() {
		teclado = new Scanner(System.in);
		System.out.println("Ingrese el numero de variables:");
		n = teclado.nextInt();
		A = new int[n][n + 1];
		det = new int[n][n + (n - 1)][n];
		System.out.println(det.length);
		System.out.println(det[0].length);
		System.out.println(det[0][0].length);
	}

	public void Llenar() {
		System.out.println("Llenando matriz");
		for (int i = 0; i < A.length; i++) {
			System.out.println("Ecuacion " + (i + 1) + ":");
			for (int j = 0; j < A[i].length - 1; j++) {
				System.out.println("X" + j + ":");
				A[i][j] = teclado.nextInt();
			}
			System.out.println("= ");
			A[i][n] = teclado.nextInt();
		}
	}

	public void PasarAMatiz(int a[][]) {
		int b[][] = new int[a.length][a.length + (a.length - 1)];
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a.length; j++) {
				b[i][j] = a[i][j];
				if (j < a.length - 1) {
					b[i][j + a.length] = a[i][j];
				}
			}
		}
		System.out.println();
		for (int i = 0; i < b.length; i++) {
			for (int j = 0; j < b[i].length; j++) {
				System.out.print(b[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println("Derecha");
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a.length; j++) {
				System.out.print(b[j][i+j] + " ");
			}
			System.out.println();
		}
		System.out.println("Izquierda"+b.length+" "+a.length);
		for (int i = b[0].length-1; i >= a.length-1; i--) {
			for (int j = 0; j < a.length; j++) {
				System.out.print(b[j][i-j] + " ");
			}
			System.out.println();
		}
		
	}

	public void Imprimir() {
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[i].length - 1; j++) {
				if (A[i][j] >= 0 && j > 0) {
					System.out.print(" + " + A[i][j] + "X" + (j + 1));
				} else {
					System.out.print(A[i][j] + "X" + (j + 1));
				}
			}
			System.out.println(" = " + A[i][n]);
		}
		System.out.println();
	}

	public static void main(String[] args) {
		ReglaDeCramer cramer = new ReglaDeCramer();
		cramer.Llenar();
		cramer.Imprimir();
		int a[][] = new int[3][4];
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a[i].length; j++) {
				a[i][j] = (int) (Math.random() * 10);
				System.out.print(a[i][j] + " ");
			}
			System.out.println();
		}
		cramer.PasarAMatiz(a);
	}
}
