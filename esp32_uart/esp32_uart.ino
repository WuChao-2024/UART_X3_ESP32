void setup() {
  // 启动ESP32的调试串口Serial-0
  // Start ESP32 Debug Serial-0
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial 0 init successfully.");
  // 启动用于X3的Serial-2
  // Start Serial-2 for X3
  Serial2.begin(115200);
  while (!Serial2);
  Serial.println("Serial 2 init successfully.");
  int cnt = 1;
  // 程序主循环
  // Main program loop
  while (true) {
    // 以下程序将检查ESP32 Debug串口的输入，如果你有回车输入动作，则会捕获输入并发送
    // 在应用中，你可以直接使用Serial2.println函数，将字符串发送到串口
    if (Serial.available()) {
      String data_receive_from_DebugSerial = Serial.readStringUntil('\n');
      Serial2.println(data_receive_from_DebugSerial);
    }
    // 从Serial2接收数据，一直接收到\n
    // Receive data from Serial2 until \n
    if (Serial2.available()) {
      String data_receive_from_uart = Serial2.readStringUntil('\n');
      Serial.print("--> ESP32 Received Message From RDK X3: \n" + data_receive_from_uart);
      Serial.println();
    }
    //等待0.01秒，假设你要做其他的事情，例如小车的PID巡线控制或处理传感器数据
    // Delay for 0.01 seconds to allow time for other operations such as PID line-following control of a car or sensor data processing
    delay(10);
  }
}

void loop() {
}
