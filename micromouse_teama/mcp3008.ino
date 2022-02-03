/***
   File:mcp3008get_adc関数
   Author:太田
*/
void line_sensor() {
  for (int i = 0; i < 6; i++) {
    get_adc(i);

    l_analogData[i] = analogData[0];
    r_analogData[(5 - i)] = analogData[1];
  }
  //Serial.println(r_analogData[5]);


}
void get_adc(byte ch) {
  byte data[4] = {0, 0, 0, 0};                               //SPI通信用変数

  //------[ ADC0のデータを取得する ]------
  digitalWrite(slaveSelectPin0, LOW);       //CS LOW
  SPI.transfer(0x01);                       //①スタートビット送信
  data[0] = SPI.transfer((ch << 4) | 0x80);  //②Single-ended チャンネル選択,ADC0のbit9,8取得
  data[1] = SPI.transfer(0);                //③ADC0のbit7～0取得
  digitalWrite(slaveSelectPin0, HIGH);                  //CS HIGH
  // ------[ ADC1のデータを取得する ]------
  digitalWrite(slaveSelectPin1, LOW);       //CS LOW
  SPI.transfer(0x01);                       //①スタートビット送信
  data[2] = SPI.transfer((ch << 4) | 0x80);  //②Single-ended チャンネル選択,ADC0のbit9,8取得
  data[3] = SPI.transfer(0);                //③ADC0のbit7～0取得
  digitalWrite(slaveSelectPin1, HIGH);                  //CS HIGH
  analogData[0] = ((data[0] & 0x03) << 8) | data[1];  //ADC0
  analogData[1] = ((data[2] & 0x03) << 8) | data[3];  //ADC1
}
