/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Testes simples às classes Point e Point3D.
 */

public class jtestp {

	private static void printInfo(Point p) {
		p.print();
		System.out.println("magnitude: " + p.magnitude());
	}

	private static void printInfo3D(Point3D p3) {
		p3.print();
		System.out.println("magnitude: " + p3.magnitude());
	}

	public static void main(String[] args) {

		Point p;
		Point3D p3;

		p = new Point(1, 2, "p");
		printInfo(p);

		System.out.println("------------------------");

		p.translate(3, 1);
		printInfo(p);

		System.out.println("------------------------");

		p3 = new Point3D(1, 2, 3, "p3");
		printInfo((Point)p3);
		printInfo3D(p3);

		System.out.println("------------------------");

		p3.translate(1, 0, -1);
		printInfo((Point)p3);
		printInfo3D(p3);
	}
}
