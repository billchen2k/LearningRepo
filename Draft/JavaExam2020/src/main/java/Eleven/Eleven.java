package Eleven;

import it.firegloves.mempoi.MemPOI;
import it.firegloves.mempoi.builder.MempoiBuilder;
import it.firegloves.mempoi.domain.MempoiSheet;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.*;
import java.util.concurrent.CompletableFuture;

/**
 * 10
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-09 12:57
 **/
public class Eleven {

	public static final String URL = "jdbc:mysql://172.20.4.156:3306/t_test";
	public static final String USER = "test";
	public static final String PASSWORD = "test1209";
	private static Connection conn = null;

	public static void Connect() {
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection(URL, USER, PASSWORD);

		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}

	}

	public static void queryAndSave() {
		try {
			File fileDest = new File("output.xlsx");
			String queryStr = "SELECT * FROM t_test";
			PreparedStatement pstmt= conn.prepareStatement(queryStr);
			MemPOI memPOI = MempoiBuilder.aMemPOI()
					.addMempoiSheet(new MempoiSheet(pstmt, "output"))
					.build();
			CompletableFuture<String> fut = memPOI.prepareMempoiReportToFile();
			String absoluteFileName = fut.get();
			System.out.println("File saved to: " + absoluteFileName);
		}
		catch (Exception e) {
			e.printStackTrace();
		}


	}

	public static void main(String[] args) {
		Connect();
		queryAndSave();
	}

}
