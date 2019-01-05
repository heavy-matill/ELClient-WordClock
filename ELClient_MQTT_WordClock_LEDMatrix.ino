/**
 * Simple example to demo the esp-link MQTT client
 */

#include <ELClient.h>
#include <ELClientCmd.h>
#include <ELClientMqtt.h>
#include "FastLED.h"
#include <LEDMatrix.h>


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define FILLARRAY(a,n) a[0]=n, memcpy( ((char*)a)+sizeof(a[0]), a, sizeof(a)-sizeof(a[0]) );

#define BRIGHTNESS          128
#define FRAMES_PER_SECOND  120

#define LED_PIN        11
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   11  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_HEIGHT  10  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX  // See top of LEDMatrix.h for matrix wiring types

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;




uint8_t angle = 0;
bool fillColor = 0;
bool fillBackInv = 0;
bool colRandom = 0;
uint8_t colAdvance = 0;
uint8_t colForeground = 0;





uint8_t iEsIst[11] = {9,0,9,1,9,3,9,4,9,5,255};
uint8_t iFuenfMin[9] = {9,7,9,8,9,9,9,10,255};
uint8_t iZehnMin[9] = {8,0,8,1,8,2,8,3,255};
uint8_t iViertel[15] = {8,4,8,5,8,6,8,7,8,8,8,9,8,10,255};
uint8_t iZwanzig[15] = {7,0,7,1,7,2,7,3,7,4,7,5,7,6,255};
uint8_t iVor[7] = {7,8,7,9,7,10,255};
uint8_t iNach[9] = {6,0,6,1,6,2,6,3,255};
uint8_t iHalb[9] = {6,7,6,8,6,9,6,10,255};
uint8_t iFuenf[9] = {5,1,5,2,5,3,5,4,255};
uint8_t iZwei[9] = {5,7,5,8,5,9,5,10,255};
uint8_t iSieben[13] = {4,1,4,2,4,3,4,4,4,5,4,6,255};
uint8_t iVier[9] = {4,7,4,8,4,9,4,10,255};
uint8_t iZehn[9] = {3,1,3,2,3,3,3,4,255};
uint8_t iSechs[11] = {3,6,3,7,3,8,3,9,3,10,255};
uint8_t iDrei[9] = {2,1,2,2,2,3,2,4,255};
uint8_t iAcht[9] = {2,6,2,7,2,8,2,9,255};
uint8_t iElf[7] = {1,0,1,1,1,2,255};
uint8_t iNeun[9] = {1,3,1,4,1,5,1,6,255};
uint8_t iEins[9] = {1,7,1,8,1,9,1,10,255};
uint8_t iEin[7] = {1,7,1,8,1,9,255};
uint8_t iZwoelf[11] = {0,1,0,2,0,3,0,4,0,5,255};
uint8_t iUhr[7] = {0,8,0,9,0,10,255};

#define BRIGHTNESS          128
#define FRAMES_PER_SECOND  120


// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial, &Serial);

// Initialize CMD client (for GetTime)
ELClientCmd cmd(&esp);

// Initialize the MQTT client
ELClientMqtt mqtt(&esp);

// Callback made from esp-link to notify of wifi status changes
// Here we just print something out for grins
void wifiCb(void* response) {
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1) {
    uint8_t status;
    res->popArg(&status, 1);

    if(status == STATION_GOT_IP) {
    Serial.println("WIFI CONNECTED");
    } else {
     Serial.print("WIFI NOT READY: ");
    Serial.println(status);
    }
  }
}

bool connected; 

// Callback when MQTT is connected
void mqttConnected(void* response) {
  Serial.println("MQTT connected!");
  //mqtt.subscribe("/esp-link/1");
  //mqtt.subscribe("/hello/world/#");
  mqtt.subscribe("srgb");
  //mqtt.subscribe("/esp-link/2", 1);
  //mqtt.publish("/esp-link/0", "test1");
  connected = true;
}

// Callback when MQTT is disconnected
void mqttDisconnected(void* response) {
  Serial.println("MQTT disconnected");
  connected = false;
}

// Callback when an MQTT message arrives for one of our subscriptions
void mqttData(void* response) {
  ELClientResponse *res = (ELClientResponse *)response;

  Serial.print("Received: topic=");
  String topic = res->popString();
  Serial.println(topic);
  //rgb.stringAvailable(res->popString());

  
  Serial.print("data=");
  String data = res->popString();
  Serial.println(data);

  /*
  if(topic=="/rgb")
  {
  uint8_t myuint = 0;
  for (uint8_t i=0; i<data.length()/2;i++) {
        myuint = 0;
        for (uint8_t j=0; j<2; j++) {
            char firstchar = data[(i*2)+j];
            //printf("myuint[%d] = %3d data[%d+%d] = %c ", i, myuint[i], i, j, mystring[(i*2)+j]);
            if (firstchar >= '0' && firstchar <= '9') {
                //Serial.print("Number");
                myuint = myuint*16 + firstchar - '0';
            } else if (firstchar >= 'A' && firstchar <= 'F') {
                //Serial.print("LETTER");
                myuint = myuint*16 + firstchar - 'A' + 10;
            } else if (firstchar >= 'a' && firstchar <= 'f') {
                //Serial.print("letter");
                myuint = myuint*16 + firstchar - 'a' + 10;
            } else {
                // error
               // Serial.println("NOOOO");
            }
            //printf(" myuint[%d] = %3d\n", i, myuint[i]);
        }
    rgb.dataAvailable(myuint);
    }
  }*/

  
 // if(topic=="/RGB")
  //{
    //if (data=="faster")
     // mqtt.publish("/rgb", (&char) 0x04);
    //if (data=="slower")
    //mqtt.publish("/rgb", (char) 0x05);
  //}
}



void mqttPublished(void* response) {
  Serial.println("MQTT published");
}

void setup() {

  delay(3000); // 3 second delay for recovery
 FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(127);
  FastLED.clear(true);
  delay(500);
  
  Serial.begin(115200);
  Serial.println("EL-Client starting!");
 
// Sync-up with esp-link, this is required at the start of any sketch and initializes the
  // callbacks to the wifi status change callback. The callback gets called with the initial
  // status right after Sync() below completes.
  esp.wifiCb.attach(wifiCb); // wifi status change callback, optional (delete if not desired)
  bool ok;
  do {
    ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
    if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
  Serial.println("EL-Client synced!");
  esp.Process();  
  // Set-up callbacks for events and initialize with es-link.
  mqtt.connectedCb.attach(mqttConnected);
  mqtt.disconnectedCb.attach(mqttDisconnected);
  mqtt.publishedCb.attach(mqttPublished);
  mqtt.dataCb.attach(mqttData);
  mqtt.setup();

  //Serial.println("ARDUINO: setup mqtt lwt");
  //mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

  Serial.println("EL-MQTT ready");
  Serial.println("RGB-Setup");
//  setup_rgb();
  randomSeed(GetTime());
}

static int count;
static uint32_t last;
uint32_t next = 0;

uint32_t GetTime() {
  esp.Request(CMD_GET_TIME, 0, 0);
  esp.Request();

  ELClientPacket *pkt = esp.WaitReturn();
  return pkt ? pkt->value : 0;
}    

uint8_t tSec(uint32_t tSecTot)
{
  return tSecTot%60;
}

uint8_t tMin(uint32_t tSecTot)
{
  return tSecTot/60%60;  
}

uint8_t tHour(uint32_t tSecTot)
{
  return tSecTot/3600%12;  
}

void displayIdx(uint8_t idx[])
{
  if(fillColor)
  {
    if(colRandom)
      colForeground = random8();
  
  
        for(uint8_t i=0;idx[i]!=255;i+=2)
          {
            leds(idx[i+1],idx[i]).setHue(colForeground+colAdvance*i);
          }
  }

  if(fillBackInv)
  {
  for(uint8_t i=0;idx[i]!=255;i+=2)
          {
            leds(idx[i+1],idx[i])=-leds(idx[i+1],idx[i]);
          }
  }
  
}

void displayTime(uint8_t m, uint8_t h)
{
  FastLED.clear();
  fillBackInv = random8()%2;
  fillColor = !fillBackInv;
  colRandom = 1;
  colAdvance = random8()%20;
  if(fillBackInv)
  {
    colForeground = random8();
    leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1,  CHSV( colForeground, 255, 255));
  }
  h+=2;
  char buff[50];
  char pre[25] = "Es ist";  
  char post[5] = "";
//bMatrix bMat;
  //minuteLEDs = m%5; //hier oder woanders?
  displayIdx(iEsIst);
  switch(m/5){
    case 0:
      //display "Uhr"
      sprintf(post,"%s"," Uhr");
      displayIdx(iUhr);
      break;
    case 1:
      //display "5 nach"
      sprintf(pre, "%s %i nach", pre, m);
      displayIdx(iFuenfMin);
      displayIdx(iNach);
      break;
    case 2:
      //display "10 nach"
      sprintf(pre, "%s %i nach", pre, m);
      displayIdx(iZehnMin);
      displayIdx(iNach);
      break;
    case 3:
      //display "15 nach"
      sprintf(pre, "%s %i nach", pre, m);
      displayIdx(iViertel);
      displayIdx(iNach);
      break;
    case 4:
      //display "20 nach"
      sprintf(pre, "%s %i nach", pre, m);
      displayIdx(iZwanzig);
      displayIdx(iNach);
      break;
    case 5:
      //display "5 vor halb"
      sprintf(pre, "%s 5 vor halb", pre);
      displayIdx(iFuenfMin);
      displayIdx(iVor);
      h++;
      break;
    case 6:
      //display "halb"
      sprintf(pre, "%s halb", pre);
      displayIdx(iHalb);
      h++;
      break;
    case 7:
      //display "5 nach halb"
      sprintf(pre, "%s 5 nach halb", pre);
      displayIdx(iFuenfMin);
      displayIdx(iNach);
      displayIdx(iHalb);
      h++;
      break;
    case 8:
      //display "20 vor"
      sprintf(pre, "%s 20 vor", pre);
      displayIdx(iZwanzig);
      displayIdx(iVor);
      h++;
      break;
    case 9:
      //display "15 vor"
      sprintf(pre, "%s 15 vor", pre);
      displayIdx(iViertel);
      displayIdx(iVor);
      h++;
      break;
    case 10:
      //display "10 vor"
      sprintf(pre, "%s 10 vor", pre);
      displayIdx(iZehnMin);
      displayIdx(iVor);
      h++;
      break;
    case 11:
      //display "5 vor"
      sprintf(pre, "%s 5 vor", pre);
      displayIdx(iFuenfMin);
      displayIdx(iVor);
      h++;
      break;
    default:
      break;  
  }
  switch(h%12){
    case 0:
      //display "zwölf"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iZwoelf);
      break;
    case 1:
      //display "1"
      sprintf(buff, "%s %i%s",pre,h,post);
      if(m)
        displayIdx(iEins);
      else
        displayIdx(iEin);
      break;
    case 2:
      //display "2"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iZwei);
      break;
    case 3:
      //display "3"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iDrei);
      break;
    case 4:
      //display "4"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iVier);
      break;
    case 5:
      //display "5"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iFuenf);
      break;
    case 6:
      //display "6"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iSechs);
      break;
    case 7:
      //display "7"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iSieben);
      break;
    case 8:
      //display "8"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iAcht);
      break;
    case 9:
      //display "9"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iNeun);
      break;
    case 10:
      //display "10"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iZehn);
      break;
    case 11:
      //display "11"
      sprintf(buff, "%s %i%s",pre,h,post);
      displayIdx(iElf);
      break;
    default:
      break;  
  }
      Serial.println(buff);
      //leds[m] = CRGB::Red; 
      //leds[h] = CRGB::Blue;       
        FastLED.show(); 
}

void loop() {
  esp.Process();
  //rgb.update();      
    uint32_t now = millis();    
 
    if(now>next)
    {
      uint32_t t = GetTime(); 
      while(t==0)
        t = GetTime(); 
      uint8_t s=tSec(t);
      uint8_t m=tMin(t);
      uint8_t h=tHour(t);
      char buff[50];
      
      uint32_t delta = 60*(4-m%5)+60-s+3;//-prepTime; //3sekunden verzögert      
      uint32_t now = millis();
      next = now+1000*delta;
      sprintf(buff, "Time: %02d:%02d:%02d fehlen %i", h,m,s, delta);
      Serial.println(buff);
      displayTime(m,h);
    }
     // Serial.println("Time: %i",t);
      
  
  //if (connected && (millis()-last) > 4000) {
    //Serial.println("publishing");
    //char buf[12];

    //itoa(count++, buf, 10);
    //mqtt.publish("/esp-link/1", buf);

    //itoa(count+99, buf, 10);
    //mqtt.publish("/hello/world/arduino", "asd");

   // uint32_t t = cmd.GetTime();
    //Serial.print("Time: "); Serial.println(t);

  //  last = millis();
  //}
  
}


