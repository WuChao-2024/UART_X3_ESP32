void setup() {
  // 启动ESP32的调试串口Serial0
  // Start ESP32 Debug Serial0
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial 0 init successfully.");
  // 启动用于X3的Serial2
  // Start Serial2 for X3
  Serial2.begin(115200);
  while (!Serial2);
  Serial.println("Serial 2 init successfully.");
  int cnt = 1;
  // 程序主循环
  while (true) {
    // 调试信息
    // Debug Message
    Serial.print("loop: "); Serial.println(cnt);
    cnt ++;
    String data = "AA55";
    Serial.println("Data Send:" + data);
    Serial.print("Data Receive:");
    // 向Serial2发送数据
    // Send data to Serial2
    Serial2.println(data);
    delay(10);
    // 从Serial2接收数据，直到缓冲区为空
    // Receive data from Serial2 until its buffer is empty
    while (Serial2.available()) {
      char data_rx = Serial2.read();
      Serial.print(data_rx);
    }
    Serial.println();
    delay(1000);
  }
}

void loop() {
}
