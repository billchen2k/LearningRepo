<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
	<meta charset="ISO-8859-1">
	<title>Insert title here</title>
	<!-- import CSS -->
	<link rel="stylesheet" href="https://unpkg.com/element-ui/lib/theme-chalk/index.css">
	<!-- import JavaScript -->
	<script src="https://unpkg.com/element-ui/lib/index.js"></script>
	<link rel="stylesheet" href="//cdnjs.loli.net/ajax/libs/mdui/0.4.3/css/mdui.min.css">
	<script src="//cdnjs.loli.net/ajax/libs/mdui/0.4.3/js/mdui.min.js"></script>
</head>
<body>
	<form name="loginForm" method="POST" action="hello.jsp">
		<table class="mdui-ripple">
			<tr>
				<td><div align="right">User Name:</div></td>
				<td><input type="text" name="user" class="mdui-textfield-input" maxlength="20"></input></td>
			</tr>
			<tr>
				<td><div align="right">Password:</div></td>
				<td><input type="password" name="password" class="mdui-textfield-input" maxlength="20"></td>
			</tr>
			<tr>
				<td><input type="submit" name="submit" value="submit" class="mdui-btn mdui-btn-raised mdui-color-indigo mdui-ripple"></td>
				<td><input type="reset" name="reset" value="reset" class="mdui-btn mdui-btn-raised mdui-color-indigo mdui-ripple"></td>
			</tr>
		</table>
	</form>
	<% %>
</body>
</html>