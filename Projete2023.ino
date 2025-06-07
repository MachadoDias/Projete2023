#include <LiquidCrystal.h>
#include <Keypad.h>
#include <rdm6300.h>

LiquidCrystal lcd(22, 23, 24, 25, A9, A8);

char Letter1 = 'C', Letter2 = 'U', Letter3 = 'S', Letter4 = 'T', Letter5 = 'O', Letter6 = 'A', Letter7 = 'A', Letter8 = 'A', Letter9 = 'A', Letter10 = 'A', *Letter, *Letra, s1 = 'A', s2 = 'A', s3 = 'A', s4 = 'A', s5 = 'A';

char adivinhar[5], Letter11 = 'A', Letter12 = 'A', Letter13 = 'A', Letter14 = 'A', Letter15 = 'A', Letter16 = 'A', Letter17 = 'A', Letter18 = 'A', Letter19 = 'A', Letter20 = 'A';

char *adivinhar1[5] = { &Letter6, &Letter7, &Letter8, &Letter9, &Letter10 };

char montar[5];

int cont = 1, ntentativa = 5, tentativa = 0, iniciar = 0, certo = 0, certo1 = 0, volume = 7, jogo = 1, comecar = 0, sensoratual = 1, pass = 1, bp = 0;

bool botao = false, showText = false, executarLoop = false, executar, passar = false, passar1 = true, jogadores = false, buz = false, S1 = false, S2 = false, S5 = true;

unsigned long previousTime = 0, tempoanterior = 0, tempo = 0, cartaoLido, Cartao, R;

int som = 25, Sensor = 1, US;

const int trocasensor = 250, interval = 600, RDM6300_RX_PIN = 13, A = 44, B = 45, C = 46, v1 = 28, v2 = 29, v3 = 30, v4 = 31, v5 = 32, verde1 = 33, verde2 = 34, verde3 = 35, verde4 = 10, verde5 = 37, a1 = 38, a2 = 39, a3 = 40, a4 = 41, a5 = 42;

String leds = "";

int vermelhos[5] = { v1, v2, v3, v4, v5 };
int verdes[5] = { verde1, verde2, verde3, verde4, verde5 };
int azuis[5] = { a1, a2, a3, a4, a5 };

byte voluminho[8] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
};

byte seta[8] = {
  B00000,
  B00100,
  B01100,
  B11111,
  B11111,
  B01100,
  B00100,
  B00000
};

static int posicao = 0;

String mensagem = "                Jogo de Adivinhacao de Palavras ";
String mensagem3 = "               Voce perdeu ";
String mensagem2 = "               Tentativa ";
String mensagem22 = "               Tentativa ";
String mensagem4 = "               Voce ganhou ";

const byte LINHAS = 1;
const byte COLUNAS = 5;

char Keys[LINHAS][COLUNAS] = {
  { '1', '2', '3', '4', '5' },
};

byte rowPins[LINHAS] = { 7 };
byte colPins[COLUNAS] = { 6, 5, 4, 2, 3 };

Keypad myKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, LINHAS, COLUNAS);
char Key = myKeypad.getKey();
Rdm6300 rdm6300;

void canal(int c, int b, int a) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
}

void EscolhaSensor(int sensor) {
  switch (sensor) {
    case 1:
      canal(0, 0, 0);
      break;
    case 2:
      canal(0, 0, 1);
      break;
    case 3:
      canal(0, 1, 0);
      break;
    case 4:
      canal(0, 1, 1);
      break;
    case 5:
      canal(1, 0, 0);
      break;
    default:
      break;
  }
}

void DefinirLetra(char *Letra) {
  if (rdm6300.get_new_tag_id()) {
    switch (sensoratual) {
      case 1:
        Serial.println("sensor 1");
        break;
      case 2:
        Serial.println("sensor 2");
        break;
      case 3:
        Serial.println("sensor 3");
        break;
      case 4:
        Serial.println("sensor 4");
        break;
      case 5:
        Serial.println("sensor 5");
        break;
    }
    S5 = true;
    cartaoLido = rdm6300.get_tag_id();
    Serial.println(cartaoLido, HEX);
    if (cont != 26) {
      switch (sensoratual) {
        case 1:
          if (s1 != Letter6) {
            buzzer(som);
            s1 = Letter6;
            break;
          }
        case 2:
          if (s2 != Letter7) {
            buzzer(som);
            s2 = Letter7;
            break;
          }
        case 3:
          if (s3 != Letter8) {
            buzzer(som);
            s3 = Letter8;
            break;
          }
        case 4:
          if (s4 != Letter9) {
            buzzer(som);
            s4 = Letter9;
            break;
          }
        case 5:
          if (s5 != Letter10) {
            buzzer(som);
            s5 = Letter10;
            break;
          }
      }
    }

    if (cartaoLido == 0x1E1274 || cartaoLido == 0xBA52EA) {
      *Letra = 'A';
    } else if (cartaoLido == 0xBAEF55) {
      *Letra = 'B';
    } else if (cartaoLido == 0x1D6DC6) {
      *Letra = 'C';
    } else if (cartaoLido == 0x1D6DE1) {
      *Letra = 'D';
    } else if (cartaoLido == 0x1E0A25 || cartaoLido == 0x1E073C) {
      *Letra = 'E';
    } else if (cartaoLido == 0x1D6DE0) {
      *Letra = 'F';
    } else if (cartaoLido == 0x1E5820) {
      *Letra = 'G';
    } else if (cartaoLido == 0x1D5AB0) {
      *Letra = 'H';
    } else if (cartaoLido == 0x1E1117 || cartaoLido == 0x1DBD84) {
      *Letra = 'I';
    } else if (cartaoLido == 0xBAB28F) {
      *Letra = 'J';
    } else if (cartaoLido == 0x1D9B39) {
      *Letra = 'K';
    } else if (cartaoLido == 0x1E1275) {
      *Letra = 'L';
    } else if (cartaoLido == 0x1E581B) {
      *Letra = 'M';
    } else if (cartaoLido == 0x1D5D9B) {
      *Letra = 'N';
    } else if (cartaoLido == 0xBA06E3 || cartaoLido == 0xBA06EC) {
      *Letra = 'O';
    } else if (cartaoLido == 0xBAC9C1) {
      *Letra = 'P';
    } else if (cartaoLido == 0xBA06ED) {
      *Letra = 'Q';
    } else if (cartaoLido == 0x1DD34D || cartaoLido == 0x1E4892) {
      *Letra = 'R';
    } else if (cartaoLido == 0x1E548A) {
      *Letra = 'S';
    } else if (cartaoLido == 0x1D5D97) {
      *Letra = 'T';
    } else if (cartaoLido == 0x1D6DE9 || cartaoLido == 0x1DE55B) {
      *Letra = 'U';
    } else if (cartaoLido == 0x1E197B) {
      *Letra = 'V';
    } else if (cartaoLido == 0x1E110E) {
      *Letra = 'W';
    } else if (cartaoLido == 0x1E128B) {
      *Letra = 'X';
    } else if (cartaoLido == 0x1E581A) {
      *Letra = 'Y';
    } else if (cartaoLido == 0x1D67AE) {
      *Letra = 'Z';
    } else if (cartaoLido == 0x97F375) {
      Letter6 = 'A';
      Letter7 = 'R';
      Letter8 = 'E';
      Letter9 = 'I';
      Letter10 = 'A';
    } else if (cartaoLido == 0x47BE52) {
      Letter6 = 'C';
      Letter7 = 'U';
      Letter8 = 'L';
      Letter9 = 'T';
      Letter10 = 'O';
    } else if (cartaoLido == 0x990F5F) {
      Letter6 = 'C';
      Letter7 = 'U';
      Letter8 = 'S';
      Letter9 = 'T';
      Letter10 = 'O';
    } else if (cartaoLido == 0x474E78) {
      Letter6 = 'L';
      Letter7 = 'O';
      Letter8 = 'J';
      Letter9 = 'A';
      Letter10 = 'S';
    } else if (cartaoLido == 0x597D7B) {
      Letter6 = 'C';
      Letter7 = 'U';
      Letter8 = 'S';
      Letter9 = 'T';
      Letter10 = 'O';
    }
  }
}

void al(char *Letter) {
  char Key = myKeypad.getKey();
  unsigned long current = millis();
  if (current - tempo >= 500) {
    tempo = current;
    showText = !showText;
  }
  if (showText) {
    lcd.setCursor(pass, 1);
    lcd.print(" ");
  } else {
    lcd.setCursor(pass, 1);
    lcd.print(*Letter);
  }
  if (Key) {
    if (Key == '4' && cont != 2 && cont != 10 || Key == '4' && S1) {
      lcd.setCursor(pass, 1);
      lcd.print(*Letter);
      if (S1 && iniciar != 1) {
        Serial.print("ola");
        iniciar--;
        pass = pass - 1;
      } else if (!S1) {
        cont--;
        pass = pass - 3;
      }
      tempo = current;
    }
    else if (Key == '2') {
      Serial.print("ola");
      (*Letter)++;
      showText = false;
      tempo = current;
    } else if (Key == '3') {
      (*Letter)--;
      showText = false;
      tempo = current;
    } else if (Key == '5' && cont != 6 && cont != 14) {
      tempo = current;
      lcd.setCursor(pass, 1);
      lcd.print(*Letter);
      if (S1 && iniciar != 5) {
        Serial.print("ola");
        iniciar++;
        pass = pass + 1;
      } else if (!S1) {
        cont++;
        pass = pass + 3;
      }
    }
    else if (Key == '1' && S5 == true) {
      S5 = false;
      if (!S1) {
        cont = 7;
      } else if (S1 && S2) {
        cont = 15;
      }
    }
    if (*Letter > 'Z') {
      *Letter = 'A';
    }
    if (*Letter < 'A') {
      *Letter = 'Z';
    }
  }
}

bool comparar(char *letra, char *letra2) {
  if (*letra == *letra2) {
    leds += "g";
    certo++;
    return 1;
  } else {
    for (int i = 0; i < 5; i++) {
      if (montar[i] != adivinhar[i] && *letra == montar[i]) {
        leds += "b";
        montar[i] = '0';
        return 0;
      }
    }
    leds += "r";
    return 0;
  }
}

void buzzer(int som) {
  if (buz) {
    analogWrite(12, som);
  } else {
    digitalWrite(12, 0);
  }
}

void setup() {
  rdm6300.begin(RDM6300_RX_PIN);
  for (int i = 26; i < 52; i++) {

    pinMode(i, OUTPUT);
  }
  pinMode(50, INPUT_PULLUP);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  for (int i = 0; i < 5; i++) {
    digitalWrite(vermelhos[i], 0);
    digitalWrite(verdes[i], 0);
    digitalWrite(azuis[i], 0);
  }
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.createChar(1, voluminho);
  lcd.createChar(2, seta);

  while (iniciar == 0) {
    digitalWrite(12, 0);
    char Key = myKeypad.getKey();
    if (Key) {
      iniciar++;
    }
    lcd.setCursor(0, 0);
    lcd.print("Bem Vindo ao JAP");
    unsigned long currentTime = millis();
    if (currentTime - previousTime >= interval) {
      lcd.setCursor(0, 1);
      lcd.print(mensagem.substring(posicao, posicao + 16));
      posicao++;
      if (posicao >= mensagem.length()) {
        posicao = 0;
      }
      previousTime = currentTime;
    }
  }
  lcd.clear();

  while (comecar == 0) {
    char Key = myKeypad.getKey();
    unsigned long Time = millis();
    if (Time - previousTime >= 100) {
      buz = false;
      buzzer(som);
    }
    unsigned long currentTime = millis();
    if (Key) {
      buz = true;
      buzzer(som);
      unsigned long Time = millis();
      if (Time - previousTime >= 100) {
        previousTime = Time;
      }
      showText = true;
      previousTime = currentTime;
      lcd.clear();
      if (Key == '2') {
        if (cont < 3 && cont > 1 && executarLoop || cont == 0) {
          passar = !passar;
          passar1 = !passar1;
        }
        if (jogo > 0 && cont < 3) {
          executarLoop = true;
          cont++;
        }
      }
      if (Key == '1') {
        if (jogo == 1 && cont == 1) {
          cont = 1;
          executarLoop = false;
          comecar++;
        }
        if ((cont == 2) && volume < 15) {
          volume++;
          som += 25;
        }
        if (cont == 3 && ntentativa < 10) {
          ntentativa++;
        }
      }
      if (Key == '3') {
        if (Key == '3' && cont != 1) {
          if (cont != 4 && !executarLoop || jogo == 2) {
            passar = !passar;
            passar1 = !passar1;
          }
          if ((jogo == 1 && cont > 1 && jogo)) {
            executarLoop = false;
            cont--;
          }
        }
      }
      if (Key == '4') {
        if (jogo == 1) {
          if (cont == 2 && volume > 6) {
            lcd.setCursor(volume, passar);
            lcd.print(" ");
            volume--;
            som -= 25;
          }
          if (cont == 3 && ntentativa > 2) {
            ntentativa--;
            if (ntentativa == 9) {
              lcd.setCursor(14, passar);
              lcd.print("  ");
            }
          }
        }
      }
      if (Key == '5') {
        if (cont == 1) {
          cont = 1;
          executarLoop = false;
          comecar++;
        }
        if ((cont == 2) && volume < 15) {
          volume++;
          som += 25;
        }
        if (cont == 3 && ntentativa < 10) {
          ntentativa++;
        }
      }
      Serial.println(cont);
    }
    if (jogo == 1) {
      if (cont == 1 || cont == 2 && executarLoop) {
        lcd.setCursor(0, passar);
        lcd.print("Comecar");
      }
      if (cont < 3 || cont == 3 && executarLoop) {
        lcd.setCursor(0, passar1);
        lcd.print("Volume");
        if (volume >= 7) {
          for (int i = 6; volume - i != 0; i++) {
            lcd.setCursor(i + 1, passar1);
            lcd.write(1);
          }
        }
      }
      if (cont > 2 && cont < 5 || cont == 2 && !executarLoop) {
        lcd.setCursor(0, passar);
        lcd.print("Tentativas ");
        lcd.print(ntentativa);
      }
    }
    if (currentTime - previousTime >= interval) {
      previousTime = currentTime;
      showText = !showText;
    }
    if (jogo == 1) {
      if (cont == 2) {
        lcd.setCursor(volume + 2, executarLoop);
      }
      if (cont == 3) {
        if (ntentativa == 10) {
          lcd.setCursor(14, executarLoop);
        } else {
          lcd.setCursor(13, executarLoop);
        }
      }
      if (cont == 1) {
        lcd.setCursor(8, executarLoop);
      }
      lcd.write(2);
    }
  }
}
void loop() {
  unsigned long Time = millis();
  if (bp == 5000) {
    asm volatile("  jmp 0");
  }
  if (bp != 0 && Time - R >= 5000) {
    bp = 0;
    R = Time;
  }
  if (digitalRead(50) == 0) {
    bp++;
  }
  if (Time - previousTime >= 500) {
    digitalWrite(12, 0);
    previousTime = Time;
  }
  unsigned long currentTime = millis();
  if (cont == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Defina a palavra");
    lcd.setCursor(4, 1);
    pass = 1;
    lcd.print("U  S  T  O");
    lcd.setCursor(pass, 1);
    lcd.print(Letter1);
    delay(50);
    cont++;
  }
  if (cont == 7) {
    char Key = myKeypad.getKey();
    if (Key) {
      if (Key == '5' || Key == '1') {
        if (tentativa > 0) {
          cont = 15;
        } else if (tentativa == 0 && jogadores == false) {
          Serial.print(jogadores);
          cont++;
        }
      }
      if (Key == '4') {
        if (tentativa == 0) {
          Letter1 = 'A';
          Letter2 = 'A';
          Letter3 = 'A';
          Letter4 = 'A';
          Letter5 = 'A';
          cont = 1;
        } else {
          Letter6 = 'A';
          Letter7 = 'A';
          Letter8 = 'A';
          Letter9 = 'A';
          Letter10 = 'A';
          cont = 9;
        }
      }
    }
    lcd.setCursor(0, 0);
    lcd.print("confirmar       ");
    lcd.setCursor(0, 1);
    lcd.print("palavra ");
    delay(50);
    lcd.setCursor(10, 1);
    if (tentativa == 0) {
      lcd.print(Letter1);
      lcd.print(Letter2);
      lcd.print(Letter3);
      lcd.print(Letter4);
      lcd.print(Letter5);
    } else {
      lcd.print(Letter6);
      lcd.print(Letter7);
      lcd.print(Letter8);
      lcd.print(Letter9);
      lcd.print(Letter10);
    }
    posicao = 0;
  }
  if (cont == 8) {
    if (!executarLoop) {
      posicao = 0;
      tentativa++;
      lcd.clear();
      mensagem2 = mensagem2 + String(tentativa) + (" ");
      executarLoop = true;
    }
    lcd.setCursor(0, 0);
    lcd.print(mensagem2.substring(posicao, posicao + 16));
    posicao++;
    delay(300);
    if (posicao == 14) {
      delay(1500);
      cont = 10;
    }
  }
  if (cont == 15) {
    montar[0] = Letter1;
    montar[1] = Letter2;
    montar[2] = Letter3;
    montar[3] = Letter4;
    montar[4] = Letter5;
    adivinhar[0] = Letter6;
    adivinhar[1] = Letter7;
    adivinhar[2] = Letter8;
    adivinhar[3] = Letter9;
    adivinhar[4] = Letter10;
    comparar(&Letter6, &Letter1);
    cont++;
  }
  if (cont == 16) {  //verifica segunda letra
    comparar(&Letter7, &Letter2);
    cont++;
  }
  if (cont == 17) {  //terceira
    comparar(&Letter8, &Letter3);
    cont++;
  }
  if (cont == 18) {  //4
    comparar(&Letter9, &Letter4);
    cont++;
  }
  if (cont == 19) {  //5
    comparar(&Letter10, &Letter5);
    for (int i = 0; i < 5; i++) {
      if (leds[i] == 'r') {
        digitalWrite(vermelhos[i], 1);
      } else if (leds[i] == 'g') {
        digitalWrite(verdes[i], 1);
      } else {
        digitalWrite(azuis[i], 1);
      }
    }
    if (certo == 5) {  //verifica se ganhou
      lcd.clear();
      posicao = 0;
      mensagem2 = mensagem22;
      cont++;
    } else if (ntentativa - tentativa == 0) {  //verifica se a pessoa perdeu
      posicao = 0;
      lcd.clear();
      cont = 22;
    } else {
      certo = 0;
      executarLoop = false;
      mensagem2 = mensagem22;
      S2 = false;
      cont = 8;
    }
  }
  if (cont == 20) {  // vitoria
    lcd.setCursor(0, 0);
    lcd.print(mensagem4.substring(posicao, posicao + 16));
    posicao++;
    delay(300);
    if (posicao == 14) {
      delay(1500);
      cont++;
    }
  }
  if (cont == 21) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(vermelhos[i], 0);
      digitalWrite(verdes[i], 0);
      digitalWrite(azuis[i], 0);
    }
    delay(3000);
    asm volatile("  jmp 0");
  }
  if (cont == 22) {  //derrota
    lcd.setCursor(0, 0);
    lcd.print(mensagem3.substring(posicao, posicao + 16));
    posicao++;
    delay(300);
    if (posicao == 14) {
      delay(1500);
      cont--;
    }
  }
  if (cont == 2) {
    al(&Letter1);
  } else if (cont == 3) {
    al(&Letter2);
  } else if (cont == 4) {
    al(&Letter3);
  } else if (cont == 5) {
    al(&Letter4);
  } else if (cont == 6) {
    al(&Letter5);
  } else if (cont == 10) {
    if (currentTime - tempoanterior >= trocasensor) {
      sensoratual++;
      if (sensoratual > 5) {
        sensoratual = 1;
      }
      tempoanterior = currentTime;
    }
    EscolhaSensor(sensoratual);
    if (cont == 10) {
      if (digitalRead(50) == 0) {
        leds = "";
        cont = 15;
        for (int i = 0; i < 5; i++) {
          digitalWrite(verdes[i], 0);
          digitalWrite(vermelhos[i], 0);
          digitalWrite(azuis[i], 0);
        }
      }
      DefinirLetra(adivinhar1[sensoratual - 1]);
      lcd.setCursor(0, 1);
      lcd.print(Letter6);
      lcd.print(Letter7);
      lcd.print(Letter8);
      lcd.print(Letter9);
      lcd.print(Letter10);
    }
  }
}
