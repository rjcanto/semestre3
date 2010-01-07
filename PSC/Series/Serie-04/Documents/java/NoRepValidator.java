
public final class NoRepValidator implements ExamValidator.TwoExamsValidator {
	public String ruleName() { return "Sobreposicoes nao se repetem nas duas epocas."; }
	public void setArgs(String dist) {  }
	public boolean isValid(Exam exam1, Exam exam2) {
		return (exam1.date1() != exam2.date1()) ||
		       (exam1.date2() != exam2.date2());
	}
}
