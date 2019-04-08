#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>

struct CaptivePortal {
  DNSServer dnsServer;
  ESP8266WebServer webServer;

  CaptivePortal () : webServer(80) {}

  void setup (IPAddress softApIP) {
    SPIFFS.begin();
    Serial.println("SPIFFS started. Contents:");
    {
      Dir dir = SPIFFS.openDir("/");
      while (dir.next()) {                      // List the file system contents
        Serial.println("neat");
        String fileName = dir.fileName();
        Serial.println(fileName);
      //   size_t fileSize = dir.fileSize();
      //   Serial.printf("\tFS File: %s,\tsize: %s\r\n", fileName.c_str());
      }
      Serial.print('\r');
    }
    dnsServer.start(53, "*", softApIP);
    webServer.onNotFound([&]() {
      if (!handleFileRead(webServer.uri())) {
        webServer.send(404, "text/plain", "404: Not Found :(");
      }
      // servePortal();
    });
    webServer.begin();
  }

  void loop () {
    dnsServer.processNextRequest();
    webServer.handleClient();
  }

  bool handleFileRead (String path) {
    if (path.endsWith("/")) {
      path += "index.html";
    }
    Serial.print("Requested ");
    Serial.println(path);
    String contentType = getContentType(path);
    if (SPIFFS.exists(path)) {
      File file = SPIFFS.open(path, "r");
      Serial.print("Streaming ");
      Serial.println(path);
      size_t sent = webServer.streamFile(file, contentType);
      file.close();
      Serial.print("Done sending ");
      Serial.println(path);
      return true;
    }
    Serial.println("not found");
    return false;
  }

  String getContentType(String filename){
    if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".svg")) return "image/svg+xml";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
  }

  // void servePortal () {
  //   webServer.send(200, "text/plain", "Hello world");
  // }
};
