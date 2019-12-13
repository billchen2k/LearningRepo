<%-- Created by IntelliJ IDEA. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>Hello, jsp.</title>
  </head>
  <body>
    <h1>This is a test.</h1>
    <p>This is another test.</p>

    <form method="post" action="api/upload" enctype="multipart/form-data">
      选择一个文件:
      <input type="file" name="uploadFile"/>
      <br/><br/>
      <input type="submit" value="上传"/>
    </form>

  </body>
</html>