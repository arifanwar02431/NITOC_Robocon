// 先輩から受け継がれたものらしい
// 不要な部分の削除とかちょっと手を加えてあります

#include "mbed.h"

DigitalOut Dig[4] = {D2, D4, D7, D8};
PwmOut P[4] = {D10, D5, D6, D9};
// RawSerial PC(USBTX,USBRX);
// RawSerial SBDBT(PC_12, PD_2, 2400);

void Config(void);
inline void Move(double X_move, double Y_move, double Rotate);      //Move関数のプロトタイプ宣言(xはx軸方向への動作、yはy軸方向への動作、zは回転動作を示す)
// inline void PS3Data(void);

double motor[4];        //各モーターの制御状態を管理するため、double型で変数motorを宣言
double Rotate;

int PS3[7];

int main() {
    int i;
    Config();
    while(true) {
        // ここからは試走用のゴリゴリプログラムなので使用用途に合わせて適宜書き換えて下さい
        Move(0, 0, 0);      //停止状態
        wait_ms(1000);      //1000㍉秒(1秒)待機
        Move(1.0, 0, 0);        //x方向：右方に全速移動(速度1)
        wait_ms(1000);
        Move(0, 1.0, 0);        //y方向：前方に全速移動(速度1)
        wait_ms(1000);
        Move(-1.0, 0, 0);       //-x方向：左方に全速移動(速度1)
        wait_ms(1000);
        Move(0, -1.0, 0);       //-y方向：後方に全速移動(速度1)
        wait_ms(1000);
        Move(0.5, 0.5, 0);      //x+y方向：右斜め前方に半速移動(速度0.7：三平方の定理より導出)
        wait_ms(1000);
        Move(0.5, -0.5, 0);     //x-y方向：右斜め後方に半速移動(速度0.7：三平方の定理より導出)
        wait_ms(1000);
        Move(-0.5, -0.5, 0);        //-x-y方向：左斜め後方に半速移動(速度0.7：三平方の定理より導出)
        wait_ms(1000);
        Move(-0.5, 0.5, 0);     //-x+y方向：左斜め前方に半速移動(速度0.7：三平方の定理より導出)
        wait_ms(1000);
        Move(0, 0, 0);      //停止状態
        wait_ms(1000);
        Move(0, 0, 1.0);        //正回転：全速右回転(速度1)
        wait_ms(1000);
        Move(0, 0, 0);      //停止状態
        wait_ms(1000);
        Move(0, 0, -1.0);       //逆回転：全速左回転(速度1)
        wait_ms(1000);
    }
}

inline void Move(double X_move, double Y_move, double Rotate) {     //Move関数宣言
    int i;      // for文用の変数i
    if(Rotate != 0) {       // 回転指示であるか？(zが0以外の値であるか？)
        // 回転指示は全モーターを同じ方向へ回転させれば良いだけである。(全モーターを右方向に回せば右回転が出来る)
        motor[0] = Rotate;
        motor[1] = Rotate;
        motor[2] = Rotate;
        motor[3] = Rotate;
    } else {      // 回転指示でない場合(zが0である)
        //ここは各モーターの速度制御を調整するが、理解が困難なので各自図などを描いて要領を得ると良い。
        motor[0] = (X_move + Y_move) / 2.0;     // 左方前側のモーター。x方向、y方向共に正回転させると正方向に動く。
        motor[1] = (X_move - Y_move) / 2.0;     // 右方前側のモーター。x方向は正回転させると、y方向は逆回転させると正方向に動く。
        motor[2] = (-X_move + Y_move) / 2.0;    // 左方後側のモーター。x方向は逆回転させると、y方向は正回転させると正方向に動く。
        motor[3] = (-X_move - Y_move) / 2.0;    // 右方後側のモーター。x方向、y方向共に逆回転させると正方向に動く。
    }

    PC.printf("%lf, %lf, %lf, %lf\r\n\r\n\r\n", motor[0], motor[1], motor[2], motor[3]);

    for(i = 0; i < 4; i++) {      // 各モーター制御用のfor文
        if(motor[i] >= 0) {
            Dig[i] = 0;     // モーターの回転速度が正の場合、Dig(モーターの回転方向を制御するデジタル信号変数)を0(正回転)とする
        } else {
            Dig[i] = 1;     // モーターの回転速度が負の場合、Digを1(逆回転)とする
        }
        P[i] = fabs(motor[i]);      // 回転速度をPWM信号変数Pに代入。PWMの値域は0~1なので、回転速度指定変数motorの絶対値を取る。(fabsは絶対値の関数)
    }
}

// Serial通信(UART)とPWM周期の設定
void Config() {
    P[0].period_us(1432);
    P[1].period_us(1432);
    P[2].period_us(1432);
    P[3].period_us(1432);
    // SBDBT.attach(&PS3Data, Serial::RxIrq);       //受信割込みの時にPS3Data関数を呼び出すよう設定
}

/*
//PS3コントローラーからの入力処理
inline void PS3Data() {
    //生データ受け取り
    int SBDBT_Data = SBDBT.getc();
    static int bits = 0;

    if(SBDBT_Data == 128) {
        bits = 0;
    }

    //各配列にデータを格納
    if (SBDBT_Data >= 0) {
        PS3[bits] = SBDBT_Data;

        if (bits == 7) {
            bits = 0;
        } else {
            bits++;
        }
    }
}
*/