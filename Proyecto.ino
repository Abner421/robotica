#include <String.h>

/*****    DECLARACIONES GENERALES   *****/
int PWM_base;
int PWM_brazo;
int PWM_terminal;

int baseHorario = 11;
int baseAntihorario = 9;

int brazoHorario = 22;
int brazoAntihorario = 23;

int terminalHorario = 24;
int terminalAntihorario = 25;

int inicioBase = 40;
int finBase = 41;
int inicioBrazo = 42;
int finBrazo = 43;
int inicioTerminal = 44;
int finTerminal = 45;

/*****    CONTADORES    *****/
int cont_base = 0;
int cont_brazo = 0;
int cont_terminal = 0;

/*****    ARTICULACIONES Y MOVIMIENTOS   *****/
int q1 = 0;
int q2 = 0;
int q3 = 0;

int m1 = 0;
int m2 = 0;
int m3 = 0;

/*****    POSICIONES    *****/
int pos_base = 0;
int pos_brazo = 0;
int pos_terminal = 0;

/*****    VARIABLES GLOBALES    *****/
String cad = "";

void setup() {
  Serial.begin(9600);

  //INTERRUPCIONES
  attachInterrupt(0, base, CHANGE);
  attachInterrupt(1, brazo, CHANGE);
  attachInterrupt(2, terminal, CHANGE);

  //DECLARACIÓN MOVIMIENTOS
  pinMode(baseHorario, OUTPUT);
  pinMode(baseAntihorario, OUTPUT);
  pinMode(brazoHorario, OUTPUT);
  pinMode(brazoAntihorario, OUTPUT);
  pinMode(terminalHorario, OUTPUT);
  pinMode(terminalAntihorario, OUTPUT);

  //DECLARACIÓN COMIENZO Y FINES CARRERA
  pinMode(inicioBase, INPUT);
  pinMode(finBase, INPUT);
  pinMode(inicioBrazo, INPUT);
  pinMode(finBrazo, INPUT);
  pinMode(inicioTerminal, INPUT);
  pinMode(finTerminal, INPUT);
}

void loop() {
  if(Serial.available() > 0){
    inicializar();
    
    cad = Serial.readString();
    Info(cad);
    //Motor Base
    if(m1>0){
      Serial.println("Moviendo Base sentido antihorario");
      mueveBaseAntihorario(m1);
    }else{
      Serial.println("Moviendo Base sentido horario");
      mueveBaseHorario(-1*m1);
    }

    //Motor Brazo
    if(m2>0){
      Serial.println("Moviendo Brazo sentido antihorario");
      mueveBrazoAntihorario(m2);
    }else{
      Serial.println("Moviendo Brazo sentido horario");
      mueveBrazoHorario(-1*m2);
    }

    //Motor Terminal
    if(m3>0){
      Serial.println("Moviendo Terminal sentido antihorario");
      mueveTerminalAntihorario(m3);
    }else{
      Serial.println("Moviendo Terminal sentido horario");
      mueveTerminalHorario(-1*m3);
    }
  }
}

void mueveBaseAntihorario(int grados){
  cont_base = 0;
  delay(420);
  while(grados > cont_base){
    if(digitalRead(finBase)==HIGH){
      cont_base = grados;
    }else{
      digitalWrite(baseHorario, HIGH); //REVISAR
      digitalWrite(baseAntihorario, LOW);
    }
  }
  stopBase();
}

void mueveBaseHorario(int grados){
  cont_base = 0;
  delay(420);
  while(grados > cont_base){
    if(digitalRead(inicioBase)==HIGH){
      cont_base = grados;
    }else{
      digitalWrite(baseAntihorario, HIGH); //REVISAR
      digitalWrite(baseHorario, LOW);
    }
  }
  stopBase();
}

void stopBase(){
  digitalWrite(baseHorario, LOW);
  digitalWrite(baseAntihorario, LOW);
}

void mueveBrazoAntihorario(int grados){
  cont_brazo = 0;
  delay(420);
  while(grados > cont_brazo){
    if(digitalRead(finBrazo)==HIGH){
      cont_brazo = grados;
    }else{
      digitalWrite(brazoAntihorario, HIGH);
      digitalWrite(brazoHorario, LOW); 
    }
  }
  stopBrazo();
}

void mueveBrazoHorario(int grados){
  cont_brazo = 0;
  delay(420);
  while(grados > cont_brazo){
    if(digitalRead(finBrazo)==HIGH){
      cont_brazo = grados;
    }else{
      digitalWrite(brazoHorario, HIGH);
      digitalWrite(brazoAntihorario, LOW); 
    }
  }
  stopBrazo();
}

void stopBrazo(){
  digitalWrite(brazoAntihorario, LOW);
  digitalWrite(brazoHorario, LOW);
}

void mueveTerminalAntihorario(int grados){
  cont_terminal = 0;
  delay(420);
  while(grados > cont_terminal){
    if(digitalRead(finTerminal)==HIGH){
      cont_terminal = grados;
    }else{
      digitalWrite(terminalHorario, HIGH);
      digitalWrite(terminalAntihorario, LOW);
    }
  }
  stopTerminal();
}

void mueveTerminalHorario(int grados){
  cont_terminal = 0;
  delay(420);
  while(grados > cont_terminal){
    if(digitalRead(finTerminal)==HIGH){
      cont_terminal = grados;
    }else{
      digitalWrite(terminalAntihorario, HIGH);
      digitalWrite(terminalHorario, LOW);
    }
  }
  stopTerminal();
}

void stopTerminal(){
  digitalWrite(terminalAntihorario, LOW);
  digitalWrite(terminalHorario, LOW);
}

void base(){
  cont_base++;
  Serial.println("BASE");
}

void brazo(){
  cont_brazo++;
  Serial.println("BRAZO");
}

void terminal(){
  cont_terminal++;
  Serial.println("TERMINAL");
}

void Info(String cad){
  String aux = "";
  int m[4];
  char str[25]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
  cad.toCharArray(str, cad.length()+1);
  int j = 0;
  int k = 0;

  while(str[j]!='\0' && j<cad.length()+1){
    if(str[j]==','){
      m[k]=aux.toInt();
      k++;
      aux="";
    }else{
      aux=aux+str[j];
    }
    j++;
  }
  m[3]=aux.toInt();
  m1 = m[0];
  m2 = m[1];
  m3 = m[2];
}

void inicializar(){
  // METODOS PARA INICIALIZAR ROBOT
}