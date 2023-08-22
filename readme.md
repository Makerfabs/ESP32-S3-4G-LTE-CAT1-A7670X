# ESP32-S3-Parallel-TFT-with-Touch-1.9inch

```
/* 
    Version:      V1.0
    Author:       Vincent
    Create Date:  2023/8/22
*/
```

# Makerfabs

[Makerfabs home page](https://www.makerfabs.com/)

[Makerfabs Wiki](https://wiki.makerfabs.com/)

## Intruduce

Product Link:[]()

Wiki Link : []()


## Features

- Controller: ESP32-S3
- Wireless: WiFi& Bluetooth 5.0
- Arduino support
- MicroPython support: Yes
- Operation temperature: -40℃ to +85℃
- USB: USB Native, Type-C
- Power Supply: USB Type-C 5.0V(4.0V~5.25V); 3.7V Lipo battery



# Usage

All supporting information, such as the AT instructions and other official documents are in the A76XX Manual.zip.

## Complier Option

- Use type-c use cable connect USB-TTL to PC.
- Select "ESP32-S3 DEV Module"
- Select PSRAM "OPI PSRAM"

## Example

at_command_demo.ino

Serial port transparent transmission demo.
Can be used to test AT Commands.

## AT Commands

### AT+CSQ

Query signal quality

```
AT+CSQ
+CSQ: 28,99

OK

```

### AT+SIMCOMATI

Example Query module information


```
AT+SIMCOMATI
Manufacturer: INCORPORATED
Model: A7670SA-FASE
Revision: A011B04A7670M7_F
A7670M7_B04V02_220927
QCN:
IMEI: 869731059057646
MEID:
+GCAP: +CGSM,+FCLASS,+DS
DeviceInfo:

OK

```

### AT+COPS

Operator selection

```
AT+COPS?
+COPS: 0,2,"46000",7

OK

```

### AT+CICCID

Read ICCID from SIM card

```
AT+CICCID
+ICCID: 898607E0102250030751

OK

```

### AT+CBC

Read the voltage value of the power supply

```
AT+CBC
+CBC: 4.167V

OK

```

## TTS Test

```
AT+CTTSPARAM=? 
AT+CTTSPARAM=1,3,0,1,1 
AT+CTTSPARAM?
AT+CTTS=1,"6B228FCE4F7F75288BED97F3540862107CFB7EDF" 
AT+CTTS=2,"Hi, Makerfabs"

```

## LBS Test

```
AT+CLBS=? 
AT+SIMCOMATI
AT+SIMEI=xxxxx 
AT+CLBS=2 
AT+CLBS=1
```

## Make a call

```
ATD<phone_number>;
AT+COUTGAIN=?
AT+COUTGAIN=5
AT+CHUP 
```
## TCP test

```
AT+CIPMODE=1
AT+NETOPEN
AT+CIPOPEN=0,"TCP","122.114.122.174",39348
Hi,Makerfabs
AT+CIPCLOSE=0
AT+NETCLOSE
```
## LBS Test

```
AT+CLBS=? 
AT+SIMCOMATI
AT+SIMEI=xxxxx 
AT+CLBS=2 
AT+CLBS=1
```
## HTTP Test

```
AT+HTTPINIT
AT+HTTPPARA="URL","http:www.makerfabs.com"
AT+HTTPACTION=0
AT+HTTPHEAD
AT+HTTPREAD=0,500
AT+HTTPTERM
```

## MQTT Test

```
AT+CMQTTSTART
AT+CMQTTACCQ=0,"client test0"
AT+CMQTTWILLTOPIC=0,10
AT+CMQTTWILLMSG=0,6,1
AT+CMQTTCONNECT=0,"tcp://test.mosquitto.org:1883",60,1
AT+CMQTTSUB=0,9,1
AT+CMQTTTOPIC=0,9
AT+CMQTTPAYLOAD=0,60
```