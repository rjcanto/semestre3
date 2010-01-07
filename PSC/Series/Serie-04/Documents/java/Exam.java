import java.io.*;
import java.util.*;
import java.util.regex.*;

public final class Exam {

	// --- Instance members ---

	private final ProgramCourse course;
	private final int date1;
	private final int date2;

	public Exam(ProgramCourse course, int date1, int date2) {
		this.course = course; this.date1 = date1; this.date2 = date2;
	}

	public ProgramCourse course() { return course; }
	public int            date1() { return date1; }
	public int            date2() { return date2; }

	// --- Static members (private) ---

	private static final Comparator<Exam> comparator = new Comparator<Exam>() {
		public int compare(Exam e1, Exam e2) {
			return e1.course.acronym().compareTo(e2.course.acronym());
		}
	};

	private static final class ExamLoader extends DataLoader<Exam> {
			
			private ProgramCourse[] courses;
			
			public ExamLoader(ProgramCourse[] cs) { courses=cs; }
			
			protected Exam[] newArray(int n) { return new Exam[n]; }
			
			protected Exam newInstance(String[] elems) {
				int index = ProgramCourse.indexOf(elems[0], courses);
				if (index<0) return null;
				return new Exam(courses[index], parseValue(elems[1]), parseValue(elems[2]));
			}
			private static int parseValue(String s) { 
				return ((s.length() < 4) && Pattern.matches("-?\\d+", s)) ? Integer.parseInt(s) : Integer.MIN_VALUE; 
			} 
		};

	// --- Static members (public) ---

	public static Comparator<Exam> comparator() { return comparator; }

	public static Exam[] loadFrom(String filename, ProgramCourse[] courses) throws IOException {
		Exam[] exams = new ExamLoader(courses).loadFrom(filename);
		Arrays.sort(exams, Exam.comparator);
		return exams;
	}

	public static int indexOf(String acr, Exam[] exams) {
		return Arrays.binarySearch(exams, new Exam(new ProgramCourse(acr, '\0', -1), Integer.MIN_VALUE, Integer.MIN_VALUE), Exam.comparator);
	}
}
