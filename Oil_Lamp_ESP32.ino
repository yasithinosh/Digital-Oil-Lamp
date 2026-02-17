#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

// Replace with your network credentials
const char *ssid = "TECH_B";
const char *password = "VoidYasi";

// Create an instance of the web server running on port 80
WebServer server(80);

// Function prototype
void handleToggle();

void setup()
{
  // Start Serial Monitor
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 18, 19); // RX = 18, TX = 19

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("Failed to mount filesystem");
    return;
  }

  // Define routes
  server.on("/", []() {
    server.send(200, "text/html", generateHTML());
  });

  server.on("/toggle", []() {
    handleToggle();
  });

  server.on("/background.jpg", HTTP_GET, []() {
    File file = SPIFFS.open("/background.jpg", "r");
    if (!file)
    {
      server.send(404, "text/plain", "File not found");
      return;
    }
    server.streamFile(file, "image/jpg");
    file.close();
  });

  // Start server
  server.begin();
}

void loop()
{
  server.handleClient();
}

String generateHTML()
{
  String buttonHTML = "";
  for (int i = 1; i <= 20; i++)
  {
    buttonHTML += "<button class=\"button\" id=\"button" + String(i) + "\" data-state=\"OFF\" onclick=\"sendToggle(" + String(i) + ")\">";
    buttonHTML += "<img src=\"https://prhayvjhhvikyogvygja.supabase.co/storage/v1/object/public/images/3e267225-3d4a-4ca5-af36-e959ec9009ae/41688946-f69d-4900-a1fc-a2cef099d406.png">";
    buttonHTML += "</button>\n";
  }

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Digital Oil Lamp - ATIT</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        background-image: url('https://prhayvjhhvikyogvygja.supabase.co/storage/v1/object/public/images/3e267225-3d4a-4ca5-af36-e959ec9009ae/370f1e40-faea-4332-8f90-136bb88f068b.jpg');
        background-size: cover;
        background-position: center;
        background-repeat: no-repeat;
        background-attachment: fixed;
        color: white;
        margin: 0;
        padding: 0;
        min-height: 100vh;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
      }

      h2 {
        color: #000;
        margin-bottom: 50px;
        text-align: center;
        font-size:30px;
      }

      #buttons {
        display: grid;
        grid-template-columns: repeat(auto-fit, minmax(80px, 1fr));
        gap: 15px;
        width: 90%;
        max-width: 1000px;
        padding: 20px;
        border-radius: 10px;
      }

      .button {
        padding: 5px;
        border: none;
        background:transparent;
        border-radius: 8px;
        cursor: pointer;
        transition: transform 0.2s;
      }

      .button img {
        width: 80px;
        height: auto;
      }

      .button:hover {
        transform: scale(1.05);
      }

      @media (max-width: 1200px) {
        #buttons {
          grid-template-columns: repeat(auto-fit, minmax(100px, 1fr));
        }
      }

      @media (max-width: 768px) {
        .button img {
          width: 50px;
        }
      }

      @media (max-width: 480px) {
        .button img {
          width: 40px;
        }
      }
    </style>
  </head>
  <body>
    <h2>AMT AGM 2025</h2>
    <div id="buttons">
      %BUTTONS%
    </div>
    <script>
      function sendToggle(toggleNumber) {
        var xhr = new XMLHttpRequest();
        var button = document.getElementById("button" + toggleNumber);
        var state = button.getAttribute("data-state") === "ON" ? 0 : 1;
        xhr.open("GET", "/toggle?state=" + state + "&toggle=" + toggleNumber, true);
        xhr.onreadystatechange = function() {
          if (xhr.readyState == 4 && xhr.status == 200) {
            button.setAttribute("data-state", state === 1 ? "ON" : "OFF");
            button.innerHTML = "<img src='" + (state === 1
              ? "https://prhayvjhhvikyogvygja.supabase.co/storage/v1/object/public/images/3e267225-3d4a-4ca5-af36-e959ec9009ae/8cef0d3e-23f4-4518-a3e0-144c369772f0.png"
              : "https://prhayvjhhvikyogvygja.supabase.co/storage/v1/object/public/images/3e267225-3d4a-4ca5-af36-e959ec9009ae/41688946-f69d-4900-a1fc-a2cef099d406.png") + "'>";
          }
        };
        xhr.send();
      }
    </script>
  </body>
  </html>
  )rawliteral;

  html.replace("%BUTTONS%", buttonHTML);
  return html;
}

void handleToggle()
{
  if (server.hasArg("state") && server.hasArg("toggle"))
  {
    int toggleNumber = server.arg("toggle").toInt();
    int state = server.arg("state").toInt();
    if (toggleNumber >= 1 && toggleNumber <= 30)
    {
      String toggleStateStr = state == 1 ? "ON" : "OFF";
      Serial1.println(String(toggleNumber) + ":" + toggleStateStr);
      server.send(200, "text/plain", "OK");
    }
    else
    {
      server.send(400, "text/plain", "Invalid Toggle Number");
    }
  }
  else
  {
    server.send(400, "text/plain", "Bad Request");
  }
}
