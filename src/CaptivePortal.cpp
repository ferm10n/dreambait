#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP.h>

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
        String fileName = dir.fileName();
        Serial.println(fileName);
      }
      Serial.print('\r');
    }
    dnsServer.start(53, "*", softApIP);
    webServer.onNotFound([&]() {
      if (!handleFileRead(webServer.uri())) {
        webServer.sendHeader("Location", "/index.html");
        webServer.send(302, "text/plain", "");
        Serial.println("sending redirect");
      }
      // servePortal();
    });
    webServer.begin();
  }

  void loop () {
    dnsServer.processNextRequest();
    webServer.handleClient();
    Serial.print('.');
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
      int fileSize = file.size();
      Serial.println(fileSize);
      int bytesRemaining = fileSize;
      webServer.sendHeader("Content-Length", (String) fileSize);
      
      int minBuffer = 1;
      int maxBuffer = ESP.getFreeHeap() * .66;
      while (bytesRemaining > 0) {
        int buffSize = maxBuffer;
        if (buffSize < minBuffer) {
          buffSize = minBuffer;
        }
        if (buffSize > bytesRemaining) {
          buffSize = bytesRemaining;
        }

        char* buff = (char*) malloc(buffSize);
        file.readBytes(buff, buffSize);
        bytesRemaining -= buffSize;
        Serial.print("remaining ");
        Serial.println(bytesRemaining);
        webServer.sendContent_P(buff, buffSize);
        free(buff);
      }
      
      // for (int i = 0; i < fileSize; i++) {
      //   char buff[1];
      //   file.readBytes(buff, 1);
      //   if (i % 256 == 0) {
      //     Serial.println(ESP.getFreeHeap());
      //     yield();
      //   }
      //   webServer.sendContent_P(buff, 1);
      // }
      
      // size_t sent = webServer.streamFile(file, contentType);
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
