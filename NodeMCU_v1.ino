//v1

#include <ESP8266WiFi.h>

const char* ssid     = "Zmaj Wi-Fi";
const char* password = "88888888";

WiFiServer server(80);
IPAddress ip(192, 168, 5, 105);            // Server
IPAddress gateway(192, 168, 5, 1);        // Gateway
IPAddress subnet(255, 255, 255, 0);       // Subnet mask nesto


String header;


String output13stanje = "off";
String output12stanje = "off";
String output14stanje = "off";
String output2stanje = "off";
String output0stanje = "off";
String output4stanje = "off";
String output5stanje = "off";
String output16stanje = "off";

//

const int output13 = 13;
const int output12 = 12;
const int output14 = 14;
const int output2 = 2;
const int output0 = 0;
const int output4 = 4;
const int output5 = 5;
const int output16 = 16;

//

void setup() {
  Serial.begin(145200);
  //
  pinMode(output13, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output16, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output13, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output16, LOW);

  //
  Serial.print("Povezivanje... ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi povezan.");
  Serial.println("IP adresa: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13stanje = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13stanje = "off";
              digitalWrite(output13, LOW);
            }

            else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12stanje = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12stanje = "off";
              digitalWrite(output12, LOW);
            }

            else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14stanje = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14stanje = "off";
              digitalWrite(output14, LOW);
            }

            //2

            else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2stanje = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2stanje = "off";
              digitalWrite(output2, LOW);
            }

            //

            //0

            else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0stanje = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0stanje = "off";
              digitalWrite(output0, LOW);
            }

            //

            //4

            else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4stanje = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4stanje = "off";
              digitalWrite(output4, LOW);
            }

            //

            //5
            else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5stanje = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5stanje = "off";
              digitalWrite(output5, LOW);
            }

            //

            //16
            else if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16stanje = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16stanje = "off";
              digitalWrite(output16, LOW);
            }
            //


            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>NodeMCU Web Server</h1>");

            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 13 - stanje " + output13stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output13stanje == "off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current stanje, and ON/OFF buttons for GPIO 4
            client.println("<p>GPIO 12 - stanje " + output12stanje + "</p>");
            // If the output12stanje is off, it displays the ON button
            if (output12stanje == "off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 14 - stanje " + output14stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output14stanje == "off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            //
            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 2 - stanje " + output2stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output2stanje == "off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //

            //
            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 0 - stanje " + output0stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output0stanje == "off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //
            //
            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 4 - stanje " + output4stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output4stanje == "off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //
            //
            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 5 - stanje " + output5stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output5stanje == "off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //
            //
            // Display current stanje, and ON/OFF buttons for GPIO 5
            client.println("<p>GPIO 16 - stanje " + output16stanje + "</p>");
            // If the output13stanje is off, it displays the ON button
            if (output16stanje == "off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    //
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
