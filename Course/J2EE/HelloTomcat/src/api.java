import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Parameter;
import java.util.Enumeration;

@WebServlet(name = "api")
public class api extends HttpServlet {
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		Enumeration<String> parameterEnumeration = request.getParameterNames();
		while(parameterEnumeration.hasMoreElements()){
			String paramName = (String)parameterEnumeration.nextElement();
			out.print("<TR><TD>" + paramName + "\n<TD>");
			String paramValue =
					request.getParameter(paramName);
				out.println(paramValue);

			out.print("</TD></TR>");
		}
	}
}
