//#include "MotorEncoder_Controller.h"
#include "EncoderStepCounter.h"

class MotorController{
  public:
      EncoderStepCounter *Right_Encoder;
      EncoderStepCounter *Left_Encoder;
      //EncoderStepCounter Right_Encoder( 36 , 39 );
      //EncoderStepCounter Left_Encoder( EncoderPin_C, EncoderPin_D );
    //MotorEncoder Right_Encoder( IntPin_A , IntPin_B );
    //MotorEncoder Left_Encoder( IntPin_C, IntPin_D );
      MotorController( ){
        
      }
      
      MotorController( EncoderStepCounter &Right_Enc , EncoderStepCounter &Left_Enc ){
        Right_Encoder = &Right_Enc;
        Left_Encoder = &Left_Enc;
      }

      void setRightEncoder( EncoderStepCounter &Right_Enc ){
        Right_Encoder = &Right_Enc;
        Right_Encoder->begin();
      }

      void setLeftEncoder( EncoderStepCounter &Right_Enc ){
        Left_Encoder = &Right_Enc;
        Left_Encoder->begin();
      }
      
      void init(){
        
        //attachInterrupt(EncoderPin_A, Right_Encoder->tick() , CHANGE);
        //attachInterrupt(EncoderPin_B, Right_Encoder->tick() , CHANGE);
        //attachInterrupt(IntPin_B, interrupt, CHANGE);
      }
};


void MoverDch (bool DerAvz, bool DerRet, int DSpeed){
  digitalWrite(DER_AVZ, DerAvz);
 digitalWrite(DER_RET, DerRet);
 ledcWrite (DER_PWM_Ch, DSpeed);
}
void MoverIzq(bool IzqAvz, bool IzqRet, int ISpeed){
  digitalWrite(IZQ_AVZ, IzqAvz);
 digitalWrite(IZQ_RET, IzqRet);
 ledcWrite (IZQ_PWM_Ch, ISpeed);
}

void giraDch () {
  MoverDch ( 0, 1, 400);
  MoverIzq ( 1, 0, 400);
  delay (150);
}
void giraIzq () {
  MoverDch ( 1, 0, 400);
  MoverIzq ( 0, 1, 400);
  delay (150);
}
void paroMotores () {
  MoverDch ( 0, 0, 0);
  MoverIzq ( 0, 0, 0);
}

void salidaMotores () {
    if (Lspeed < 0) {
    digitalWrite(IZQ_AVZ, LOW);
    digitalWrite(IZQ_RET, HIGH);
  } else {
    digitalWrite(IZQ_AVZ, HIGH);
    digitalWrite(IZQ_RET, LOW);
  }
  if (Rspeed < 0) {
    digitalWrite(DER_AVZ, LOW);
    digitalWrite(DER_RET, HIGH);
  } else {
    digitalWrite(DER_AVZ, HIGH);
    digitalWrite(DER_RET, LOW);
  }
  Lspeed = abs(Lspeed);  if (Lspeed < 30) Lspeed = 0;
  Rspeed = abs(Rspeed);  if (Rspeed < 30) Rspeed = 0;
  Lspeed = constrain (Lspeed, 0, 1023);
  Rspeed = constrain (Rspeed, 0, 1023);
  ledcWrite (IZQ_PWM_Ch, Lspeed);
  ledcWrite (DER_PWM_Ch, Rspeed);
  // Serial.print ("L  "); Serial.print (Lspeed); Serial.print ("R  "); Serial.println(Rspeed);
}

void xyAdiferencial()
{
  int baseSpeed;
  int turnDelta;

  // velocidad base
  baseSpeed = map ( pad_y, MIN_RAW_ADC, MAX_RAW_ADC, MAX_SPEED_SETTING, MIN_SPEED_SETTING );
  // valor diferencial para girar
  turnDelta = map ( pad_x, MIN_RAW_ADC, MAX_RAW_ADC, MIN_TURN_DELTA, MAX_TURN_DELTA );

  Lspeed = baseSpeed + turnDelta;
  Rspeed = baseSpeed - turnDelta;

}
