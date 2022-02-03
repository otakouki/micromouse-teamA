// ラインセンサー
#include"include.h"

void setup() {
  Serial.begin(115200);                      //シリアル通信開始
  pinMode(slaveSelectPin0, OUTPUT);          //SS(10)を出力に設定
  pinMode(slaveSelectPin1, OUTPUT);
  SPI.setBitOrder(MSBFIRST);                //MSBから送信
  SPI.setClockDivider(SPI_CLOCK_DIV2);      //クロック分周設定
  SPI.setDataMode(SPI_MODE0);               //SPIモード0
  SPI.begin();//SPI通信開始
}

void loop() {
  //Serial.println(cnt++);
  line_sensor();
  delay(1000);
//  r_analogData[5] = 31;
//  l_analogData[5] = 31;
//  l_analogData[0] = 31;
  if (r_analogData[5] <= 100 || l_analogData[5] <= 100) {
    write_vset_r();
    //write_vset_l();
    
  }

  if(l_analogData[0] <= 100){
//  stop_r();
//  stop_l();
//  Wire.endTransmission();
  delay(2000);
  }

}
