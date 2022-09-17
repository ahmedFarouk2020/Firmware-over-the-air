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

>> Note: The Hex file used with this FOTA has a special format :)

## How to create the Hex file
1. Create empty .hex file 
2. Modify the **ldscripts/mem.ld** file in the project you want to upload to MCU as follows
```
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
  CCMRAM (xrw) : ORIGIN = 0x00000000, LENGTH = 0
  FLASH (rx) : ORIGIN = 0x08002800, LENGTH = 27k
  FLASHB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB0 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB2 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB3 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  MEMORY_ARRAY (xrw)  : ORIGIN = 0x00000000, LENGTH = 0
}
```
3. Compile
4. Copy all the content of the generated hex file from step 3 and paste it in the empty file
5. Add '*' in a new line just after the present data
6. repeat the steps from 2 to 4 but with this new values 
```
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
  CCMRAM (xrw) : ORIGIN = 0x00000000, LENGTH = 0
  FLASH (rx) : ORIGIN = 0x08009400, LENGTH = 27k
  FLASHB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB0 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB2 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB3 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  MEMORY_ARRAY (xrw)  : ORIGIN = 0x00000000, LENGTH = 0
}
```
7. Your file is ready to be uploaded **I will add a sample file too**
