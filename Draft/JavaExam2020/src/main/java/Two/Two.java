package Two;

import org.apache.poi.openxml4j.exceptions.InvalidFormatException;
import org.apache.poi.openxml4j.opc.OPCPackage;
import org.apache.poi.xwpf.usermodel.*;
import org.apache.poi.util.*;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * 2
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-09 14:11
 **/
public class Two {

	public static void main(String[] args) {
		try {
			XWPFDocument doc = new XWPFDocument(OPCPackage.open("template.docx"));
			for (XWPFTable tbl : doc.getTables()) {
				for (XWPFTableRow row : tbl.getRows()) {
					for (XWPFTableCell cell : row.getTableCells()) {
						for (XWPFParagraph p : cell.getParagraphs()) {
							for (XWPFRun r : p.getRuns()) {
								String text = r.getText(0);
								if (text != null && text.contains("$$userno")) {
									text = text.replace("$$userno", "12345678");
									r.setText(text,0);
								}
								if (text != null && text.contains("$$username")) {
									text = text.replace("$$username", "姓名");
									r.setText(text,0);
								}
								if (text != null && text.contains("$$barcode")) {
									text = text.replace("$$barcode", "");
									r.setText(text,0);
									String barcodeFile = "barcode.png";
									FileInputStream is = new FileInputStream(barcodeFile);
									r.addPicture(is, XWPFDocument.PICTURE_TYPE_PNG, barcodeFile, Units.toEMU(100), Units.toEMU(20));
								}
								if (text != null && text.contains("$$image")) {
									text = text.replace("$$image", "");
									r.setText(text,0);
									String headFile = "head.png";
									FileInputStream is = new FileInputStream(headFile);
									r.addPicture(is, XWPFDocument.PICTURE_TYPE_PNG, headFile, Units.toEMU(50), Units.toEMU(50));
								}
							}
						}
					}
				}
			}
			doc.write(new FileOutputStream("output.docx"));
			System.out.println("Finished. File saved to output.docx.");
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
}
