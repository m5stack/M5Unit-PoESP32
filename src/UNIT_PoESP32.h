
#include <Arduino.h>

typedef enum { HEAD = 1, GET, POST, PUT, DELETE } http_method_t;
typedef enum {
    APPLICATION_X_WWW_FORM_URLENCODED = 0,
    APPLICATION_JSON,
    MULTIPART_FORM_DATA,
    TEXT_XML
} http_content_t;

class UNIT_PoESP32 {
   private:
    HardwareSerial *_serial;
    String _readstr;

   public:
    void Init(HardwareSerial *serial = &Serial2, unsigned long baud = 9600,
              uint8_t RX = 16, uint8_t TX = 17);
    String waitMsg(unsigned long time);
    void sendCMD(String command);
    bool checkDeviceConnect();
    bool checkETHConnect();
    bool checkMQTTConnect();

    bool createTCPClient(String ip, int port);
    bool sendTCPData(uint8_t *buffer, size_t size);

    bool createMQTTClient(String host = "host", String port = "port",
                          String clientId  = "client id",
                          String user_name = "user", String user_pwd = "pwd");
    bool publicMQTTMsg(String topic, String payload, String qos = "0");
    bool subscribeMQTTMsg(String topic, String qos = "0");

    String createHTTPClient(
        http_method_t method        = GET,
        http_content_t content_type = APPLICATION_X_WWW_FORM_URLENCODED,
        String url = "", String payload = "");
};