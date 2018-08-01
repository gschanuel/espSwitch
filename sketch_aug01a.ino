#include <ESP8266WiFi.h>
 
const char* ssid = "FC552588";
const char* password = "fc552588";
 
int portaPin = 4; 
int garagemPin = 5; 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(portaPin, OUTPUT);
  digitalWrite(portaPin, LOW);
  pinMode(garagemPin, OUTPUT);
  digitalWrite(garagemPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

     //initialize variable
  
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("garagem=on") != -1)  {
    digitalWrite(garagemPin, LOW);
  }
  if (request.indexOf("garagem=on") == -1)  {
    digitalWrite(garagemPin, HIGH);
  }


  if (request.indexOf("porta=on") != -1)  {
    digitalWrite(portaPin, HIGH);
  }
  if (request.indexOf("porta=on") == -1)  {
    digitalWrite(portaPin, LOW);
  }


 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response


  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
client.println("<style>");
client.println("    .onoffswitch {");
client.println("        position: relative; width: 192px;");
client.println("        -webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;");
client.println("    }");
client.println("    .onoffswitch-checkbox {");
client.println("        display: none;");
client.println("    }");
client.println("    .onoffswitch-label {");
client.println("        display: block; overflow: hidden; cursor: pointer;");
client.println("        border: 2px solid #FFFFFF; border-radius: 50px;");
client.println("    }");
client.println("    .onoffswitch-inner {");
client.println("        display: block; width: 200%; margin-left: -100%;");
client.println("        transition: margin 0.3s ease-in 0s;");
client.println("    }");
client.println("    .onoffswitch-inner:before, .onoffswitch-inner:after {");
client.println("        display: block; float: left; width: 50%; height: 41px; padding: 0; line-height: 41px;");
client.println("        font-size: 25px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;");
client.println("        box-sizing: border-box;");
client.println("    }");
client.println("    .onoffswitch-inner:before {");
client.println("        content: \"ON\";");
client.println("        padding-left: 14px;");
client.println("        background-color: #EEEEEE; color: #34A7C1;");
client.println("    }");
client.println("    .onoffswitch-inner:after {");
client.println("        content: \"OFF\";");
client.println("        padding-right: 14px;");
client.println("        background-color: #EEEEEE; color: #999999;");
client.println("        text-align: right;");
client.println("    }");
client.println("    .onoffswitch-switch {");
client.println("        display: block; width: 38px; margin: 1.5px;");
client.println("        background: #A1A1A1;");
client.println("        position: absolute; top: 0; bottom: 0;");
client.println("        right: 147px;");
client.println("        border: 2px solid #FFFFFF; border-radius: 50px;");
client.println("        transition: all 0.3s ease-in 0s; ");
client.println("    }");
client.println("    .onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner {");
client.println("        margin-left: 0;");
client.println("    }");
client.println("    .onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch {");
client.println("        right: 0px; ");
client.println("        background-color: #34A7C1; ");
client.println("    }");
client.println("</style>");

client.println(request.indexOf("porta=on"));
client.println(request.indexOf("garagem=on"));
client.println("<form name=\"form\" action=\"\" method=\"GET\">");
client.println("    <div class=\"onoffswitch\">");
client.print("        <input onclick=\"document.form.submit()\" type=\"checkbox\" name=\"porta\" class=\"onoffswitch-checkbox\" id=\"porta\"");
if (request.indexOf("porta=on") != -1){
    client.print( " checked " );
}
client.print(">");
client.println("        <label class=\"onoffswitch-label\" for=\"porta\">");
client.println("            <span class=\"onoffswitch-inner\"></span>");
client.println("            <span class=\"onoffswitch-switch\"></span>");
client.println("        </label>");
client.println("</div>");
client.println("    <div class=\"onoffswitch\">");

client.print("        <input onclick=\"document.form.submit()\" type=\"checkbox\" name=\"garagem\" class=\"onoffswitch-checkbox\" id=\"garagem\"");
if (request.indexOf("garagem=on") != -1){
    client.print( " checked " );
}
client.println(">");
client.println("        <label class=\"onoffswitch-label\" for=\"garagem\">");
client.println("            <span class=\"onoffswitch-inner\"></span>");
client.println("            <span class=\"onoffswitch-switch\"></span>");
client.println("        </label>   ");     
client.println("</form>");


client.println("</html>");
}

