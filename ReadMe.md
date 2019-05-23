
# OPENLAB (IoT Temperature Sensor, Episode 1)

## Instructions initial setup of the prototype

## [Estimated setup time : 15-20 minutes]
**NB: _Call for help if your group realizes that its taking or going to take more time than estimated to setup_**

* Install the [Arduino IDE](https://www.arduino.cc/en/Main/Software) on your machine. Alternatively an online [IDE](https://create.arduino.cc/) can be used for this task.
* Configure the Arduino IDE to work with the ESP8266. Follow the instructions in [this](https://github.com/esp8266/Arduino)  link
* Download and unzip the [OneWire](OneWire.zip) library into the Arduino libraries folder on your machine.
* Download and unzip the [DallasTemperature](DallasTemperature.zip) library into the Arduino libraries folder on your machine.
* Analyze the code in the [Temperature.ino](Temperature.ino) arduino file. In the file, change your Network SSID to match a desired unique name.
* Connect your device to your computer through a mini usb device provided to you.
* Upload the Temperature.ino sketch to the device.
* Open the serial monitor and check out which IP address that shows up. That is the IP address that will be used to access your device bia a web browser
