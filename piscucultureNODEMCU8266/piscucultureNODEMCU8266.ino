#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <Servo.h>

const char *ssid = "samaki ya kwetu";
const char *password = "samakiyakwetu";


SoftwareSerial NanoSerial(D1, D2);
ESP8266WebServer server(80);
long temps;
float tm;
String dataIn;
String c;
String data1pH,data2TDS,data3EC,data4CM,data5GAZ,data6Temp;

Servo  portefenetre;
//float tm=0.00;
void setup() {
  Serial.begin(115200);
  NanoSerial.begin(115200);
  portefenetre.attach(D3);

  portefenetre.write(80);

  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.println(F("erreur 2329"));
  //   delay(500);
  // }
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/portefenetreon", handleouvertureporte);
  server.on("/portefenetreoff", handlefermetureporte);
  server.begin();

  //IPAddress myIP = WiFi.localIP();
  IPAddress myIP = WiFi.softAPIP();
  Serial.print(myIP);
   temps = millis();
}

void loop() {
 LecturaTH();
  server.handleClient();
}

// creamos la funcion Estructura HTML
void handleRoot() {
  server.send(200, "text/html",
   "<html><head><title>DASHBOARD DU PISCUCUTURE</title><meta name='viewport' content='width=device-width, initial-scale=1'>"
   "<link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>"
"<link rel='icon' href='data:,'>"
"<style>"
    "html {font-family: Arial; display: inline-block; text-align: center;} p {  font-size: 1.2rem;}"
    "body {  margin: 0;} .topnav { overflow: hidden; background-color: #1f71ff; color: white; font-size: 1.7rem; }.content { padding: 20px; }"
    ".card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }"
    ".cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }"
    ".reading { font-size: 2.8rem; }.packet { color: #bebebe; }.card.temperature { color: #fd7e14; }.card.humidity { color: #1b78e2; }"
    ".card.temperature1 { color: #045c29; }"
    ".highcharts-figure,.highcharts-data-table table {min-width: 310px;max-width: 800px;margin: 1em auto;}#container {height: 480px;}"
    ".highcharts-data-table table {font-family: Verdana, sans-serif;border-collapse: collapse;border: 1px solid #ebebeb;margin: 10px auto;text-align: center;width: 100%;max-width: 500px;}"
    ".highcharts-data-table caption { padding: 1em 0;  font-size: 1.2em;  color: #555;}"
    ".highcharts-data-table th {font-weight: 600;padding: 0.5em;}"
    ".highcharts-data-table td,.highcharts-data-table th,.highcharts-data-table caption { padding: 0.5em;}"
    ".highcharts-data-table thead tr,.highcharts-data-table tr:nth-child(even) { background: #f8f8f8;}"
    ".highcharts-data-table tr:hover {  background: #f1f7ff;}"
    ".card.humidity1 { color: #ff1919; }.card.temperature2 { color: #abfd14; }.card.humidity2 { color: #e21bb7; }"
    "</style>"
    "</head><meta http-equiv='refresh' content='5' charset='UTF-8'>"
    "<body> <div class='topnav'>   <h3>DASHBOARD DE LA PISCUCUTURE</h3> </div>"
    "<div class='content'>  <div class='cards'>   <div class='card temperature'>"
    "<h4><i class='fas fa-thermometer-half'></i>TEMPERATURE</h4><p><span class='reading'><span id='t1'></span>"+ String(data6Temp) + "  &deg;C</span></p> </div>"
    "<div class='card humidity'> <h4><i class='fas fa-thermometer-half'></i>pH</h4><p><span class='reading'>"+ String(data1pH) + "  pH</span></p></div>"
    "<div class='card temperature1'><h4><i class='fas fa-thermometer-half'></i> TDS</h4><p><span class='reading'> "+ String(data2TDS) + " ppm</span></p></div><div class='card humidity1'>"
    "<h4><i class='fas fa-thermometer-half'></i> EC</h4><p><span class='reading'>"+ String(data3EC) + "  mv &sup2;</span></div><div class='card humidity2'>"
    "<h4><i class='fas fa-thermometer-half'></i> Litre</h4><p><span class='reading'>"+ String(data4CM) + "  L</span></p>"
    "</div><div class='card temperature2'> <h4><i class='fas fa-thermometer-half'></i>  GAZ</h4><p><span class='reading'> "+ String(data5GAZ) + "mg/L;</span></p>"
    "</div><td> <a href='portefenetreon'> <button style='background-color: green ; width:250px ; height:50px ;border-radius:15px'> <h4> OUVERTURE </h4> </button> </a> </td> "
    "<td > <a href='portefenetreoff'> <button style='background-color: red ; width:250px ; height:50px ;border-radius:15px'> <h4> FERMETURE </h4> </button> </a> </td>"
    "</div></div>"

//     "<script src='https://code.highcharts.com/highcharts.js'></script>"
//     "<script src='https://code.highcharts.com/themes/high-contrast-light.js'></script>"
//     "<script src='https://code.highcharts.com/modules/exporting.js'></script>"
//     "<script src='https://code.highcharts.com/modules/export-data.js'></script>"
//     "<script src='https://code.highcharts.com/modules/series-label.js'></script>"
//     "<script src='https://code.highcharts.com/modules/accessibility.js'></script>"
//     "<figure class='highcharts-figure'>"
//     "<div id='container'></div>"
// "<script> Highcharts.chart('container', {chart: {  type: 'spline' }, accessibility: {point: { descriptionFormatter: function (p) {  return p.series.name + ', ' + p.category + ', ' + p.y + '°C.';}}},title: { text: 'Evolution de different mesure samaki ya kwetu '},subtitle: {text: 'Source: samaki.com' },"
// "xAxis: {categories: [    'Januar',    'February',      'March',      'April',     'May',   'June',    'July',    'August','September','October' ],  crosshair: true},"
// "yAxis: {min: 0,title: {text: 'Temperature' }},tooltip: {headerFormat: '<span style='font-size: 10px'>{point.key} poissons </span><br/>',valueSuffix: ' '},"
// "plotOptions: {column: { pointPadding: 0.2,borderWidth: 0}},"
// "series: [{name: 'Temperature',data: [20.7, 21.5, 22, 24.8, 24.8, 29.2, 30.6, 31.8, 30.9, 21.9] },{  name: 'ph', data: [8.4, 7.8, 6.5, 5.8, 4.4, 3.5, 4.5, 9.2, 10.7, 9.5]"
// "}, {name: 'gaz',data: [12.2, 23.8, 25.5, 21.2, 25.0, 24.8, 29.1, 36.7, 28.5, 26.6] }, {  name: 'litre',data: [1.5, 2.1, 3.1, 4.2, 2.7, 2.1, 3.0, 3.0, 8.5, 4.2]"
// " },{name: 'tds',data: [465.5, 467.1, 572.1, 579.2, 586.7, 590.1, 595.0, 595.0, 590.5, 584.2]},{ name: 'ec',data: [1.5, 1.1, 1.1, 1.2, 1.7, 1.1, 1.0, 1.0, 1.1, 1.2,]}]});"
// "</script>"
// "<p class='highcharts-description'>Le tableau suivant illustre certaines fonctionnalités d’accessibilité de evolution de poissons, y compris l’utilisation de l’option.</p>"
// "</figure>"
"</body></html>");
}

// funcion de lectura de temperatura y humedad
void LecturaTH() {
  if(NanoSerial.available()>0){
    c=NanoSerial.readString();

    

    Serial.println(c);
    envoie_donner();
    
    Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

}
}
