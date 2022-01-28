#include <Wire.h>



// I2Cアドレス
#define DRV_ADR_R 0x64 // RightDRV8830のI2Cアドレス
#define DRV_ADR_L 0x60 // LeftDRV8830のI2Cアドレス
#define CTR_ADR 0x00 // CONTROLレジスタのサブアドレス
#define FLT_ADR 0x01 // FAULTレジスタのアドレス



// ブリッジ制御
#define M_STANBY B00 // スタンバイ
#define M_REVERSE B01 // 逆転
#define M_NORMAL B10 // 正転
#define M_BRAKE B11 // ブレーキ



// 電圧定義
#define MAX_VSET 0x3F // 5.06V
#define MIN_VSET 0x09 // 0.72V
#define R_VSET 0x1A // 2.09V
#define L_VSET 0x1A // 2.09V
#define CSPEED 0x23 //2.81V



//ラインセンサ
#include <SPI.h>
#define slaveSelectPin0 5
#define slaveSelectPin1 4
int analogData[16];
int flganalogData[16];
int oldanalogData[16];
int count =0;



int r_array[6];
int l_array[6];
boolean start = false;
char turn = 'n';




// 制御コマンド送信
int write_vset_r(byte vs, byte ctr) {
Wire.beginTransmission(DRV_ADR_R);
Wire.write(CTR_ADR);
Wire.write( ctr + (vs<<2) );
return Wire.endTransmission();
}



// 制御コマンド送信
int write_vset_l(byte vs, byte ctr) {
Wire.beginTransmission(DRV_ADR_L);
Wire.write(CTR_ADR);
Wire.write( ctr + (vs<<2) );
return Wire.endTransmission();
}



void setup() {
Wire.begin();
Serial.begin(115200);
pinMode(slaveSelectPin0, OUTPUT); //SS(10)を出力に設定
pinMode(slaveSelectPin1, OUTPUT);
SPI.setBitOrder(MSBFIRST); //MSBから送信
SPI.setClockDivider(SPI_CLOCK_DIV2); //クロック分周設定
SPI.setDataMode(SPI_MODE0); //SPIモード0
SPI.begin(); //SPI通信開始
}



void loop() {



get_adc(0);
Serial.print("ch1:R");
Serial.println(analogData[0]);
Serial.print("ch1:L");
Serial.println(analogData[1]);
get_adc(1);
Serial.print("ch2:R");
Serial.println(analogData[2]);
Serial.print("ch2:L");
Serial.println(analogData[3]);
get_adc(2);
Serial.print("ch3:R");
Serial.println(analogData[4]);
Serial.print("ch3:L");
Serial.println(analogData[5]);
get_adc(3);
Serial.print("ch4:R");
Serial.println(analogData[6]);
Serial.print("ch4:L");
Serial.println(analogData[7]);
get_adc(4);
Serial.print("ch5:R");
Serial.println(analogData[8]);
Serial.print("ch5:L");
Serial.println(analogData[9]);
get_adc(5);
Serial.print("ch6:R");
Serial.println(analogData[10]);
Serial.print("ch6:L");
Serial.println(analogData[11]);
get_adc(6);
Serial.print("ch7:R");
Serial.println(analogData[12]);
Serial.print("ch7:L");
Serial.println(analogData[13]);
get_adc(7);
Serial.print("ch8:R");
Serial.println(analogData[14]);
Serial.print("ch8:L");
Serial.println(analogData[15]);
delay(1);



if(turn != 'r' && analogData[0] != oldanalogData[0]){
//右回り(右センサ白線検知)
write_vset_r(MIN_VSET, M_NORMAL);
turn = 'r';
Serial.println("右停止");
delay(10);


}else if(turn != 'l' && analogData[1] != oldanalogData[1]){
//左回り(左センサ白線検知)
write_vset_l(MIN_VSET, M_NORMAL);
turn = 'l';
Serial.println("左停止");
delay(10);

}else if(turn == 'r' || turn == 'l' ){
if(analogData[0] == oldanalogData[0]){
write_vset_r(MAX_VSET, M_NORMAL);
turn = 't';
Serial.println("右再起動");
delay(10);
}else if(analogData[1] == oldanalogData[1]){
write_vset_l(MAX_VSET, M_NORMAL);
turn = 't';
Serial.println("左再起動");
delay(10);
}




}else if(start == false){
//定速スタート
start = true;
//モータドライバブリッジ制御をスタンバイ、最低電圧に設定
write_vset_r(MIN_VSET, M_STANBY);
write_vset_l(MIN_VSET, M_STANBY);
delay(10);
//定速運転開始
Serial.print("正転開始");
write_vset_r(MAX_VSET, M_NORMAL);
write_vset_l(MAX_VSET, M_NORMAL);
delay(10);
}
}



void get_adc(byte ch)
{
byte data[4] = {0, 0, 0, 0}; //SPI通信用変数




//------[ ADC0のデータを取得する ]------
digitalWrite(slaveSelectPin0, LOW); //CS LOW
SPI.transfer(0x01); //①スタートビット送信
data[0] = SPI.transfer((ch << 4) | 0x80); //②Single-ended チャンネル選択,ADC0のbit9,8取得
data[1] = SPI.transfer(0); //③ADC0のbit7～0取得
digitalWrite(slaveSelectPin0, HIGH); //CS HIGH





//------[ ADC1のデータを取得する ]------
digitalWrite(slaveSelectPin1, LOW); //CS LOW
SPI.transfer(0x01); //①スタートビット送信
data[2] = SPI.transfer((ch << 4) | 0x80); //②Single-ended チャンネル選択,ADC0のbit9,8取得
data[3] = SPI.transfer(0); //③ADC0のbit7～0取得
digitalWrite(slaveSelectPin1, HIGH); //CS HIGH



oldanalogData[count] = analogData[count];
analogData[count] = ((data[0] & 0x03) << 8) | data[1]; //ADC0
count++;
oldanalogData[count] = analogData[count];
analogData[count] = ((data[2] & 0x03) << 8) | data[3]; //ADC1
//return analogData[0];
count++;

if(count ==15){
count = 0;
}
}
