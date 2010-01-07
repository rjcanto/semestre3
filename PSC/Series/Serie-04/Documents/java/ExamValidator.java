import java.io.*;

public final class ExamValidator {

	public interface BaseExamValidator {
		String ruleName();
		void setArgs(String args);
	}
	public interface OneExamValidator extends BaseExamValidator {
		boolean isValid(Exam exam);
	}
	public interface TwoExamsValidator extends BaseExamValidator {
		boolean isValid(Exam exam1, Exam exam2);
	}

	public static boolean validate(Exam[] exams, OneExamValidator[] val1, TwoExamsValidator[] val2) {
		boolean result = true;
		/* Validacoes singulares. */
		for (Exam e : exams)
			for (OneExamValidator v : val1)
				if (!v.isValid(e)) {
					System.err.println(e.course().acronym() + " falha na regra \"" + v.ruleName() + "\"");
					result = false;
				}
		/* Validacoes duplas. */
		for (int i = 0; i < exams.length - 1; ++i)
			for (int j = i + 1; j < exams.length; ++j)
				for (TwoExamsValidator v : val2)
					if (!v.isValid(exams[i], exams[j])) {
						System.err.println(exams[i].course().acronym() + " e " + exams[j].course().acronym() + " falham na regra \"" + v.ruleName() + "\"");
						result = false;
					}
		return result;
	}

	private abstract static class ValidatorLoader<T> extends DataLoader<T> {
		@SuppressWarnings("unchecked")
		protected T newInstance(String[] elems) {
			try {
				Class<?> cls = Class.forName(elems[0]);
				BaseExamValidator validator = (BaseExamValidator) cls.newInstance();
				if (elems.length > 1)
					validator.setArgs(elems[1]);
				return (T) validator;
			} catch (Exception e) {
				System.err.print("Validador "+elems[0]);
				if (elems.length > 1) System.err.print("(\""+elems[1]+"\")");
				System.err.println(" nao encontrado.");
				return null;
			}
		}	  
	}
	
	private static ValidatorLoader<OneExamValidator> oneExamValidatorLoader = new ValidatorLoader<OneExamValidator>() {
		protected OneExamValidator[] newArray(int numEntries) {
			return new OneExamValidator[numEntries];
		}
	};
	private static ValidatorLoader<TwoExamsValidator> twoExamsValidatorLoader = new ValidatorLoader<TwoExamsValidator>() {
		protected TwoExamsValidator[] newArray(int numEntries) {
			return new TwoExamsValidator[numEntries];
		}
	};
	
	public static void main(String[] args) {
		if (args.length != 2) {
			System.err.println("use: java ExamValidator SomeProgram.txt Exams.txt");
			System.exit(1);
		}
		try {
			ProgramCourse[] courses = ProgramCourse.loadFrom(args[0]);
			System.out.println("#ProgramCourse = " + courses.length);
			System.out.println("----------------");
			Exam[] exams = Exam.loadFrom(args[1], courses);
			System.out.println("#Exams = " + exams.length);
			System.out.println("----------------");

			OneExamValidator[]  val1 = oneExamValidatorLoader.loadFrom("Validators1.txt");
			TwoExamsValidator[] val2 = twoExamsValidatorLoader.loadFrom("Validators2.txt");

			boolean res = validate(exams,val1,val2);
			System.out.println("O mapa de exames e' " + (res ? "" : "in") + "valido.");
			
		} catch (IOException e) {
			System.err.println("Error loading data from " + args[0] + " or " + args[1]);
			e.printStackTrace();
		}
	}
}
