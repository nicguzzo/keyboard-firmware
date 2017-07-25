EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X06 J5
U 1 1 5977C5C6
P 4400 2950
F 0 "J5" H 4400 3300 50  0000 C CNN
F 1 "CONN_01X06" V 4500 2950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 4400 2950 50  0001 C CNN
F 3 "" H 4400 2950 50  0001 C CNN
	1    4400 2950
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X06 J4
U 1 1 5977C664
P 3750 3100
F 0 "J4" H 3750 3450 50  0000 C CNN
F 1 "CONN_01X06" V 3850 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 3750 3100 50  0001 C CNN
F 3 "" H 3750 3100 50  0001 C CNN
	1    3750 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04_FEMALE J7
U 1 1 5977C6A3
P 5350 2400
F 0 "J7" H 5350 2800 50  0000 C CNN
F 1 "CONN_01X04_FEMALE" H 5450 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 5350 2700 50  0001 C CNN
F 3 "" H 5350 2700 50  0001 C CNN
	1    5350 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04_FEMALE J8
U 1 1 5977C6EA
P 5350 3250
F 0 "J8" H 5350 3650 50  0000 C CNN
F 1 "CONN_01X04_FEMALE" H 5450 2850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 5350 3550 50  0001 C CNN
F 3 "" H 5350 3550 50  0001 C CNN
	1    5350 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04_FEMALE J2
U 1 1 5977C71F
P 2750 2400
F 0 "J2" H 2750 2800 50  0000 C CNN
F 1 "CONN_01X04_FEMALE" H 2850 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2750 2700 50  0001 C CNN
F 3 "" H 2750 2700 50  0001 C CNN
	1    2750 2400
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X04_FEMALE J3
U 1 1 5977C798
P 2750 3250
F 0 "J3" H 2750 3650 50  0000 C CNN
F 1 "CONN_01X04_FEMALE" H 2850 2850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2750 3550 50  0001 C CNN
F 3 "" H 2750 3550 50  0001 C CNN
	1    2750 3250
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X04 J6
U 1 1 5977C7ED
P 5100 1700
F 0 "J6" H 5100 1950 50  0000 C CNN
F 1 "CONN_01X04" V 5200 1700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 5100 1700 50  0001 C CNN
F 3 "" H 5100 1700 50  0001 C CNN
	1    5100 1700
	1    0    0    -1  
$EndComp
Text GLabel 2850 2300 2    60   Input ~ 0
SDA
Text GLabel 2850 2100 2    60   Input ~ 0
SCL
Text GLabel 4900 1650 0    60   Input ~ 0
SDA
Text GLabel 4900 1750 0    60   Input ~ 0
SCL
Text GLabel 4900 1850 0    60   Input ~ 0
GND
Text GLabel 4900 1550 0    60   Input ~ 0
5V
Text GLabel 5250 2100 0    60   Input ~ 0
GND
Text GLabel 5250 2300 0    60   Input ~ 0
5V
Wire Wire Line
	4600 2700 4600 2500
Wire Wire Line
	4600 2500 5250 2500
Wire Wire Line
	4600 2800 4950 2800
Wire Wire Line
	4950 2800 4950 2700
Wire Wire Line
	4950 2700 5250 2700
Wire Wire Line
	4600 2900 5150 2900
Wire Wire Line
	5150 2900 5150 2950
Wire Wire Line
	5150 2950 5250 2950
Wire Wire Line
	4600 3000 5150 3000
Wire Wire Line
	5150 3000 5150 3150
Wire Wire Line
	5150 3150 5250 3150
Wire Wire Line
	4600 3100 5050 3100
Wire Wire Line
	5050 3100 5050 3350
Wire Wire Line
	5050 3350 5250 3350
Wire Wire Line
	4600 3200 4950 3200
Wire Wire Line
	4950 3200 4950 3550
Wire Wire Line
	4950 3550 5250 3550
Wire Wire Line
	2850 2500 3300 2500
Wire Wire Line
	3300 2500 3300 2850
Wire Wire Line
	3300 2850 3550 2850
Wire Wire Line
	3550 2950 3250 2950
Wire Wire Line
	3250 2950 3250 2700
Wire Wire Line
	3250 2700 2850 2700
Wire Wire Line
	2850 2950 3200 2950
Wire Wire Line
	3200 2950 3200 3050
Wire Wire Line
	3200 3050 3550 3050
Wire Wire Line
	3550 3150 2850 3150
Wire Wire Line
	3550 3250 2950 3250
Wire Wire Line
	2950 3250 2950 3350
Wire Wire Line
	2950 3350 2850 3350
Wire Wire Line
	3550 3350 3200 3350
Wire Wire Line
	3200 3350 3200 3550
Wire Wire Line
	3200 3550 2850 3550
$Comp
L CONN_01X01_FEMALE J1
U 1 1 5977CC17
P 2750 1950
F 0 "J1" H 2750 2050 50  0000 C CNN
F 1 "CONN_01X01_FEMALE" H 2750 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 2750 1950 50  0001 C CNN
F 3 "" H 2750 1950 50  0001 C CNN
	1    2750 1950
	-1   0    0    1   
$EndComp
Text GLabel 2850 1950 2    60   Input ~ 0
GND
$EndSCHEMATC
