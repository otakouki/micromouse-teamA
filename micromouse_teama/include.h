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

// ラインセンサー
#include <SPI.h>
#define slaveSelectPin0 5
#define slaveSelectPin1 4

static int analogData[16];
static int oldanalogData[16];
static int l_analogData[6];
static int r_analogData[6];

boolean start = false;
char turn = 'n';
