\# Waste Level Monitoring (Arduino) — P2339096



A simple Arduino project that measures \*\*waste/bin fill level\*\* using an \*\*ultrasonic distance sensor\*\*.  

The sketch reads the distance to the surface inside the bin and outputs the result via \*\*Serial Monitor\*\* (and can be extended to alerts or IoT).



---



\## 📁 Files





---



\## 🔧 Hardware Required



\- Arduino board (Uno / Nano / Mega, etc.)

\- Ultrasonic sensor \*\*HC-SR04\*\*

\- Jumper wires

\- Breadboard (optional)

\- USB cable / power source



---



\## 🔌 Wiring (Typical HC-SR04 → Arduino)



| HC-SR04 Pin | Arduino Pin |

|------------|-------------|

| VCC        | 5V          |

| GND        | GND         |

| TRIG       | (set in code) |

| ECHO       | (set in code) |



> If your TRIG/ECHO pins are different, update the pin numbers in the sketch.



---



\## ⚙️ How It Works



1\. Arduino sends a short pulse on \*\*TRIG\*\*

2\. Sensor returns pulse width on \*\*ECHO\*\*

3\. Arduino converts pulse time → \*\*distance (cm)\*\*

4\. Distance can be interpreted as:

&nbsp;  - \*\*Empty\*\* (large distance)

&nbsp;  - \*\*Half\*\* (medium distance)

&nbsp;  - \*\*Full\*\* (small distance)



---



\## ▶️ How to Run



1\. Open \*\*Arduino IDE\*\*

2\. Open `Waste\_Level\_P2339096.ino`

3\. Select:

&nbsp;  - \*\*Tools → Board\*\* (your Arduino model)

&nbsp;  - \*\*Tools → Port\*\* (correct COM port)

4\. Upload the sketch

5\. Open \*\*Tools → Serial Monitor\*\*

6\. Set baud rate to match the code (commonly `9600` or `115200`)

7\. Observe live distance / level readings



---



\## ✅ Notes / Tips



\- For best readings, mount the sensor facing straight down into the bin.

\- Soft or angled surfaces can cause unstable readings — use averaging if needed.

\- This project can be extended with:

&nbsp; - LCD display (real-time level)

&nbsp; - Buzzer/LED alerts when “full”

&nbsp; - IoT upload (ThingSpeak / MQTT / Firebase)



---



\## 👤 Author



\*\*La Wun Shun Lett\*\*  

Arduino / Embedded Systems



---



\## 📜 License



Educational use. Feel free to learn from and adapt this project with credit.



