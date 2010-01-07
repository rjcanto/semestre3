/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Point: versão Java da classe Point
 */

public class Point {
	protected String name;
	protected int x;
	protected int y;

	public Point(String name) { this(0, 0, name); }
	public Point(int px, int py, String pname) {
		name = pname;
		x = px;
		y = py;
	}

	public int getX() { return x; }
	public int getY() { return y; }

	public String getName() { return name; }

	public void translate(int dx, int dy) {
		x += dx;
		y += dy;
	}

	public double magnitude() {
		return Math.sqrt((double)x * x + (double)y * y);
	}

	public void print() {
		System.out.println("{ name = \"" + name + "\"; x = " + x + "; y = " + y + " }");
	}
}

