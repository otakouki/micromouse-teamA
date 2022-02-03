
void write_vset_r() {
  
  Wire.beginTransmission(DRV_ADR_R);//I2Cスレーブ「Arduino Uno」のデータ送信開始
  Wire.write(CTR_ADR);//コントロール
  Wire.write(0x3F);//正転0.48V
  
  Serial.println(Wire.endTransmission(true));//I2Cスレーブ「Arduino Uno」のデータ送信終了
  
  delay(10);//10msec待機
  Serial.println("R正転");
}

// 制御コマンド送信
void write_vset_l() {
  Wire.beginTransmission(DRV_ADR_L);
  Wire.write(CTR_ADR);
  Wire.write(0x3F);
  Wire.endTransmission(true);

  delay(10);
  Serial.println("L正転");
}

void stop_r(){
  Wire.beginTransmission(DRV_ADR_R);//I2Cスレーブ「Arduino Uno」のデータ送信開始
  Wire.write(CTR_ADR);//コントロール
  Wire.write(0x09);//ブレーキ
  Wire.endTransmission(true);//I2Cスレーブ「Arduino Uno」のデータ送信終了
  Serial.println("Rstop");
}

void stop_l(){
  Wire.beginTransmission(DRV_ADR_L);//I2Cスレーブ「Arduino Uno」のデータ送信開始
  Wire.write(CTR_ADR);//コントロール
  Wire.write(0x09);//ブレーキ
  Wire.endTransmission(true);//I2Cスレーブ「Arduino Uno」のデータ送信終了
  Serial.println("Lstop");
}
