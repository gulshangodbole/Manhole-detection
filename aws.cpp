/*===================================================================================================
 *Project Name : Manhole Indication System 
 *Author List : Sankalp Singh
 *Filename : aws.cpp
 *Functions : callback(char*, byte*, unsigned int), setup_wifi(), reconnect(), setupAWS(), web(int)
 *Global Variables : lastMsg, msg[], mac[6], mac_Id[18], ssid, password, AWS_endpoint
===================================================================================================*/

#include "FS.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "declaration.h"
#include "switchoffline.h"
#include "aws.h"
#include "motor_control.h"

//ssid -> Stores the SSID of the the WiFi network 
const char* ssid = "SnS";

//password -> Stores the password of the WiFi network
const char* password = "samop2000";

switchoffline test;
motor_control motorObjAWS;

#define BUFFER_LEN 256

//lastMsg -> This variables stores the time when the last message was received
long lastMsg = 0;

//msg[BUFFER_LEN] -> This array stores the message to be sent to the AWS IoT core
char msg[BUFFER_LEN];

//mac[6] -> This byte array stores the mac id generated 
byte mac[6];

//mac_Id[18] -> This char array stores the mac id in char form which is then sent to the AWS IoT Core
char mac_Id[18];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//AWS_endpoint -> This variable stores the MQTT broker IP Address
const char* AWS_endpoint = "a6vtmbll1wgmr-ats.iot.us-west-2.amazonaws.com";

/*=============================================================================================================================
 * Function Name : callback
 * Input : topic -> It contains the name of the topic to which our device receives messages on, payload -> It contains the 
 *         payload to be processed, length -> It contains the length of the payload 
 * Output : NONE
 * Logic : This function is used for receiving data on the ESP from the website. It is automatically called in the web function 
 * Example Call : NONE
===============================================================================================================================*/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: ");
  Serial.println(topic);
  
  //count -> This variable iterates for the values that are between 0 and length - 1
  for (int count = 0; count < length; count++) {
    Serial.print((char)payload[count]);
    if((char)payload[count]=='0'){
      //Sending the value to tell the system to go down
      motorObjAWS.operate(1);
    }
    else if((char)payload[count]=='1'){
      //Sending the value to tell the system to go up
      motorObjAWS.operate(0);
    }
  }
  Serial.println();

}

WiFiClientSecure espClient;
PubSubClient client(AWS_endpoint, 8883, callback, espClient);

/*=============================================================================================================================
 * Function Name : setup_wifi
 * Input : NONE
 * Output : NONE
 * Logic : In this function we use the WiFI objects for connecting to the network if available and when it isn't connected to 
 *         the internet till then the offline switching library object calls the switching1 
 * Example Call : obj.setup_wifi();
==============================================================================================================================*/

void aws :: setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    test.switching_offline();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  espClient.setX509Time(timeClient.getEpochTime());
}

/*==============================================================================================================================
 * Function Name : reconnect
 * Input : NONE
 * Output : NONE
 * Logic : In this function it checks that whether the MQTT connection is still established or not and if it isn't then the ESP 
 *         attemts MQTT connection till it is established
 * Example Call : obj.reconnect();
================================================================================================================================*/

void aws :: reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    test.switching_offline();
    // Attempt to connect
    if (client.connect("ESPthing")) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("inTopicESP1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*===========================================================================================================================
 * Function Name : setupAWS
 * Input : NONE
 * Output : NONE
 * Logic : In this function the certificates are checked using if else statements and also the WiFi connect is established 
 *         when the setup_wifi() function is called also the mac address of the ESP is retrived and stored in the array
 * Example Call : obj.setupAWS();
============================================================================================================================*/

void aws :: setupAWS() {
  //Calling the wifi function for connecting to the wifi
  setup_wifi();
  delay(1000);
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());

  // Load certificate file
  File cert = SPIFFS.open("/cert.der", "r"); //replace cert.crt eith your uploaded file name
  if (!cert) {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Success to open cert file");

  delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");

  // Load private key file
  File private_key = SPIFFS.open("/private.der", "r"); //replace private eith your uploaded file name
  if (!private_key) {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Success to open private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");

  // Load CA file
  File ca = SPIFFS.open("/ca.der", "r"); //replace ca eith your uploaded file name
  if (!ca) {
    Serial.println("Failed to open ca ");
  }
  else
    Serial.println("Success to open ca");

  delay(1000);

  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());

  //===========================================================================
  WiFi.macAddress(mac);
  snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print(mac_Id);
  //============================================================================
}

/*==========================================================================================================================
 * Function Name : web
 * Input : state -> It contains the current state of the button
 * Output : NONE
 * Logic : This function checks for the MQTT connection and if the connection is broken then it calls the reconnect function
 *         it also creates a msg to be published by using the snprintf() function and the store it to msg variable
 * Example Call : obj.web(1);
============================================================================================================================*/

void aws :: web(int state) {
  int offset = 20;
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(WiFi.status() != WL_CONNECTED)
    setup_wifi();
    
  //now -> It stores the time transpired
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    //macIdStr -> It stores the mac id of the ESP in the String format
    String macIdStr = mac_Id;

    //volt -> This variable stores the value given by the voltage sensor
    int volt = analogRead(A0);

    //voltage_map -> This variable maps the value and returns the voltage value
    double voltage_map = map(volt,0,1023, 0, 2500) + offset;

    //temp -> This variable stores the volatage in String format
    String temp = String(voltage_map);

    //voltage -> It stores the voltage value into char array
    const char* voltage = temp.c_str();
    
    snprintf (msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"state\" : %d, \"voltage\" : \"%s\"}", macIdStr.c_str(), state, voltage);

    Serial.print("Publish message: ");
    Serial.println(msg);
    //The publish function publishes the message on the outTopicESP1 topic
    client.publish("outTopicESP1", msg);
    //=============================================================================
    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  }
}
