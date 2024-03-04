# 实现非阻塞式输入功能，实际应用中可以删除此部分代码
# Non-blocking input implementation, can be removed in practical applications
from time import sleep
from select import select
from sys import stdin

# 引入RDK X3的串口库
# Import the serial library for RDK X3
from serial import Serial

def main():
    # 初始化并打开RDK X3的串口，波特率为115200
    # Initialize and open the serial port for RDK X3 with a baud rate of 115200
    try:
        x3_serial = Serial("/dev/ttyS3", 115200, timeout=1)
    except Exception as e:
        print("Open Serial /dev/ttyS3 failed!\n")
        exit()
    print("Open serial Successfully\n")
    # 程序主循环
    # Main program loop
    while True:
        # 检查Serial2是否有数据可读，若有直到接收到换行符\n时接收数据
        # Check if there is any data to read from Serial2, and receive data until encountering newline '\n'
        if x3_serial.in_waiting:
            data_receive_from_uart = x3_serial.read_until(b"\n").decode('UTF-8')
            print("\033[31m" + "--> RDK X3 Received Message From ESP32: \n%s"%data_receive_from_uart + "\033[0m")

        # 检查系统标准输入（键盘）是否有回车输入，如果有，则捕获并发送到串口
        # Check if there's an enter key input from system standard input (keyboard), capture and send it to the serial port if so
        r, w, e = select([stdin], [], [], 0.0)
        if r:
            data_receive_from_shell = stdin.readline()
            print()
            # 在应用中，你可以随时发送
            # you can send message anytime
            x3_serial.write(data_receive_from_shell.encode('UTF-8'))
    
        # 等待1秒，假设你要做其他的事情，例如视频帧的处理
        # Delay for 0.001 seconds to allow time for other operations such as video frame processing
        sleep(0.001)

if __name__ == "__main__":
    main()
