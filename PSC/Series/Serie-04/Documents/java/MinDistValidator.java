
public final class MinDistValidator implements ExamValidator.OneExamValidator {
    private int minDist = 13;
	public void setArgs(String dist) {
		minDist = Integer.parseInt(dist); 
	}
	public String ruleName() { return "Distancia minima entre exames da mesma UC.";	}
	public boolean isValid(Exam exam) { 
		return (exam.date2() - exam.date1()) >= minDist; 
	}
}
