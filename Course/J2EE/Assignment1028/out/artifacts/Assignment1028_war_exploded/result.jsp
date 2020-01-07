<%--
  Created by IntelliJ IDEA.
  User: billchen
  Date: 2020-01-07
  Time: 20:17
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>欢迎</title>
</head>
<%
    if(request.getParameter("name") == null){
    	response.sendRedirect("/index.jsp");
    	return;
    }
    request.setCharacterEncoding("utf-8");
%>
<body>
    <h3>欢迎，<%=request.getParameter("name")%></h3>
    <p>以下是你的个人信息：</p>
    <table width="400" cellspacing="0" cellpadding="12" border="solid">
        <tbody>
        <tr>
            <td>姓名：</td>
            <td><%=request.getParameter("name")%>
            </td>
        </tr>
        <tr>
            <td>密码：</td>
            <td><%=request.getParameter("password")%>
            </td>
        </tr>
        <tr>
            <td>个人描述：</td>
            <td><%=request.getParameter("desc")%>
            </td>
        </tr>
        <tr>
            <td>性别</td>
            <td>
                <%=request.getParameter("gender").equals("male") ? "男" : "女" %>

            </td>
        </tr>
        <tr>
            <td>年级</td>
            <td><%=request.getParameter("grade") + " 年级"%>
            </td>
        </tr>
        </tbody>
    </table>

</body>
</html>
