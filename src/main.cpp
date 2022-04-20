#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

static String WIFI_SSID = "<SSID>";
static String WIFI_PASS = "<PASSWORD>";
static String MQTT_USER = "test1";
static String MQTT_PASS = "test1";

void save();
void read();

void setup()
{
    Serial.begin(115200);
    while (!Serial) { };
}

void loop()
{
    if (Serial.available()) {
        char c = (char) Serial.read();
        if (c == 's') {
            save();
            return;
        }
        if (c == 'r') {
            read();
            return;
        }
        Serial.println("Unknown command");
    }
}

void save()
{
    preferences.begin("credentials", false);

    Serial.print("Saving...");
    preferences.putString("wifi.ssid", WIFI_SSID);
    preferences.putString("wifi.pswd", WIFI_PASS);
    preferences.putString("mqtt.user", MQTT_USER);
    preferences.putString("mqtt.pass", MQTT_PASS);
    Serial.println("done");

    preferences.end();
}

void read()
{
    preferences.begin("credentials", true);

    String wifiSSID = preferences.getString("wifi.ssid");
    String wifiPass = preferences.getString("wifi.pswd");
    if (wifiSSID.isEmpty() || wifiPass.isEmpty()) {
        Serial.println("No WiFi credentials");
    } else {
        Serial.println("WiFi credentials:");
        Serial.println(" - SSID = " + wifiSSID);
        Serial.println(" - PSWD = " + wifiPass);
    }

    String mqttUser = preferences.getString("mqtt.user");
    String mqttPass = preferences.getString("mqtt.pass");
    if (mqttUser.isEmpty() || mqttPass.isEmpty()) {
        Serial.println("No MQTT credentials");
    } else {
        Serial.println("MQTT credentials:");
        Serial.println(" - USER = " + mqttUser);
        Serial.println(" - PSWD = " + mqttPass);
    }

    preferences.end();
}