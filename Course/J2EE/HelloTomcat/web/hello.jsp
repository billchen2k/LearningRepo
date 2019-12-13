<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
</head>
<body>

hello, There!

<p style="font-weight: bold;font-family: Helvetica;font-size: 150%"><%=request.getParameter("user") %> </p><br><br>
YourPassword IS:<%=request.getParameter("password") %>

</body>
</html>