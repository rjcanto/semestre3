import java.io.*;
import java.util.*;
import java.util.regex.*;

public final class ProgramCourse {

	// --- Instance members ---

	private final String acronym;
	private final char   type;
	private final int    terms;

	public ProgramCourse(String acronym, char type, int terms) {
		this.acronym = acronym; this.type = type; this.terms = terms;
	}

	public String acronym() { return acronym; }
	public char   type()    { return type; }
	public int    terms()   { return terms; }

	// --- Static members (private) ---

	private static final Comparator<ProgramCourse> comparator = new Comparator<ProgramCourse>() {
		public int compare(ProgramCourse pc1, ProgramCourse pc2) {
			return pc1.acronym.compareTo(pc2.acronym);
		}
	};

	private static final DataLoader<ProgramCourse> loader =
		new DataLoader<ProgramCourse>() {
			
			protected ProgramCourse[] newArray(int n) { return new ProgramCourse[n]; }
			
			protected ProgramCourse newInstance(String[] elems) {
				if (elems[0] == null) return null;
				char type = ((elems[1].length() == 1) ? elems[1].charAt(0) : '\0');
				int  trms = ((elems[2].length() < 10) && Pattern.matches("\\d+",elems[2])) ? Integer.parseInt(elems[2]) : -1;
				return new ProgramCourse(elems[0], type, trms);
			}
		};

	// --- Static members (public) ---

	public static Comparator<ProgramCourse> comparator() { return comparator; }

	public static ProgramCourse[] loadFrom(String filename) throws IOException {
		ProgramCourse[] courses = loader.loadFrom(filename);
		Arrays.sort(courses, ProgramCourse.comparator);
		return courses;
	}

	public static int indexOf(String acr, ProgramCourse[] courses) {
		return Arrays.binarySearch(courses, new ProgramCourse(acr, '\0', -1), ProgramCourse.comparator);
	}
}
