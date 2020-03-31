

#define NUM_PINES 8
enum pines {PIN_1 = 2, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8};

/*Configuración de las entradas*/
void setup() {
  Serial.begin(115200);
  pinMode(PIN_1, INPUT);
  pinMode(PIN_2, INPUT);
  pinMode(PIN_3, INPUT);
  pinMode(PIN_4, INPUT);
  pinMode(PIN_5, INPUT);
  pinMode(PIN_6, INPUT);
  pinMode(PIN_7, INPUT);
  pinMode(PIN_8, INPUT);

}

void loop() {
  int pines[NUM_PINES];
  int valores[NUM_PINES] = {1, 2, 4, 8, 16, 32, 64, 128};
  int decimal = 0;


  for (int i = 0, j = 2; i < NUM_PINES; i++, j++)
    pines[i] = digitalRead(j);

  delay(10000);

  for (int i = 0, j = 7; i < NUM_PINES; i++, j--)
  {
    decimal += valores[j] * pines[i];
    Serial.print(pines[i]);
  }
  Serial.println("");

}
