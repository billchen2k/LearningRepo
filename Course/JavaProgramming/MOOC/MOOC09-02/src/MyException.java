public class MyException extends Exception {

	private String returnCode ;  //异常对应的返回码
	private String returnMsg;  //异常对应的描述信息
	
	public MyException() {
		super();
	}

	public MyException(String returnMsg) {
		super(returnMsg);
		this.returnMsg = returnMsg;
	}

	public MyException(String returnCode, String returnMsg) {
		super();
		this.returnCode = returnCode;
		this.returnMsg = returnMsg;
	}

	public String getReturnCode() {
		return returnCode;
	}

	public String getreturnMsg() {
		return returnMsg;
	}
}