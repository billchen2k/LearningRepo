<%--
  Created by IntelliJ IDEA.
  User: billchen
  Date: 2020-01-07
  Time: 20:02
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% request.setCharacterEncoding("utf-8"); %>
<html>
<head>
    <title>一个简单的简历</title>
</head>
<body>
<h3>
    一个简单的简历
</h3>
<table width="400" cellspacing="0" cellpadding="12" border="solid">
    <form method="get" action="result.jsp">
        <tbody>
        <tr>
            <td>姓名：</td>
            <td><input name="name" type="text"></td>
        </tr>
        <tr>
            <td>密码：</td>
            <td><input name="password" type="password"></td>
        </tr>
        <tr>
            <td>个人描述：</td>
            <td><textarea name="desc" rows="5"></textarea></td>
        </tr>
        <tr>
            <td>性别</td>
            <td>
                <input type="radio" name="gender" value="male" checked>男
                <input type="radio" name="gender" value="female">女
            </td>
        </tr>
        <tr>
            <td>年级</td>
            <td><select name="grade">
                <option value="1">1</option>
                <option value="2">2</option>
                <option value="3">3</option>
                <option value="4">4</option>
            </select>
            </td>
        </tr>
        <tr>
            <td></td>
            <td><input type="submit" value="提交" style="padding: 3px"></td>
        </tr>
        </tbody>
    </form>
</table>
</body>
</html>
