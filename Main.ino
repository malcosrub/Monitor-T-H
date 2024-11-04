// Main.ino
// Programa principal del montaje de sensor DHT11
// Marcos Rubiano

#include <DHT.h>
#include <LiquidCrystal_I2C.h>


#define BackPin 0
#define NextPin 1
#define SDAPIN 2 // Reservado para SDA en Arduino Leonardo, A4 en Uno
#define SCLPIN 3 // Reservado para SCL en Arduino Leonardo, A5 en Uno
#define SensorPin 4
#define InteractPin 5

#define FanPin 12
#define HumidifierPin 13


#define dhtType DHT11

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(SensorPin, dhtType);

int Ready = 0;
int Humidifying = 0;
int Fanning = 0;

void setup(){
  lcd.init();
  lcd.backlight();
  pinMode(BackPin, INPUT);
  pinMode(NextPin, INPUT);

  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Monitor T&H");
  dht.begin();

  delay(1000);

  lcd.setCursor(0,0);
  lcd.print("Marcos Rubiano");
  lcd.setCursor(0,1);
  lcd.print("Daniel Sisa 1005");

  delay(1000);

  Ready = 1;
}

int Failed = 0;
int Mode = 0;
int nochange = 0;
int nochange1 = 0;

unsigned long heartbeat = 0;
unsigned long previousMillis = 0;
void loop(){
  if (Ready) {
    unsigned long currentMillis = millis();
    unsigned long interval = currentMillis - previousMillis;
    previousMillis = currentMillis;

    heartbeat = heartbeat + interval;
    if (heartbeat >= 5000){
      heartbeat = 0;
      Mode = Mode + 1;
    }

    if (Mode > 4)
    {
      Mode = 0;
    } else if (Mode < 0)
    {
      Mode = 4;
    }

    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    float temp_F = dht.readTemperature(true);
    float hic;
    float hic_F;
    if (isnan(hum) || isnan(temp) || isnan(temp_F)) {
      Failed = 1;
    } else {
      Failed = 0;
    float hic = dht.computeHeatIndex(temp, hum, false);
    float hic_F = dht.computeHeatIndex(temp_F, hum);
    }
    

    lcd.setCursor(0,0);
    switch (Mode) {
      case 0:
        lcd.print("Humedad:  ");
        lcd.print(round(hum));
        lcd.print("%    ");

        lcd.setCursor(0,1);

        if ((hum >= 0) && (hum <= 25)){
          lcd.print("Ambiente Seco    ");
          _Humidify(HIGH);
        } else if ((hum > 25) && (hum <= 65)){
          lcd.print("Ambiente Normal   ");
          _Humidify(LOW);
        } else if ((hum > 65)){
          lcd.print("Ambiente Húmedo   ");
          _Humidify(LOW);
        }
        
        
        break;
      case 1:

        lcd.print("Temperatura:      ");
        lcd.setCursor(0,1);

        lcd.print(round(temp));
        lcd.write(223);
        lcd.print("C  ");

        lcd.print(round(temp_F));
        lcd.write(223);
        lcd.print("F          ");

        break;
      case 2:
        lcd.print("Indice De Calor:   ");
        lcd.setCursor(0,1);

        lcd.print(round(hic));
        lcd.write(223);
        lcd.print("C  ");

        lcd.print(round(hic_F));
        lcd.write(223);
        lcd.print("F       ");
        break;
      case 3:
        lcd.print  ("Humidificador.  ");
        lcd.setCursor(0,1);
        if (Humidifying == 1){
          lcd.print("Encendido.      ");
        } else{
          lcd.print("Apagado.        ");
        }

        int intState = digitalRead(InteractPin);
        if (intState == HIGH){
          Humidifying = !Humidifying;
          Humidify((Humidifying==1) ? HIGH : LOW);
          delay(200);
        }
        break; 
      case 4:
        lcd.print("Ventilador.       ");
        lcd.setCursor(0,1);
        if (Fanning == 1){
          lcd.print("Encendido.      ");
        } else{
          lcd.print("Apagado.        ");
        }

        int intState1 = digitalRead(InteractPin);
        if (intState1 == HIGH){
          Fanning = !Fanning;
          Fanify((Fanning==1) ? HIGH : LOW);
          delay(200);
        }
        break;
    }

    int nextState = digitalRead(NextPin);
    int prevState = digitalRead(BackPin);

    if (nextState == HIGH){
      Mode = Mode + 1;
      heartbeat = 0;
      delay(200);
    }
    if (prevState == HIGH){
      Mode = Mode - 1;
      heartbeat = 0;
      delay(200);
    }
    
  } else {

  }
  
}



void Humidify(int state){
  if (state == HIGH){
    digitalWrite(HumidifierPin, HIGH);
    Humidifying = 1;
  } else {
    digitalWrite(HumidifierPin, LOW);
    Humidifying = 0;
  }
}

void _Humidify(int state){
  if (state == HIGH){
    if (nochange == 0){
      digitalWrite(HumidifierPin, HIGH);
      Humidifying = 1;
      nochange = 1;
    }
  } else {
    if (nochange == 1){
      digitalWrite(HumidifierPin, LOW);
      Humidifying = 0;
      nochange = 0;
    }
  }
}

void Fanify(int state){
  if (state == HIGH){
    digitalWrite(FanPin, HIGH);
    Fanning = 1;
  } else {
    digitalWrite(FanPin, LOW);
    Fanning = 0;
  }
}

void _Fanify(int state){
  if (state == HIGH){
    if (nochange1 == 0){
      digitalWrite(FanPin, HIGH);
      Fanning = 1;
      nochange1 = 1;
    }
  } else {
    if (nochange1 == 1){
      digitalWrite(FanPin, LOW);
      Fanning = 0;
      nochange1 = 0;
    }
  }
}
