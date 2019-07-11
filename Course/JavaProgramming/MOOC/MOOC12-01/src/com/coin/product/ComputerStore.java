package com.coin.product;

import com.coin.part.imp.AMDCPU;
import com.coin.part.imp.IntelCPU;
import com.coin.part.imp.Seagate;
import com.coin.part.imp.WestDigital;
import com.coin.part.type.CPU;
import com.coin.part.type.Disk;

/**
 * ComputerStore 矿机公司类，出售矿机
 * @author Tom
 *
 */
public class ComputerStore {
	public static void main(String[] args) {		
		
		//定义第一台机器的部件
		CPU intel = new IntelCPU("intel cpu", 2, 1000);
		Disk seagate = new Seagate("Seagate disk", 1000, 40960);		
		
		//组装第一台机器并工作
		Computer computer1 = new Computer("computer 1", intel, seagate);		
		System.out.println("computer 1 description: " + computer1.description());
		System.out.println("Computer 1 work: ");
		computer1.work();
		
		//定义第二台机器的部件
		CPU amd = new AMDCPU("AMD cpu", 800, 2);
		Disk westdigital = new WestDigital("West Digital disk", 2000, 81920);
		
		//组装第二台机器并工作
		Computer computer2 = new Computer("computer 2", amd, westdigital);		
		System.out.println("computer 2 description: " + computer2.description());
		System.out.println("Computer 2 work: ");
		computer2.work();
	}
}
