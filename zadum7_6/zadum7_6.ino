#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <VirtualWire.h>
#include <Eeprom24C32_64.h>
#include <EEPROM.h>
#define EEPROM_ADDRESS 0x50
//static Eeprom24C32_64 eeprom(EEPROM_ADDRESS);

class svetofor
{
  public:
    byte k;
    bool sk;
    byte g;
    bool sg;
    byte z;
    bool sz;
    byte nomer;
};

svetofor tsvetN1;
svetofor psvetN1;
svetofor tsvetN2;
svetofor psvetN2;

const byte addr_TN1 = 0; //время направления 1 время МСЕК целое
const byte count_TN1 = 4; //количество байт
const byte addr_TN2 = 4; //время направления 2 время МСЕК целое
const byte count_TN2 = 4; //количество байт
const byte addr_Gmorg = 8; //режим желтого моргающего вкл/выкл
const byte count_Gmorg = 1; //количество байт
const byte addr_geltstart = 9; //желтый моргающий по расписанию время старт целое от 0 до 24 (часы)
const byte count_geltstart = 4; //количество байт
const byte addr_geltiend = 13; //желтый моргающий по расписанию время стоп целое от 0 до 24 (часы)
const byte count_geltiend = 4; //количество байт
const byte addr_tzm = 29; // период моргания зеленого МСЕК целое
const byte count_tzm = 4; //количество байт
const byte addr_zp = 33; // количество повоторений моргания зеленого, целое
const byte count_zp = 4; //количество байт
const byte addr_tgm = 37; // период моргания желтого МСЕК целый
const byte count_tgm = 4; //количество байт
const byte addr_tg = 41; // Горение желтого при переходе с красного на зеленый
const byte count_tg = 4; //количество байт
const byte addr_ch1 = 51; //канал №1
const byte count_ch1 = 1; //количество байт
const byte addr_ch2 = 52; //канал №2
const byte count_ch2 = 1; //количество байт
const byte addr_ch3 = 53; //канал №3
const byte count_ch3 = 1; //количество байт
const byte addr_ch4 = 54; //канал №4
const byte count_ch4 = 1; //количество байт
const byte addr_ch5 = 55; //канал №5
const byte count_ch5 = 1; //количество байт
const byte addr_ch6 = 56; //канал №6
const byte count_ch6 = 1; //количество байт
const byte addr_ch7 = 57; //канал №7
const byte count_ch7 = 1; //количество байт
const byte addr_ch8 = 58; //канал №8
const byte count_ch8 = 1; //количество байт
const byte addr_ch9 = 59; //канал №9
const byte count_ch9 = 1; //количество байт
const byte addr_ch10 = 60; //канал №=10
const byte count_ch10 = 1; //количество байт
const byte addr_ch11 = 61; //канал №11
const byte count_ch11 = 1; //количество байт
const byte addr_ch12 = 62; //канал №12
const byte count_ch12 = 1; //количество байт
const byte addr_ch13 = 63; //канал №13
const byte count_ch13 = 1; //количество байт
const byte addr_ch14 = 64; //канал №14
const byte count_ch14 = 1; //количество байт
const byte addr_ch15 = 65; //канал №15
const byte count_ch15 = 1; //количество байт
const byte addr_ch16 = 66; //канал №16
const byte count_ch16 = 1; //количество байт

const byte addr_s1 = 201; //канал №1
const byte count_s1 = 1; //количество байт
const byte addr_s2 = 202; //канал №2
const byte count_s2 = 1; //количество байт
const byte addr_s3 = 203; //канал №3
const byte count_s3 = 1; //количество байт
const byte addr_s4 = 204; //канал №4
const byte count_s4 = 1; //количество байт
const byte addr_s5 = 205; //канал №5
const byte count_s5 = 1; //количество байт
const byte addr_s6 = 206; //канал №6
const byte count_s6 = 1; //количество байт
const byte addr_s7 = 207; //канал №7
const byte count_s7 = 1; //количество байт
const byte addr_s8 = 208; //канал №8
const byte count_s8 = 1; //количество байт
const byte addr_s9 = 209; //канал №9
const byte count_s9 = 1; //количество байт
const byte addr_s10 = 210; //канал №=10
const byte count_s10 = 1; //количество байт
const byte addr_s11 = 211; //канал №11
const byte count_s11 = 1; //количество байт
const byte addr_s12 = 212; //канал №12
const byte count_s12 = 1; //количество байт
const byte addr_s13 = 213; //канал №13
const byte count_s13 = 1; //количество байт
const byte addr_s14 = 214; //канал №14
const byte count_s14 = 1; //количество байт
const byte addr_s15 = 215; //канал №15
const byte count_s15 = 1; //количество байт
const byte addr_s16 = 216; //канал №16
const byte count_s16 = 1; //количество байт
const byte addr_GMpehihod = 217; //канал №16
const byte count_GMpehihod = 1; //количество байт
const byte addr_kill = 218; //канал №16
const byte count_kill = 1; //количество байт


//Время по направлениям
unsigned long TN1 = 5000; //Направление 1
unsigned long TN2 = 5000; //Направления 2

byte geltiStart = 4; // со скольки на желтый моргающий
byte geltiEnd = 4; // до скольки на желтый моргающий
bool komandanagelti = true; // желтый по команде
bool GMpeshihod = true; // Пешиходы горят зеленым при ЖМ

int oproscherez = 317; // опрос через каждые мсек
byte koloprosov = 6; //количество опросов для выбора среднего значения
int logEdenica = 895; // значение выше которого будет логичская единица, если меньше этого значения будет логический 0

unsigned long TnachOpros;
int iopros = 0; // нужно для счетчика опросов
int valuechaneL6 = 1000;//значение аналогового входа № 6, меняеться процессором само, здесь устанавливаеться первоночальное
int valuechanel6 = 0; // нужно для расчета среднего значения
int tzm = 1000; // зеленый моргающий
byte zp = 3; // количество повторений зеленого моргающего
int tg = 3000; //желтый при переходе с зеленого на красный
int tgm = 1000; //желтый моргающий
unsigned long tN1zm;
unsigned long tN1g;
unsigned long tN2;
unsigned long tN2zm;
unsigned long tN2N1;
unsigned long Tnach;
byte register1 = 0b11111111; //регистр 1
byte register2 = 0b11111111; //регистр 2
byte register3 = 0b11111111; //регистр 3
byte register4 = 0b11111111; //регистр 4
const byte clockPin = 11; // 11 sh_cp  Пин подключен к SH_CP входу 74HC595
const byte latchPin = 12; // 12 st_cp Пин подключен к ST_CP входу 74HC595
const byte dataPin = 13; // 14 ds Пин подключен к DS входу 74HC595
byte  poslednisms[17]; // последняя смс
byte ch[17]; //привязка каналов к выходам семистров по умолчанию 1канал 1 семистр, 2-2 и тд.
byte s[17]; // эмитация нерабчего семистра 0 работет, 1 всегда отключен, 2 всегда включен
byte kill = 0; // выключить светофор 0 вкл 1 выкл
bool offAllGmorg = false; // отключает любой ЖМ нужно для проверки светофора когда меняют панели
unsigned long ToffAllGmorg=0; // время для временного отключения желтого моргающиего
unsigned long tNachoffAllGmorg;// используеться таймером как счетчик для временного отключения жм
unsigned long tdayzeleni = 0; // время для временной подачи зеленого
bool glavnayadayzeleni = true; // направление для подачи зеленого главная или второстепенка
unsigned long tNachdayzeleni = 0; // используетья таймером как счетчик для подачи зеленого по требованию
byte eeW = 30; // задержка записи
byte eeR = 10; // задержка чтения
void setup()
{
  
 // eeprom.initialize();  
  // Serial.begin(9600);  
 /* Serial.println("Write eXTERNAL");
  for (byte i =0; i <255; i++)
  {
    eeprom.writeByte(i,i+33);
    //delay(eeW);
    Serial.write(i+33);
  }
  Serial.println("");
  Serial.println("Read EXTERNAL");
  for (byte i =0; i <255; i++)
  {    
    Serial.write(eeprom.readByte(i));
  //  delay(eeR);
  }
  Serial.println("");
  Serial.println("Write INTERNAL");
  for (byte i =0; i <255; i++)
  {
    EEPROM.write(i,i+33);
    Serial.write(i+33);
  }
  Serial.println("");
  Serial.println("Read INTERNAL");
  for (byte i =0; i <255; i++)
  {    
    Serial.write(EEPROM.read(i));
  }
  Serial.println("");*/

  startradio();  
  //Serial.println("Radio");
  proverkaseriala();
 // Serial.println("Serial is OK !!!");    
  pervizapusk();
  zapisperemen(); // запись переменных из флеш памяти
 
}

void loop()
{
  oproskanalov();
  worksvetofor();
  scanradio();
}



void worksvetofor()
{
  if (timer_dayzeleni())
        {
          daetzeleni();
          NormalMode();
        }
  else if (timer_offAllGmorg() && (nagataknopkagelti() || nocnoigelti() || komandanagelti)){ GeltiMorg();}
  else NormalMode(); 
}
void daetzeleni()
{
 unsigned long deltaT = millis() - Tnach;  //-20

  if (glavnayadayzeleni) // если зеленый просит на главную
     {
      if (deltaT < tN1g)// если цикл находиться от зеленого до включения желтого на переход друго направлнич
            {
               unsigned long ostalos = TN1-deltaT; //30 осталось зеленому
              if (ostalos < timer_dayzeleni()-500) Tnach = millis() - (TN1-(timer_dayzeleni())); // если оставшееся время меньше чем нужно продлить тогда увеличиваем, если наоборот ничего
            }
     // else if (deltaT < tN1g) Tnach = millis() - (TN1-(timer_dayzeleni());   //tn1 10 day = 30 время для зеленого моргающего направления, переключаем на зеленый на время таймеря 
      else if (deltaT < tN2)  Tnach = millis() - tN2zm;     
     }
  else 
  {
    if (deltaT < TN1) Tnach = millis() - TN1;
    else if (deltaT > tN1g && deltaT < tN2N1);
        {
         unsigned long ostalos = tN2-deltaT; //30 осталось зеленому
         if (ostalos < timer_dayzeleni()-500) 
            {
              if (TN2<timer_dayzeleni()) Tnach =  millis() - (tN1g+500);
              else Tnach = millis() - (tN2-(timer_dayzeleni())); // если оставшееся время меньше чем нужно продлить тогда увеличиваем, если наоборот ничего 
            }
        }    
  }
}

/* void NormalMode() ostalos5 = millis35 - tnach
{
  unsigned long deltaT = millis() - Tnach;
  if (deltaT <= TN1) {
    N1(); // время для направления 1
  }
  else if (deltaT <= tN1zm) {
    zelmorg(tsvetN1, psvetN2, tN1zm - deltaT); // время для зеленого моргающего направления 1
  }

  else if (deltaT <= tN1g)    {
    N1N2(); // время для желтого, переход с направления 1 на направление 2
  }

  else if (deltaT <= tN2) {
    N2(); // время для направления 2
  }

  else if (deltaT <= tN2zm) {
    zelmorg(tsvetN2, psvetN1, tN2zm - deltaT); // время для зеленого моргающего направления 2
  }

  else if (deltaT <= tN2N1) {
    N2N1(); // время для желтого, переход с направления 2 на направление 1
  }

  else {
    Tnach = millis(); // иначе обнуляем время
  }
}
 */
bool nagataknopkagelti()
{
  return valuechaneL6 <= logEdenica;
}

bool nocnoigelti()
{
  tmElements_t vremya;
  if (RTC.read(vremya) && (geltiStart != geltiEnd))
  {
    if (geltiStart > geltiEnd)
    {
      return (vremya.Hour >= geltiStart ||  vremya.Hour < geltiEnd);
    }
    else
    {
      return (vremya.Hour >= geltiStart &&  vremya.Hour < geltiEnd);
    }
  }
  else {
    return false;
  }
}


void GeltiMorg()
{
  unsigned long deltaT = millis() - Tnach;
  if  (deltaT <= tgm)
  {
    if (tsvetN1.sk || tsvetN1.sg || tsvetN1.sz || tsvetN2.sk || tsvetN2.sg || tsvetN2.sz || (GMpeshihod && (!psvetN1.sz || !psvetN2.sz)))
    {
      viklsvetofor(tsvetN1);
      viklsvetofor(tsvetN2);
      if (GMpeshihod)
      {
      zel(psvetN1);
      zel(psvetN2);
      }
      else
      {
      viklsvetofor(psvetN1);
      viklsvetofor(psvetN2);      
      }
      recregistr();
    }
  }
  else if (deltaT <= tgm * 2)

  {
    if (!tsvetN1.sg || !tsvetN2.sg) {
      gg(true);
      recregistr();
    }
  }
  else {
    Tnach = millis();
  }
}

void viklsvetofor(svetofor svet)
{
  svet.sk = false;
  svet.sg = false;
  svet.sz = false;
  if (svet.nomer == 1) {
    tsvetN1.sz = svet.sz;
    tsvetN1.sg = svet.sg;
    tsvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 2) {
    tsvetN2.sz = svet.sz;
    tsvetN2.sg = svet.sg;
    tsvetN2.sk = svet.sk;
  }

  else if (svet.nomer == 3) {
    psvetN1.sz = svet.sz;
    psvetN1.sg = svet.sg;
    psvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 4) {
    psvetN2.sz = svet.sz;
    psvetN2.sg = svet.sg;
    psvetN2.sk = svet.sk;
  }
}
void NormalMode()
{
  unsigned long deltaT = millis() - Tnach;
  if (deltaT <= TN1) {
    N1(); // время для направления 1
  }
  else if (deltaT <= tN1zm) {
    zelmorg(tsvetN1, psvetN2, tN1zm - deltaT); // время для зеленого моргающего направления 1
  }

  else if (deltaT <= tN1g)    {
    N1N2(); // время для желтого, переход с направления 1 на направление 2
  }

  else if (deltaT <= tN2) {
    N2(); // время для направления 1
  }

  else if (deltaT <= tN2zm) {
    zelmorg(tsvetN2, psvetN1, tN2zm - deltaT); // время для зеленого моргающего направления 2
  }

  else if (deltaT <= tN2N1) {
    N2N1(); // время для желтого, переход с направления 2 на направление 1
  }

  else {
    Tnach = millis(); // иначе обнуляем время
  }
}
void zelmorg(svetofor tsvet, svetofor psvet, unsigned long t)
{
  t = zp * tzm * 2 - t;
  bool vklvikl = t > tzm;
  if (t <= tzm) {
    vklvikl == false;
  }
  else
  {
    int chch = t / tzm;
    vklvikl = !(chch % 2 == 0);
  }

  if (tsvet.sz != vklvikl)
  {
    tsvet.sz = vklvikl;
    psvet.sz = tsvet.sz;
    if (tsvet.nomer == 1) 
    {
      tsvetN1.sz = tsvet.sz;
    }
    else if (tsvet.nomer == 2)
    {
      tsvetN2.sz = tsvet.sz;
    }

    if (psvet.nomer == 3) {
      psvetN1.sz = psvet.sz;
    }

    else if (psvet.nomer == 4) {
      psvetN2.sz = psvet.sz;
    }

    recregistr();
  }

}

void N2N1()
{
  if (!tsvetN2.sg)
  {
    krasn(psvetN1);
    gg(true);
    recregistr();
  }
}

void N1N2()
{
  if (!tsvetN1.sg)
  {
    krasn(psvetN2);
    gg(true);
    recregistr();
  }
}

void N1()
{

  if (!tsvetN1.sz)
  {
    zel(tsvetN1);
    krasn(tsvetN2);
    zel(psvetN2);
    gg(LOW);
    recregistr();

  }
}

void N2()
{

  if (!tsvetN2.sz)
  {
    krasn(tsvetN1);
    zel(psvetN1);
    zel(tsvetN2);
    gg(LOW);
    recregistr();
  }
}

void gg(bool sost)
{
  gelt(tsvetN1, sost);
  gelt(tsvetN2, sost);
}
void gelt(svetofor svet, bool sost)
{
  svet.sg = sost;
  if (sost) {
    svet.sz = false;
  }

  if (svet.nomer == 1) {
    tsvetN1.sz = svet.sz;
    tsvetN1.sg = svet.sg;
  }

  else if (svet.nomer == 2) {
    tsvetN2.sz = svet.sz;
    tsvetN2.sg = svet.sg;
  }

  else if (svet.nomer == 3) {
    psvetN1.sz = svet.sz;
    psvetN1.sg = svet.sg;
  }

  else if (svet.nomer == 4) {
    psvetN2.sz = svet.sz;
    psvetN2.sg = svet.sg;
  }
}
void krasn(svetofor svet) //переключает каналы
{
  svet.sk = true;
  svet.sz = !svet.sk;

  if (svet.nomer == 1) {
    tsvetN1.sz = svet.sz;
    tsvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 2) {
    tsvetN2.sz = svet.sz;
    tsvetN2.sk = svet.sk;
  }

  else if (svet.nomer == 3) {
    psvetN1.sz = svet.sz;
    psvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 4) {
    psvetN2.sz = svet.sz;
    psvetN2.sk = svet.sk;
  }
}

void zel(svetofor svet) //переключает каналы
{
  svet.sz = true;
  svet.sk = !svet.sz;

  if (svet.nomer == 1) {
    tsvetN1.sz = svet.sz;
    tsvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 2) {
    tsvetN2.sz = svet.sz;
    tsvetN2.sk = svet.sk;
  }

  else if (svet.nomer == 3) {
    psvetN1.sz = svet.sz;
    psvetN1.sk = svet.sk;
  }

  else if (svet.nomer == 4) {
    psvetN2.sz = svet.sz;
    psvetN2.sk = svet.sk;
  }
}

void killKanal()
{
  for (byte i = 1; i < 17; i++)
  {
    if (s[i] == 1)
    {
      if (i < 9) {
        bitWrite (register1, i-1, true);
      }
      else    {
        bitWrite (register2, i - 9, true);
      }
    }
    else if (s[i] == 2)
    {
      if (i < 9) {
        bitWrite (register1, i-1, false);
      }
      else    {
        bitWrite (register2, i - 9, false);
      }
    }
  }
}

void recregistr() //перезапись регистров
{
  recsvetofor(tsvetN1);
  recsvetofor(psvetN1);
  recsvetofor(tsvetN2);
  recsvetofor(psvetN2);
  killKanal();
  // открываем
  digitalWrite(latchPin, LOW);
  // "проталкиваем" байты в регистры
  if (kill == 0)
  {
  shiftOut(dataPin, clockPin, MSBFIRST, register4);
  shiftOut(dataPin, clockPin, MSBFIRST, register3);
  shiftOut(dataPin, clockPin, MSBFIRST, register2);
  shiftOut(dataPin, clockPin, MSBFIRST, register1);
  // "защелкиваем" регистр, чтобы биты появились на выходах регистра
  }
  else if (kill == 1) //обычная смерт все выключенно выключение
  {
      
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  // "защелкиваем" регистр, чтобы биты появились на выходах регистра
  }
  else if (kill == 2) //не обычная смерт все включенно выключение
  {
      
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  // "защелкиваем" регистр, чтобы биты появились на выходах регистра
  }
  else if (kill == 3)  //не обычная смерт горит как попало
  {
    shiftOut(dataPin, clockPin, MSBFIRST, 0b00101010);
    shiftOut(dataPin, clockPin, MSBFIRST, 0b11000011);
    shiftOut(dataPin, clockPin, MSBFIRST, 0b01110000);
    shiftOut(dataPin, clockPin, MSBFIRST, 0b01000101);
  }
  
  digitalWrite(latchPin, HIGH);
}

void recsvetofor(svetofor svet)
{
  //если управление плюсовое здесь нужно убрать восклицательный знак
  reckanal(svet.k, !svet.sk);
  reckanal(svet.g, !svet.sg);
  reckanal(svet.z, !svet.sz);
}

void reckanal(byte kanal, bool sost)
{
  if (kanal != 0)
  {
    if (kanal <= 8) {
      bitWrite (register1, kanal - 1, sost);
      paneldriver(kanal, sost);
    }
    else {
      bitWrite (register2, kanal - 9, sost);
      paneldriver(kanal, sost);
    }
  }
  paneldriver(kanal, sost);
}
void  paneldriver(byte kanal, bool sost)
{

  if (kanal == 1) {
    bitWrite (register3, 7, sost);
  }
  else if (kanal == 2) {
    bitWrite (register3, 5, sost);
  }
  else if (kanal == 3) {
    bitWrite (register3, 3, sost);
  }
  else if (kanal == 4) {
    bitWrite (register3, 1, sost);
  }
  else if (kanal == 5) {
    bitWrite (register4, 7, sost);
  }
  else if (kanal == 6) {
    bitWrite (register4, 5, sost);
  }
  else if (kanal == 7) {
    bitWrite (register4, 3, sost);
  }
  else if (kanal == 8) {
    bitWrite (register4, 1, sost);
  }
  else if (kanal == 9) {
    bitWrite (register3, 6, sost);
  }
  else if (kanal == 10) {
    bitWrite (register3, 4, sost);
  }
  else if (kanal == 11) {
    bitWrite (register3, 2, sost);
  }
  else if (kanal == 12) {
    bitWrite (register3, 0, sost);
  }
  else if (kanal == 13) {
    bitWrite (register4, 6, sost);
  }
  else if (kanal == 14) {
    bitWrite (register4, 4, sost);
  }
  else if (kanal == 15) {
    bitWrite (register4, 2, sost);
  }
  else if (kanal == 16) {
    bitWrite (register4, 0, sost);
  }
}

void oproskanalov()
{

  if ((millis() - TnachOpros) >= oproscherez)
  {
    iopros++;
    valuechanel6 += analogRead(6);
    TnachOpros = millis();
    if (iopros >= koloprosov)
    {
      // Serial.print("ValuechaneL6 ");
      //  Serial.println(valuechanel6 / iopros);
      valuechaneL6 = valuechanel6 / iopros;
      valuechanel6 = 0;
      iopros = 0;
    }
  }
}
void starttimerdayzeleni(uint8_t *sms,uint8_t smslen)
{
  //формат - код+значение+g или v, пример код+40000g
  tdayzeleni = 0; 
  byte i;
  for(i = 4; sms[i] != 103 /*ASCII 'g'*/ || sms[i] != 118 /*ASCII 'v'*/;i++)
  {
    tdayzeleni =tdayzeleni*10 + (sms[i]-48);
  }
  i++;
  //выставляет параметы запуска таймера для подачи зеленого
  tNachdayzeleni = millis();
  glavnayadayzeleni = sms[i] == 103/*ASCII 'g'*/;
}
unsigned long timer_dayzeleni()
{
  if (tdayzeleni > (millis() - tNachdayzeleni)) return (millis() - tNachdayzeleni);
  else 
  {
   tNachdayzeleni = 0;
   tdayzeleni = 0;
   return  0;
  }
}
bool timer_offAllGmorg()
{
  if (ToffAllGmorg < (millis() - tNachoffAllGmorg)) 
             {
              tNachoffAllGmorg = 0;
              ToffAllGmorg = 0;
              return true;
             }
  else return false;
}
void zapisperemen()
{
 TN1 =  konvertie(addr_TN1, count_TN1,1);
 TN2 =  konvertie(addr_TN2, count_TN2,1);
 komandanagelti = konvertie(addr_Gmorg, count_Gmorg,1);
 geltiStart = konvertie(addr_geltstart, count_geltstart,1);
 geltiEnd = konvertie(addr_geltiend, count_geltiend,1);
 tzm = konvertie(addr_tzm, count_tzm,1);
 zp = konvertie(addr_zp, count_zp,1);
 tg = konvertie(addr_tg, count_tg,1);
 tgm = konvertie(addr_tgm, count_tgm,1);
 GMpeshihod = konvertie(addr_GMpehihod, count_GMpehihod,1);  
 ch[1] = konvertie(addr_ch1, count_ch1,1);
 ch[2] = konvertie(addr_ch2, count_ch2,1);
 ch[3] = konvertie(addr_ch3, count_ch3,1);
 ch[4] = konvertie(addr_ch4, count_ch4,1);
 ch[5] = konvertie(addr_ch5, count_ch5,1);
 ch[6] = konvertie(addr_ch6, count_ch6,1);
 ch[7] = konvertie(addr_ch7, count_ch7,1);
 ch[8] = konvertie(addr_ch8, count_ch8,1);
 ch[9] = konvertie(addr_ch9, count_ch9,1);
 ch[10] = konvertie(addr_ch10, count_ch10,1);
 ch[11] = konvertie(addr_ch11, count_ch11,1);
 ch[12] = konvertie(addr_ch12, count_ch12,1);
 ch[13] = konvertie(addr_ch13, count_ch13,1);
 ch[14] = konvertie(addr_ch14, count_ch14,1);
 ch[15] = konvertie(addr_ch15, count_ch15,1);
 ch[16] = konvertie(addr_ch16, count_ch16,1);
 kill = konvertie(addr_kill, count_kill,1);
 s[1] = konvertie(addr_s1, count_s1,1);
 s[2] = konvertie(addr_s2, count_s2,1);
 s[3] = konvertie(addr_s3, count_s3,1);
 s[4] = konvertie(addr_s4, count_s4,1);
 s[5] = konvertie(addr_s5, count_s5,1);
 s[6] = konvertie(addr_s6, count_s6,1);
 s[7] = konvertie(addr_s7, count_s7,1);
 s[8] = konvertie(addr_s8, count_s8,1);
 s[9] = konvertie(addr_s9, count_s9,1);
 s[10] = konvertie(addr_s10, count_s10,1);
 s[11] = konvertie(addr_s11, count_s11,1);
 s[12] = konvertie(addr_s12, count_s12,1);
 s[13] = konvertie(addr_s13, count_s13,1);
 s[14] = konvertie(addr_s14, count_s14,1);
 s[15] = konvertie(addr_s15, count_s15,1);
 s[16] = konvertie(addr_s16, count_s16,1);  
 tN1zm = TN1 + zp * 2 * tzm; // время для зеленого моргающего направления 1
 tN1g = tN1zm + tg; // время для желтого, переход с направления 1 на направление 2
 tN2 = tN1g + TN2;// время для направления 1
 tN2zm = tN2 + zp * tzm * 2; // время для зеленого моргающего направления 2
 tN2N1 = tN2zm + tg;// время для желтого, переход с направления 2 на направление 
 //Список каналов
  //Направление 1
  tsvetN1.k = ch[1];//Красный
  tsvetN1.g = ch[2];//Желтый
  tsvetN1.z = ch[3];//Зеленый
  psvetN1.k = ch[4];//Красный Пешиход
  psvetN2.g = 0; // Желтый канал 0 означает что это пешиходный светофор
  psvetN1.z = ch[5]; // Зеленый Пешиход


  //Направление 2
  tsvetN2.k = ch[6];//Красный
  tsvetN2.g = ch[7];//Желтый
  tsvetN2.z = ch[8];  //Зеленый

  psvetN2.k = ch[9];//Красный Пешиход
  psvetN2.g = 0; // Желтый канал 0 означает что это пешиходный светофор
  psvetN2.z = ch[10]; // Зеленый Пешиход

  tsvetN1.nomer = 1;
  tsvetN2.nomer = 2;
  psvetN1.nomer = 3;
  psvetN2.nomer = 4;

  Tnach = millis();
  TnachOpros = millis();
   pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
//  pinMode(10, INPUT); 
  krasn(psvetN1);
  recregistr();
  //tNachdayzeleni = millis(); // убрать потом

// Serial.println("Zapis peremennih");
}
void proverkaseriala()
{
   while(!serialvalid()){/*Serial.println("1 Serial NE Valid");*/}
}
bool serialvalid()
{
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
if (!vw_get_message(buf, &buflen)) {/*Serial.println("Net sms");*/ return false;} // Не блокируется 
 
  char serial[16] = "28FF5DB88316039E";
  bool validserial = true; 
  for (int i = 0;i<buflen;i++)
  {
    validserial = validserial && (buf[i] == serial[i]);
 // Serial.write(buf[i]);  
 // Serial.println(serial[i], HEX);
  }
   //Serial.println("");
   //Serial.println(serial);
//  n=!n;
//  digitalWrite(13,n);
  return validserial;
}


void scanradio()
{
     uint8_t buf[VW_MAX_MESSAGE_LEN];
     uint8_t buflen = VW_MAX_MESSAGE_LEN;
     if (vw_get_message(buf, &buflen) )  // Не блокируется 
        {
          bool togesamoe = true;
          byte len;
          if (buflen<17) len = buflen;
          else len = 17;
          for (byte i = 0; i <len; i++)
          {
           // Serial.write(buf[i]);
            togesamoe = togesamoe && buf[i] == poslednisms[i];
          }          
         // Serial.println("");
         
          if (!togesamoe)//если не тоже самое
           {
           // Serial.print("Novi SMS");
            for (byte i = 0; i <len; i++)
          {
            poslednisms[i] = buf[i];
          }
           //poslednisms = buf;      
           byte tipsms = validsms(buf,buflen);
           //Serial.print(tipsms, DEC);
           //Serial.println(" = tipsms");
           if(tipsms == 0)tipsms=0;//если смс левое делоем бессмысленное действие, останов сравнений
           else if (tipsms == 1 || tipsms == 2) newsms(buf,buflen,tipsms-1); // записываем присланные смс в память, тип смс означает 2 внутряя, 1 внешняя память
           else if (tipsms == 3) starttimerdayzeleni(buf,buflen); // дать зеленый по направлению
           else if (tipsms == 4) setDateTime(buf,buflen); // установить вермя
           else if (tipsms == 5) otklgmdlyaproverki(buf,buflen); // отключить жм для проверки
           else if (tipsms == 6) tabletka(); //лечит светофор 
           else if (tipsms == 7) defaultsetings(); //лечит светофор                  
          }
        //  else Serial.println("TOGE SAMI");
         }
}

void otklgmdlyaproverki(uint8_t *sms,uint8_t smslen)
{
 
  ToffAllGmorg = 0;//длительность рекомендую 9000000 = 15 минут
  for(byte i = 4;i<smslen;i++)
  {
  ToffAllGmorg =ToffAllGmorg*10 + (sms[i]-48);
  }
//далее код запуска таймера 
 tNachoffAllGmorg = millis();// сброс счетчика
}
void setDateTime(uint8_t *sms,uint8_t smslen)
{

 //формат вывода 30m10y1980h21m00s
  byte i;
  byte Day=0;
  byte Month=0;
  int Year=0;
  byte Hour=0;
  byte Min=0;
  byte Sec=0;
  for( i = 4; sms[i] != 100/*'d'*/; i++)
  {
    Day = Day*10 + (sms[i]-48);
  }
   for(i += 2; sms[i]  != 121/*'y'*/; i++)
  {
    Month = Month*10 + (sms[i]-48);
  }
   for(i+=2; sms[i]  != 104/*'h'*/; i++)
  {
    Year =Year*10 + (sms[i]-48);
  }
     for(i+=2; sms[i]  != 109/*'m'*/; i++)
  {
    Hour =Hour*10 + (sms[i]-48);
  }
   for(i+=2; sms[i]  != 115/*'s'*/; i++)
  {
    Min =Min*10 + (sms[i]-48);
  }
    for(i+=2; i < smslen; i++)
  {
    Sec =Sec*10 + (sms[i]-48);
  }
 // String str = 'd'+Day +'m'+ Month+'y'+Year+'h'+Hour+'m'+Min;
 // Serial.println(str);
  tmElements_t tm;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  tm.Day = Day;
  tm.Month = Month;
  tm.Year = Year;
  RTC.write(tm);
}

void sendsmseeprom(byte addr, byte count, unsigned long value,bool ie)
{
 //Serial.print("Send SMS eeprom");
  /*String str = String(addr) + 'c' + String(count) + 'd' + String(value);
 Serial.println(str);
  byte len = str.length();
  char sms[len];
  len++;
  str.toCharArray(sms,len); 
  */
  
  char addr_ch[3];
  char count_ch;
  char value_ch[7];
  byte lenmas=0;
  byte addr_i=0;
  byte value_i=0;
  if (addr == 0) {addr_ch[0] = 48; addr_i = 1; }

  while (addr!=0)
  {
   addr_ch[addr_i]=48 + addr%10;
  // Serial.write(addr_ch[addr_i]);
   addr=addr/10;
   addr_i++;
   }
 //  Serial.println(" = addr");

   count_ch=48 + count;
 //  Serial.write(count_ch);
 
//   Serial.println(" = count");
     if (value == 0) {value_ch[0] = 48; value_i = 1; }
    while (value!=0)
  {
   value_ch[value_i] = 48 + value%10;
//   Serial.write(value_ch[value_i]);
   value=value/10;
   value_i++;
   }
  // Serial.println(" = value");
 char strok[addr_i+value_i+3];
 byte strok_i = 0;
for (addr_i; addr_i > 0; addr_i--)
 {
  strok[strok_i] = addr_ch[addr_i-1];
//  Serial.write(strok[strok_i]);
  strok_i++;  
 } 
 strok[strok_i]= 99 /*'c'*/;
// Serial.write(strok[strok_i]); 
  strok_i++;
 strok[strok_i]= count_ch;
 //Serial.write(strok[strok_i]); 
 strok_i++;
 strok[strok_i]= 100 /*'d'*/;
 //Serial.write(strok[strok_i]); 
 strok_i++;
 
  for (value_i; value_i > 0; value_i--)
 {
  strok[strok_i]=value_ch[value_i-1];
 // Serial.write(strok[strok_i]); 
  strok_i++; 
 }
 for(byte vb = 0; vb < strok_i; vb++)
  {
    //Serial.write(strok[vb]);
  }
  //Serial.println("");
  receeprom(strok,strok_i,ie);
}
void newsms(uint8_t *sms,uint8_t smslen, bool ie)
{
  uint8_t editsms[smslen-6];
 // Serial.println("Prishla sms  newsms");
     for(byte i = 6; i<smslen;i++)
           {
           // Serial.write(sms[i]);
            editsms[i-6] = sms[i];
           }
             //Serial.println("");
              
            receeprom(editsms,smslen-6, ie); 
            zapisperemen(); 
}

void receeprom(uint8_t *sms,uint8_t smslen, bool ie)
{ 
 /*  for(byte i = 0; i<smslen;i++)
           {
           Serial.write(sms[i]);
          
           }
           Serial.println(" = sms Receeprom");*/
     byte i; byte sdvig;
     byte addr = 0;
     byte count = 0; 
     unsigned long value = 0;  
     for(i = 0; sms[i]!=99/*ASCII код латинской с*/ ;i++) 
           {
            addr =addr*10 + (sms[i]-48);
         //  Serial.write(sms[i]);            
            sdvig = i+2;
           }
           
 /* Serial.println(" = addrstr");
  Serial.println(addr);*/
  i=sdvig;
  count = sms[i]-48;
  //Serial.write(sms[i]);
  sdvig = i+2;
// Serial.println(" = count");
 //Serial.println(count);
 for(i=sdvig; i < smslen; i++)
          {
           value =value*10+(sms[i]-48);
   //        Serial.write(sms[i]);            
          }     
 // Serial.println(" = value");
  //Serial.println(value);
   if (count == 1) {EEPROM.write(addr, value);/*delay (eeW);*/}
     else
     {
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(addr, four);
     // delay (eeW);
      EEPROM.write(addr + 1, three);
      //delay (eeW);
      EEPROM.write(addr + 2, two);
      //delay (eeW);
      EEPROM.write(addr + 3, one);
     //  delay (eeW);
     }
  /* byte data[count];
   if (count == 1) data[0] = value;
   else
   {    
    data[0] = value;
    data[1] = value >>  8;
    data[2] = value >> 16;
    data[3] = value >> 24;   
   }*/
  /* if(ie)
   {
     if (count == 1) {EEPROM.write(addr, data[0]);delay (eeW);}
        else  {
               EEPROM.write(addr, data[0]);
               delay (eeW);
               EEPROM.write(addr + 1, data[1]);
               delay (eeW);
               EEPROM.write(addr + 2, data[2]);
               delay (eeW);
               EEPROM.write(addr + 3, data[3]);
              }
   }
   else {
            if (count == 1) 
                 {eeprom.writeByte(addr, data[0]);
                 delay (eeW);}
              else  {
               eeprom.writeByte(addr, data[0]);
               delay (eeW);
               eeprom.writeByte(addr + 1, data[1]);
               delay (eeW);
               eeprom.writeByte(addr + 2, data[2]);
               delay (eeW);
               eeprom.writeByte(addr + 3, data[3]);
              }
         }*/
           
}

/*void testeprom()
{
  delay (5000);
  eeprom.initialize();

    const byte address = 0;
    const byte count = 94;

    // Declare byte arrays.
    byte inputBytes[count] = { 0 };
    byte outputBytes[count] = { 0 };

    // Fill input array with printable characters. See ASCII table for more
    // details.
    for (byte i = 0; i < count; i++)
    {    
        inputBytes[i] = i + 33;
    }

    // Write input array to EEPROM memory.
    Serial.println("Write bytes to EEPROM memory...");
   
    eeprom.writeBytes(address, count, inputBytes);

    // Read array with bytes read from EEPROM memory.
    Serial.println("Read bytes from EEPROM memory...");
    eeprom.readBytes(address, count, outputBytes);
    
    // Print read bytes.
    Serial.println("Read bytes:");
    for (byte i = 0; i < count; i++)
    {
        Serial.write(outputBytes[i]);
        Serial.print(" ");
    }
    Serial.println("");
}*/

unsigned long konvertie(byte addr, byte count, bool ie)//ie internal eeprom брать данные из внутренней памяти
{
// unsigned long vall;
  if (count == 1) return  EEPROM.read(addr);

      long four = EEPROM.read(addr);
      long three = EEPROM.read(addr + 1);
      long two = EEPROM.read(addr + 2);
      long one = EEPROM.read(addr + 3);      
     return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
    
      // return vall;
 /* long temp[count];
  unsigned long value; 
 if(ie)
 { 
  if (count == 1)
      {
        temp[0] = EEPROM.read(addr);
        delay (eeR);
        value = temp[0];
      }
  else 
      {              
        temp[0] = EEPROM.read(addr);
        delay (eeR);
        temp[1] = EEPROM.read(addr + 1);
        delay (eeR);
        temp[2] = EEPROM.read(addr + 2);
        delay (eeR);
        temp[3] = EEPROM.read(addr + 3);
        delay (eeR);
        value = ((unsigned long)temp[3] << 24) +((unsigned long)temp[2] << 16) +(temp[1] << 8) +temp[0];
      }
 } 
 else 
 {
      if (count == 1)
      {
        temp[0] = eeprom.readByte(addr);
        delay (eeR);
        value = temp[0];
      }
  else 
      {              
        temp[0] = eeprom.readByte(addr);
        delay (eeW);
        temp[1] = eeprom.readByte(addr + 1);
        delay (eeW);
        temp[2] = eeprom.readByte(addr + 2);
        delay (eeW);
        temp[3] = eeprom.readByte(addr + 3);
        delay (eeW);
        value = ((unsigned long)temp[3] << 24) +((unsigned long)temp[2] << 16) +(temp[1] << 8) +temp[0];
      }   
 }*/
 // Serial.println(value);
 // return value;
}

byte validsms(uint8_t *sms,uint8_t smslen)
{
  if (sms[0] == '3' && sms[1] == '!' && sms[2] == 'z' && sms[3] == '}' )
  {
    if (sms[4]=='E' && sms[5] == 'a') return 1; // 'E' - extrenal внешний - запись в память настрек присланных по радиоканалу 
    else if (sms[4]=='I' && sms[5] == 'a') return 2; // 'I' - internal внутренний - запись в память настрек присланных по радиоканалу 
    else return 0;
  }
  else if(sms[0] == '@' && sms[1] == '#' && sms[2] == '!' && sms[3] == 'Z') return 3; // дать зеленный по направлению
  else if(sms[0] == 's' && sms[1] == '-' && sms[2] == 'Q' && sms[3] == 'c') return 4; // установить дату время
  else if(sms[0] == '&' && sms[1] == 'E' && sms[2] == '/' && sms[3] == '3') return 5; // Отключить на время желтый моргающий для проведения работ в ночное време если моргает желтый
  else if(sms[0] == '+' && sms[1] == 'b' && sms[2] == '4' && sms[3] == '!') return 6; // tabletka
  else if(sms[0] == 'k' && sms[1] == '@' && sms[2] == 'J' && sms[3] == '%') return 7; // сброс настроек по умолчанию
  else return 0;
}

void startradio()
{
 vw_set_ptt_inverted(true); // необходимо для модуля DR3100
  vw_set_rx_pin(9);
  vw_setup(2000); // бит в секунду
  vw_wait_rx_max(200); 
  vw_rx_start(); 
}


 void defaultsetings()
{
 //Serial.println("Default setings =");
 sendsmseeprom(addr_TN1, count_TN1,10000,1);
 sendsmseeprom(addr_TN2, count_TN2,10000,1);
 sendsmseeprom(addr_Gmorg, count_Gmorg, 0,1);
 //eeprom.writeByte(addr_Gmorg,0);
// Serial.println(eeprom.readByte(addr_Gmorg), DEC);
 sendsmseeprom(addr_geltstart, count_geltstart,7,1);
 sendsmseeprom(addr_geltiend, count_geltiend,7,1);
 sendsmseeprom(addr_tzm, count_tzm,700,1);
 sendsmseeprom(addr_zp, count_zp,3,1);
 sendsmseeprom(addr_tg, count_tg,3000,1);
 sendsmseeprom(addr_tgm, count_tgm,700,1);
 sendsmseeprom(addr_GMpehihod, count_GMpehihod,0,1);
 sendsmseeprom(addr_ch1, count_ch1,1,1);
 sendsmseeprom(addr_ch2, count_ch2,2,1);
 sendsmseeprom(addr_ch3, count_ch3,3,1);
 sendsmseeprom(addr_ch4, count_ch4,4,1);
 sendsmseeprom(addr_ch5, count_ch5,5,1);
 sendsmseeprom(addr_ch6, count_ch6,6,1);
 sendsmseeprom(addr_ch7, count_ch7,7,1);
 sendsmseeprom(addr_ch8, count_ch8,8,1);
 sendsmseeprom(addr_ch9, count_ch9,9,1);
 sendsmseeprom(addr_ch10, count_ch10,10,1);
 sendsmseeprom(addr_ch11, count_ch11,11,1);
 sendsmseeprom(addr_ch12, count_ch12,12,1);
 sendsmseeprom(addr_ch13, count_ch13,13,1);
 sendsmseeprom(addr_ch14, count_ch14,14,1);
 sendsmseeprom(addr_ch15, count_ch15,15,1);
 sendsmseeprom(addr_ch16, count_ch16,16,1); 
}
void  tabletka()//лечим светофор 
{
 // Serial.print("Tabletka");
 sendsmseeprom(addr_s1,count_s1,0,1); 
 sendsmseeprom(addr_s2,count_s2,0,1); 
 sendsmseeprom(addr_s3,count_s3,0,1); 
 sendsmseeprom(addr_s4,count_s4,0,1); 
 sendsmseeprom(addr_s5,count_s5,0,1); 
 sendsmseeprom(addr_s6,count_s6,0,1); 
 sendsmseeprom(addr_s7,count_s7,0,1); 
 sendsmseeprom(addr_s8,count_s8,0,1); 
 sendsmseeprom(addr_s9,count_s9,0,1); 
 sendsmseeprom(addr_s10,count_s10,0,1); 
 sendsmseeprom(addr_s11,count_s11,0,1); 
 sendsmseeprom(addr_s12,count_s12,0,1); 
 sendsmseeprom(addr_s13,count_s13,0,1); 
 sendsmseeprom(addr_s14,count_s14,0,1); 
 sendsmseeprom(addr_s15,count_s15,0,1); 
 sendsmseeprom(addr_s16,count_s16,0,1); 
 sendsmseeprom(addr_kill,count_kill,0,1);
}
void pervizapusk()//срабатывает если при самом первом запуске процессора
{
  /*Serial.println("Read internal eeprom");
  for (byte i = 0; i<250; i++)
     {
      byte b = EEPROM.read(i);     
      Serial.print(i, DEC);
      Serial.print(" Byte = ");
      Serial.println(b);
     }
       Serial.println("Read external eeprom");
  for (byte i = 0; i<250; i++)
     {
      byte b = eeprom.readByte(i);     
      Serial.print(i, DEC);
      Serial.print(" Byte = ");
      Serial.println(b);
     }*/
   //  byte ds = EEPROM.read(310);
     
     if (EEPROM.read(309) != 174) 
    {
     // delay(30);
      EEPROM.write(309,174);
   //   Serial.println("Tabletka");     
      tabletka();
       defaultsetings();
    }
   
     /*if (eeprom.readByte(254) != 123)
     {
      eeprom.writeByte(254,123);
      Serial.println("Default");
      defaultsetings();
      }
*/      
}
 

