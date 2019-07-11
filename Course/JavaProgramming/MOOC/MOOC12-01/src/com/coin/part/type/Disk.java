package com.coin.part.type;

import com.coin.concept.Component;
import com.coin.concept.Workable;

/**
 * Disk 磁盘的抽象定义，继承自Component，实现Workable
 * @author Tom
 *
 */
public abstract class Disk extends Component implements Workable {
	/**
	 * 单位:MB
	 */
	protected int volume;
	
	public Disk(String name, double price, int volume) {
		super(name, price);
		this.volume = volume;
	}
	
	
	@Override
	public String description() {
		StringBuilder cpuDescBuilder = new StringBuilder();
		cpuDescBuilder.append(super.description())
			.append(" size(MB):{")
			.append(volume)
			.append(" MB}");
		return cpuDescBuilder.toString();
	}
	
}
