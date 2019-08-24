package io.billc.aeemo;

import android.app.AlertDialog;
import android.bluetooth.*;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.*;

import com.felhr.usbserial.*;

import java.util.List;
import java.util.UUID;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity {
	private int songDelayTime[] = {0, 1000, 0};

	private BluetoothGatt bluetoothGatt;
	private BluetoothDevice device;
	private BluetoothAdapter bluetoothAdapter;
	private int OVERALL_DELAY = 0;
	private String macAddress = "";
	private int selectedSong = 1;
	private MediaPlayer mp;
	private BluetoothAdapter bt;
	private String songList[] = {"Life Stream", "Evolution Era", "Without Me"};

	private SharedPreferences.Editor editor;
	private SharedPreferences sharedPreferences;
	private final static int STATE_CONNECTING = 0;
	private final static int STATE_CONNECTED = 1;
	private final static int STATE_DISCONNECTED = -1;
	private int bluetoothStatus = STATE_DISCONNECTED;

	private Handler handler;
	Runnable displayPlaying = new Runnable() {
		@Override
		public void run() {
			findViewById(R.id.layoutPlaying).setVisibility(View.VISIBLE);
		}
	};

	Runnable hidePlaying = new Runnable() {
		@Override
		public void run() {
			findViewById(R.id.layoutPlaying).setVisibility(View.GONE);
		}
	};

	Runnable playSongT = new Runnable() {
		@Override
		public void run() {
			playSong();
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		handler = new Handler();
		sharedPreferences = getSharedPreferences("settings", MODE_PRIVATE);
		editor = sharedPreferences.edit();
		macAddress = getMac();
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_scrolling);
		Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
		setSupportActionBar(toolbar);
		FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
		SeekBar seekVolume = (SeekBar) findViewById(R.id.seekVolume);
		seekVolume.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
			@Override
			public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
				setVolume(i);
			}
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
			}
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
			}
		});

		Button btnSwitchSong = (Button) findViewById(R.id.btnSwitchSong);
		btnSwitchSong.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				songSwitcher();
			}
		});

		mp = MediaPlayer.create(this, R.raw.life_stream);
		fab.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				if(!Utils.verifyMac(macAddress)){
					setMacAddress();
				}
				else{
					new Thread() {
						@Override
						public void run() {
							if(!Utils.verifyMac(macAddress)){
								setMacAddress();
							}
							else{
								if (bluetoothStatus == STATE_DISCONNECTED) {
									setState(STATE_CONNECTING);
									connectDevice();
								} else if (bluetoothStatus == STATE_CONNECTED) {
									setState(STATE_DISCONNECTED);
								}
							}

						}
					}.start();
				}
			}
		});

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu_scrolling, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		switch (id) {
			case R.id.action_about:
				AlertDialog.Builder dialog = new AlertDialog.Builder(this);
				dialog.setTitle(R.string.text_about_title);
				dialog.setMessage(R.string.text_about_content);
				dialog.setCancelable(true);
				dialog.setPositiveButton(getResources().getString(R.string.action_OK), new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialogInterface, int i) {
					}
				});
				dialog.show();
				return true;
			case R.id.action_macaddress:
				setMacAddress();
				return true;
			case R.id.action_delay:
				setOverallDelay();
				return true;
		}
		return super.onOptionsItemSelected(item);
	}

	public void setOverallDelay(){
		final EditText editText = new EditText(this);
		editText.setText(new Integer(OVERALL_DELAY).toString());
		editText.setLeft(5);
		editText.setRight(5);
		editText.setSingleLine();
		AlertDialog.Builder inputDialog = new AlertDialog.Builder(this);
		inputDialog.setView(editText);
		inputDialog.setMessage("请设置全局延迟（单位 ms）：");
		inputDialog.setCancelable(true);
		inputDialog.setPositiveButton(getResources().getString(R.string.action_OK), new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialogInterface, int i) {
				String text = editText.getText().toString();
				if(Utils.isNumeric(text)){
					int num = Integer.parseInt(editText.getText().toString());
					if(num >= 0){
						OVERALL_DELAY = num;
					}
					else{
						Toast toast = Toast.makeText(MainActivity.this, "请输入正整数，修改将不会保存。", Toast.LENGTH_SHORT);
						toast.show();
					}
				}
				else{
					Toast toast = Toast.makeText(MainActivity.this, "请输入一个数字，修改将不会保存。", Toast.LENGTH_SHORT);
					toast.show();
				}
			}
		});
		inputDialog.show();
	}

	public int connectDevice(){
		bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		final UUID SerialUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
		device = bluetoothAdapter.getRemoteDevice(macAddress);
		if (!bluetoothAdapter.isEnabled()) {
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableBtIntent, 1);
		}
		 bluetoothGatt = device.connectGatt(this, false, new BluetoothGattCallback() {
			@Override
			public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
				super.onConnectionStateChange(gatt, status, newState);
				if (newState == BluetoothGatt.STATE_CONNECTED) {
					Log.e("BluetoothGatt", "STATE_CONNECTED");
					setState(STATE_CONNECTED);
					bluetoothGatt = gatt;
					gatt.discoverServices();
					//Toast.makeText(getApplicationContext(), "连接成功3", Toast.LENGTH_SHORT).show();
				}
				else if(newState == BluetoothGatt.STATE_CONNECTING || newState == BluetoothGatt.STATE_DISCONNECTING){
					Log.e("BluetoothGatt", "Connecting");
					setState(STATE_CONNECTING);
				}
				else if(newState ==BluetoothGatt.STATE_DISCONNECTED){
					setState(STATE_DISCONNECTED);
				}
			}

			@Override
			public void onServicesDiscovered(BluetoothGatt gatt, int status) {
				super.onServicesDiscovered(gatt, status);
				List<BluetoothGattService> services = gatt.getServices();
//				for (BluetoothGattService service : services) {
//					List<BluetoothGattCharacteristic> characteristics = service.getCharacteristics();
//					for (BluetoothGattCharacteristic character : characteristics) {
//						enableNotification(gatt, service.getUuid(), character.getUuid());
//					}
//				}
				enableNotification(gatt, UUID.fromString("0000fff0-0000-1000-8000-00805f9b34fb"), UUID.fromString("0000fff6-0000-1000-8000-00805f9b34fb"));
			}

			 @Override
			 public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
				 super.onCharacteristicChanged(gatt, characteristic);
				 String inValue = new String(characteristic.getValue());
				 Log.e("DataReceived",
					   "onCharRead " + gatt.getDevice().getName() + " read "
							   + characteristic.getUuid().toString() + " -> "
							   + /*Utils.bytesToHexString(characteristic.getValue())*/ inValue);
				 if (inValue.substring(0,4).equals("PLAY")){
				 	selectedSong = Integer.parseInt(inValue.substring(4, 5));
				 	handler.post(playSongT);
				 //	playSong(selectedSong);
				 }
			 }

			 public boolean enableNotification(BluetoothGatt gatt, UUID serviceUUID, UUID characteristicUUID) {
				 boolean success = false;
				 BluetoothGattService service = gatt.getService(serviceUUID);
				 if (service != null) {
					 BluetoothGattCharacteristic characteristic = findNotifyCharacteristic(service, characteristicUUID);
					 if (characteristic != null) {
						 Log.i("Service UUID", serviceUUID.toString());
						 success = gatt.setCharacteristicNotification(characteristic, true);
						 if (success) {
							 // 来源：http://stackoverflow.com/questions/38045294/oncharacteristicchanged-not-called-with-ble
							 for (BluetoothGattDescriptor dp : characteristic.getDescriptors()) {
								 if (dp != null) {
									 if ((characteristic.getProperties() & BluetoothGattCharacteristic.PROPERTY_NOTIFY) != 0) {
										 dp.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
									 } else if ((characteristic.getProperties() & BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0) {
										 dp.setValue(BluetoothGattDescriptor.ENABLE_INDICATION_VALUE);
									 }
									 dp.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
									 gatt.writeDescriptor(dp);
//									 final byte[] data = characteristic.getValue();
//									 Log.i("GETVALUE", "data: " + characteristic.getValue());
								 }
							 }
						 }
					 }
				 }
				 return success;
			 }

			 private BluetoothGattCharacteristic findNotifyCharacteristic(BluetoothGattService service, UUID characteristicUUID) {
				 BluetoothGattCharacteristic characteristic = null;
				 List<BluetoothGattCharacteristic> characteristics = service.getCharacteristics();
				 for (BluetoothGattCharacteristic c : characteristics) {
					 if ((c.getProperties() & BluetoothGattCharacteristic.PROPERTY_NOTIFY) != 0
							 && characteristicUUID.equals(c.getUuid())) {
						 characteristic = c;
						 break;
					 }
				 }
				 if (characteristic != null)
					 return characteristic;
				 for (BluetoothGattCharacteristic c : characteristics) {
					 if ((c.getProperties() & BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0
							 && characteristicUUID.equals(c.getUuid())) {
						 characteristic = c;
						 break;
					 }
				 }
				 return characteristic;
			 }

		 });

		return 0;
	}

	public void setState(int state){
		FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
		switch (state) {
			case STATE_CONNECTING:
				((TextView) findViewById(R.id.textMain)).setText("正在尝试与设备通信...");
				fab.setImageResource(R.drawable.bluetooth_connecting);
				bluetoothStatus = STATE_CONNECTING;
				break;
			case STATE_CONNECTED:
				handler.post(displayPlaying);
				//findViewById(R.id.layoutPlaying).setVisibility(View.VISIBLE);
				TextView txtStatus = (TextView) findViewById(R.id.textStatusIndicator);
				((TextView) findViewById(R.id.textMain)).setText("设备 " + macAddress + " 已连接。");
				txtStatus.setText("暂未播放歌曲，Stand by.");
				fab.setImageResource(R.drawable.bluetooth_connected);
				bluetoothStatus = STATE_CONNECTED;
				break;
			case STATE_DISCONNECTED:
				handler.post(hidePlaying);
				//findViewById(R.id.layoutPlaying).setVisibility(View.INVISIBLE);
				if(bluetoothGatt != null){
					bluetoothGatt.disconnect();
				}

				((TextView) findViewById(R.id.textMain)).setText("设备已断开，请检查 MAC 地址并重新连接。");
				fab.setImageResource(R.drawable.bluetooth_connect);
				bluetoothStatus = STATE_DISCONNECTED;
				mp.stop();
				break;
		}
	}

	public void playSong(int songNum){
		selectedSong = songNum;
		playSong();
	}

	public void playSong(){
		int songNum = selectedSong;
		mp.stop();
		ImageView imgAlbum = (ImageView) findViewById(R.id.imgAlbum);
		TextView txtStatus = (TextView) findViewById(R.id.textStatusIndicator);
		switch (songNum){
			case 1:
				mp = MediaPlayer.create(this, R.raw.life_stream);
				imgAlbum.setImageResource(R.drawable.album_life_stream);
				break;
			case 2:
				mp = MediaPlayer.create(this, R.raw.evolution_era);
				imgAlbum.setImageResource(R.drawable.album_evolution_era);
				break;
			case 3:
				mp = MediaPlayer.create(this, R.raw.without_me);
				imgAlbum.setImageResource(R.drawable.album_without_me);
		}
		txtStatus.setText(String.format(getResources().getString(R.string.text_status), songList[selectedSong - 1]));
		try{
			Thread.sleep(songDelayTime[selectedSong - 1] + OVERALL_DELAY);
			//Thread.sleep(Integer.parseInt(((TextView) findViewById(R.id.textDelay)).getText().toString())  );
		}

		catch(Exception e){
			e.printStackTrace();
		}
		mp.start();
		updateProgress();
	}

	public void setVolume(int volume){
		float fVolume = (float)volume / 100;
		mp.setVolume(fVolume, fVolume);
	}

	public void updateProgress(){
		int duration = mp.getDuration();
		final ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
		progressBar.setMax(duration);
		new Thread() {
			@Override
			public void run() {
				while (mp.isPlaying()) {
					try {
						Thread.sleep(50);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					int currentPosition = mp.getCurrentPosition();
					progressBar.setProgress(currentPosition);
				}
			}
		}.start();
	}

	public void songSwitcher(){
		//selectedSong = (selectedSong == 3) ? (selectedSong + 1) : 1;
		playSong(selectedSong);
		System.out.println();
	}

	private void writeMac(String mac){
		macAddress = mac;
		editor.putString("mac_address", mac);
		editor.commit();
	}

	private String getMac(){
		macAddress = sharedPreferences.getString("mac_address", "");
		return macAddress;
	}

	private void setMacAddress(){
		final EditText editText = new EditText(this);
		editText.setText(getMac());
		editText.setLeft(5);
		editText.setRight(5);
		editText.setSingleLine();
		AlertDialog.Builder inputDialog = new AlertDialog.Builder(this);
		inputDialog.setView(editText);
		inputDialog.setMessage(getResources().getString(R.string.text_mac_title));
		inputDialog.setCancelable(true);
		inputDialog.setPositiveButton(getResources().getString(R.string.action_OK), new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialogInterface, int i) {
				String preMac = editText.getText().toString();
				if (!Utils.verifyMac(preMac)) {
					Toast toast = Toast.makeText(MainActivity.this, getResources().getText(R.string.toast_invalid_mac_address), Toast.LENGTH_SHORT);
					toast.show();
				} else {
					writeMac(editText.getText().toString());
					setState(STATE_DISCONNECTED);
				}
			}
		});
		inputDialog.show();
	}


	@Override
	protected void onDestroy() {
		super.onDestroy();
		bluetoothGatt.disconnect();
	}
}