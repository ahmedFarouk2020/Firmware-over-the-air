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

## Future Improvements
1. Authentication (using username and password provided by author) --> already implemented
2. Data Encryption and decryption (security management)
3. Data integrity check --> already implemented

>> First of all, Burn *.hex file* in **FOTA-firmware/Debug** on your MCU
<!--
>> Copy the file "FOTA-firmware/ldscripts/mem.ld" **before build** to every project you want to flash over the air 
-->
## Steps to use
1. Run app.py using this command  ``` python app.py ```
the following is displayed
![image](https://user-images.githubusercontent.com/61471002/143068207-79dc2266-4c61-43f1-b7a0-882c31dd4fd8.png)
2. Copy the link to user browser
3. Click on "Choose File" button and choose hex file
4. click "Submit"
5. Reset MCU
