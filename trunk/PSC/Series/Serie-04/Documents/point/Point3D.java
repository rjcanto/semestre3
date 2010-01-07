/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Point3D: versão Java da classe Point3D
 */

public class Point3D extends Point {
	protected int z;

	public Point3D(String name) { this(0, 0, 0, name); }
	public Point3D(int px, int py, int pz, String pname) {
		super(px, py, pname);
		z = pz;
	}

	public int getZ() { return z; }

	public void translate(int dx, int dy, int dz) {
		translate(dx, dy);
		z += dz;
	}

	public double magnitude() {
		return Math.sqrt((double)x * x + (double)y * y + (double)z * z);
	}

	public void print() {
		System.out.println("{ name = \"" + name + "\"; x = " + x + "; y = " + y + "; z = " + z + " }");
	}
}
