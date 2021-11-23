# Firmware-over-the-air
Update your MCU's flash code remotely over the web. 
## What is FOTA?
It's a SW that is used to flash MCU (update MCU code) wirelessly over internet.

## Components Used
1. stm32f103 MCU
2. ESP8266 MCU
3. Flask as web server

## How to get started?
1. Download repo code ``` git clone "https://github.com/ahmedFarouk2020/Firmware-over-the-air.git" ```
2. Install requirements.txt ``` pip install -r requirements.txt ```
3. Get HW components mentioned above

## Important Features
1. 2 Separate Banks (rooms) so if download fails in the middle you can go back to the old code
2. Smooth transitions betwen banks

