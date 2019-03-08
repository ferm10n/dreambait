#include <DNSServer.h>
#include <ESP8266WebServer.h>

struct CaptivePortal {
  DNSServer dnsServer;
  ESP8266WebServer webServer;

  CaptivePortal () : webServer(80) {}

  void setup (IPAddress softApIP) {
    dnsServer.start(53, "*", softApIP);
    webServer.onNotFound([&]() {
      servePortal();
    });
    webServer.begin();
  }

  void loop () {
    dnsServer.processNextRequest();
    webServer.handleClient();
  }

  void servePortal () {
    webServer.send(200, "text/plain", "Hello world");
  }
};
