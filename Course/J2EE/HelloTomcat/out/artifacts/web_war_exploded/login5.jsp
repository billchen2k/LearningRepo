<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<form name="loginForm" method="POST" action="HelloServlet">
    <table>
      <tr>
        <td><div align="right">User Name:</div></td>
        <td><input type="text" name="user"></td>
      </tr>
      <tr>
        <td><div align="right">Password:</div></td>
        <td><input type="password" name="password"></td>
      </tr>
      <tr>
        <td><input type="submit" name="submit" value="submit"></td>
        <td><input type="reset" name="reset" value="reset"></td>
      </tr>
    </table>
</form>
</body>
</html>