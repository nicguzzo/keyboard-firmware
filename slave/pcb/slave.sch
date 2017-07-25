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
L ATTINY2313A-PU U1
U 1 1 59779872
P 5100 4100
F 0 "U1" H 3950 5100 50  0000 C CNN
F 1 "ATTINY2313A-PU" H 6050 3200 50  0000 C CNN
F 2 "Housings_DIP:DIP-20_W7.62mm" H 5100 4100 50  0001 C CIN
F 3 "" H 5100 4100 50  0001 C CNN
	1    5100 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 J1
U 1 1 59779918
P 7300 3550
F 0 "J1" H 7300 3900 50  0000 C CNN
F 1 "CONN_01X06" V 7400 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x06_Pitch2.54mm" H 7300 3550 50  0001 C CNN
F 3 "" H 7300 3550 50  0001 C CNN
	1    7300 3550
	1    0    0    -1  
$EndComp
$Comp
L R_Small R3
U 1 1 59779981
P 8150 3700
F 0 "R3" H 8180 3720 50  0000 L CNN
F 1 "4.7k" H 8180 3660 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8150 3700 50  0001 C CNN
F 3 "" H 8150 3700 50  0001 C CNN
	1    8150 3700
	1    0    0    -1  
$EndComp
$Comp
L R_Small R4
U 1 1 59779A28
P 8500 3700
F 0 "R4" H 8530 3720 50  0000 L CNN
F 1 "4.7k" H 8530 3660 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8500 3700 50  0001 C CNN
F 3 "" H 8500 3700 50  0001 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
$Comp
L R_Small R1
U 1 1 59779A61
P 3600 3150
F 0 "R1" H 3630 3170 50  0000 L CNN
F 1 "10k" H 3630 3110 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3600 3150 50  0001 C CNN
F 3 "" H 3600 3150 50  0001 C CNN
	1    3600 3150
	1    0    0    -1  
$EndComp
$Comp
L R_Small R2
U 1 1 59779AC2
P 6700 5050
F 0 "R2" H 6730 5070 50  0000 L CNN
F 1 "1k" H 6730 5010 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 6700 5050 50  0001 C CNN
F 3 "" H 6700 5050 50  0001 C CNN
	1    6700 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J3
U 1 1 59779AF9
P 8950 4050
F 0 "J3" H 8950 4200 50  0000 C CNN
F 1 "CONN_01X02" V 9050 4050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 8950 4050 50  0001 C CNN
F 3 "" H 8950 4050 50  0001 C CNN
	1    8950 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 59779B70
P 5100 5300
F 0 "#PWR6" H 5100 5050 50  0001 C CNN
F 1 "GND" H 5100 5150 50  0000 C CNN
F 2 "" H 5100 5300 50  0001 C CNN
F 3 "" H 5100 5300 50  0001 C CNN
	1    5100 5300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR5
U 1 1 59779C54
P 5100 2800
F 0 "#PWR5" H 5100 2650 50  0001 C CNN
F 1 "+5V" H 5100 2940 50  0000 C CNN
F 2 "" H 5100 2800 50  0001 C CNN
F 3 "" H 5100 2800 50  0001 C CNN
	1    5100 2800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR8
U 1 1 59779C86
P 8350 3450
F 0 "#PWR8" H 8350 3300 50  0001 C CNN
F 1 "+5V" H 8350 3590 50  0000 C CNN
F 2 "" H 8350 3450 50  0001 C CNN
F 3 "" H 8350 3450 50  0001 C CNN
	1    8350 3450
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 59779CEB
P 6700 5450
F 0 "D1" H 6700 5550 50  0000 C CNN
F 1 "LED" H 6700 5350 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 6700 5450 50  0001 C CNN
F 3 "" H 6700 5450 50  0001 C CNN
	1    6700 5450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR7
U 1 1 59779DF7
P 6700 5700
F 0 "#PWR7" H 6700 5450 50  0001 C CNN
F 1 "GND" H 6700 5550 50  0000 C CNN
F 2 "" H 6700 5700 50  0001 C CNN
F 3 "" H 6700 5700 50  0001 C CNN
	1    6700 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5700 6700 5600
Wire Wire Line
	6700 5300 6700 5150
Wire Wire Line
	6700 4950 6700 4800
Wire Wire Line
	6700 4800 6450 4800
Wire Wire Line
	5100 5100 5100 5300
Wire Wire Line
	3750 3300 3600 3300
Wire Wire Line
	3600 3300 3600 3250
Wire Wire Line
	6450 3300 7100 3300
Wire Wire Line
	6450 3400 7100 3400
Wire Wire Line
	6450 3500 7100 3500
Wire Wire Line
	6450 3600 7100 3600
Wire Wire Line
	6450 3700 7100 3700
Wire Wire Line
	6450 3900 6950 3900
Wire Wire Line
	6950 3900 6950 3800
Wire Wire Line
	6950 3800 7100 3800
Wire Wire Line
	6450 3800 6800 3800
Wire Wire Line
	6800 3800 6800 4000
Wire Wire Line
	6800 4000 8750 4000
Wire Wire Line
	6450 4000 6600 4000
Wire Wire Line
	6600 4000 6600 4100
Wire Wire Line
	6600 4100 8750 4100
Wire Wire Line
	8500 3800 8500 4000
Connection ~ 8500 4000
Wire Wire Line
	8150 3800 8150 4100
Connection ~ 8150 4100
Wire Wire Line
	8150 3600 8150 3500
Wire Wire Line
	8150 3500 8500 3500
Wire Wire Line
	8500 3500 8500 3600
Wire Wire Line
	8350 3450 8350 3500
Connection ~ 8350 3500
$Comp
L CONN_01X06 J2
U 1 1 5977A334
P 7350 4450
F 0 "J2" H 7350 4800 50  0000 C CNN
F 1 "CONN_01X06" V 7450 4450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x06_Pitch2.54mm" H 7350 4450 50  0001 C CNN
F 3 "" H 7350 4450 50  0001 C CNN
	1    7350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4200 7150 4200
Wire Wire Line
	6450 4300 7150 4300
Wire Wire Line
	6450 4400 7150 4400
Wire Wire Line
	6450 4500 7150 4500
Wire Wire Line
	6450 4600 7150 4600
Wire Wire Line
	6450 4700 7150 4700
$Comp
L R_Small R5
U 1 1 5977A776
P 3200 3950
F 0 "R5" H 3230 3970 50  0000 L CNN
F 1 "1k" H 3230 3910 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3200 3950 50  0001 C CNN
F 3 "" H 3200 3950 50  0001 C CNN
	1    3200 3950
	1    0    0    -1  
$EndComp
$Comp
L R_Small R6
U 1 1 5977A80C
P 3500 3950
F 0 "R6" H 3530 3970 50  0000 L CNN
F 1 "1k" H 3530 3910 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3500 3950 50  0001 C CNN
F 3 "" H 3500 3950 50  0001 C CNN
	1    3500 3950
	1    0    0    -1  
$EndComp
Connection ~ 6700 5450
$Comp
L LED D3
U 1 1 5977A86F
P 3500 4300
F 0 "D3" H 3500 4400 50  0000 C CNN
F 1 "LED" H 3500 4200 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 3500 4300 50  0001 C CNN
F 3 "" H 3500 4300 50  0001 C CNN
	1    3500 4300
	0    -1   -1   0   
$EndComp
$Comp
L LED D2
U 1 1 5977A8C7
P 3200 4300
F 0 "D2" H 3200 4400 50  0000 C CNN
F 1 "LED" H 3200 4200 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 3200 4300 50  0001 C CNN
F 3 "" H 3200 4300 50  0001 C CNN
	1    3200 4300
	0    -1   -1   0   
$EndComp
Connection ~ 6700 5800
$Comp
L GND #PWR3
U 1 1 5977A908
P 3350 4600
F 0 "#PWR3" H 3350 4350 50  0001 C CNN
F 1 "GND" H 3350 4450 50  0000 C CNN
F 2 "" H 3350 4600 50  0001 C CNN
F 3 "" H 3350 4600 50  0001 C CNN
	1    3350 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3800 3500 3800
Wire Wire Line
	3500 3800 3500 3850
Wire Wire Line
	3750 3600 3200 3600
Wire Wire Line
	3200 3600 3200 3850
Wire Wire Line
	3200 4050 3200 4150
Wire Wire Line
	3500 4050 3500 4150
Wire Wire Line
	3500 4550 3500 4450
Wire Wire Line
	3200 4550 3500 4550
Wire Wire Line
	3200 4550 3200 4450
Wire Wire Line
	3350 4600 3350 4550
Connection ~ 3350 4550
$Comp
L C_Small C1
U 1 1 5977AB96
P 2150 3000
F 0 "C1" H 2160 3070 50  0000 L CNN
F 1 "C_Small" H 2160 2920 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.4mm_W2.1mm_P2.50mm" H 2150 3000 50  0001 C CNN
F 3 "" H 2150 3000 50  0001 C CNN
	1    2150 3000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 5977ACAB
P 2150 2750
F 0 "#PWR1" H 2150 2600 50  0001 C CNN
F 1 "+5V" H 2150 2890 50  0000 C CNN
F 2 "" H 2150 2750 50  0001 C CNN
F 3 "" H 2150 2750 50  0001 C CNN
	1    2150 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5977ACE0
P 2150 3250
F 0 "#PWR2" H 2150 3000 50  0001 C CNN
F 1 "GND" H 2150 3100 50  0000 C CNN
F 2 "" H 2150 3250 50  0001 C CNN
F 3 "" H 2150 3250 50  0001 C CNN
	1    2150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2750 2150 2900
Wire Wire Line
	2150 3100 2150 3250
$Comp
L +5V #PWR4
U 1 1 5977B114
P 3600 2850
F 0 "#PWR4" H 3600 2700 50  0001 C CNN
F 1 "+5V" H 3600 2990 50  0000 C CNN
F 2 "" H 3600 2850 50  0001 C CNN
F 3 "" H 3600 2850 50  0001 C CNN
	1    3600 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2850 3600 3050
Wire Wire Line
	5100 3000 5100 2800
$Comp
L CONN_01X02 J4
U 1 1 5977B868
P 2700 3000
F 0 "J4" H 2700 3150 50  0000 C CNN
F 1 "CONN_01X02" V 2800 3000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2700 3000 50  0001 C CNN
F 3 "" H 2700 3000 50  0001 C CNN
	1    2700 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2950 2500 2850
Wire Wire Line
	2500 2850 2150 2850
Connection ~ 2150 2850
Wire Wire Line
	2500 3050 2500 3150
Wire Wire Line
	2500 3150 2150 3150
Connection ~ 2150 3150
$EndSCHEMATC