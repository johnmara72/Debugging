#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
#include "wpa2_enterprise.h"
}

// SSID to connect to
// static const char* ssid = "eduroam";
// Username for authentification
// static const char* username = "...";
// Password for authentication
// static const char* password = "...";

#include "eduroamTEITHECA.h"
#include "Credentials.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("starting");
  delay(1000);
  
  // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(STATION_MODE);
 
  struct station_config wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
 
  wifi_station_set_config(&wifi_config);
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_set_wpa2_enterprise_auth(1);

  wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));
  wifi_station_set_enterprise_new_password((uint8*)password, strlen(password));

//  wifi_station_set_enterprise_ca_cert((byte*)ca_cert, strlen(ca_cert));
  
  Serial.println("Setting up wifi station");
  wifi_station_connect();
 
  // Wait for connection AND IP address from DHCP
  Serial.println();
  Serial.println("Waiting for connection and IP Address from DHCP");
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
// put your main code here, to run repeatedly:
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}
