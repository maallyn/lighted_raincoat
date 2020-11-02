EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:Conn_01x01_Female J1
U 1 1 5F8E7CBC
P 3900 2050
F 0 "J1" V 3838 1962 50  0000 R CNN
F 1 "data-input" V 3747 1962 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 3701 1962 50  0001 R CNN
F 3 "~" H 3900 2050 50  0001 C CNN
F 4 "J" H 3900 2050 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 3900 2050 50  0001 C CNN "Spice_Model"
F 6 "N" H 3900 2050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    3900 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3900 2250 3900 2750
Wire Wire Line
	3900 2750 4750 2750
$Comp
L Device:Q_NMOS_SGD Q1
U 1 1 5F8E81D0
P 6100 2750
F 0 "Q1" H 6305 2841 50  0000 L CNN
F 1 "2n7000" H 6305 2750 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline" H 6305 2659 50  0000 L CNN
F 3 "~" H 6100 2750 50  0001 C CNN
F 4 "X" H 6100 2750 50  0001 C CNN "Spice_Primitive"
F 5 "2n7000" H 6100 2750 50  0001 C CNN "Spice_Model"
F 6 "Y" H 6100 2750 50  0001 C CNN "Spice_Netlist_Enabled"
F 7 "/home/maallyn/kicad-libs/2N7000.REV0.LIB" H 6100 2750 50  0001 C CNN "Spice_Lib_File"
	1    6100 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5F8EBEE9
P 6200 2950
F 0 "#PWR03" H 6200 2700 50  0001 C CNN
F 1 "GND" H 6205 2777 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 6200 2950 50  0001 C CNN
F 3 "" H 6200 2950 50  0001 C CNN
	1    6200 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F8EC374
P 6200 1550
F 0 "R2" H 6130 1504 50  0000 R CNN
F 1 "1000" H 6130 1595 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6130 1550 50  0001 C CNN
F 3 "~" H 6200 1550 50  0001 C CNN
	1    6200 1550
	-1   0    0    1   
$EndComp
Wire Wire Line
	6200 1700 6200 2100
$Comp
L Connector:Conn_01x01_Female J3
U 1 1 5F8ECB08
P 6700 2100
F 0 "J3" H 6728 2126 50  0000 L CNN
F 1 "data-output" H 6728 2035 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 6501 2012 50  0001 R CNN
F 3 "~" H 6700 2100 50  0001 C CNN
F 4 "J" H 6700 2100 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 6700 2100 50  0001 C CNN "Spice_Model"
F 6 "N" H 6700 2100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    6700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 2100 6450 2100
Connection ~ 6200 2100
Wire Wire Line
	6200 2100 6200 2550
$Comp
L power:+5V #PWR02
U 1 1 5F8F07B4
P 6200 850
F 0 "#PWR02" H 6200 700 50  0001 C CNN
F 1 "+5V" H 6215 1023 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 6200 850 50  0001 C CNN
F 3 "" H 6200 850 50  0001 C CNN
	1    6200 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 850  6200 1400
$Comp
L Device:R R3
U 1 1 5F8FB2D2
P 3900 5800
F 0 "R3" V 3693 5800 50  0000 C CNN
F 1 "1000" V 3784 5800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3830 5800 50  0001 C CNN
F 3 "~" H 3900 5800 50  0001 C CNN
	1    3900 5800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J4
U 1 1 5F8FB2E0
P 2900 5100
F 0 "J4" V 2838 5012 50  0000 R CNN
F 1 "clock-input" V 2747 5012 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 2701 5012 50  0001 R CNN
F 3 "~" H 2900 5100 50  0001 C CNN
F 4 "J" H 2900 5100 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 2900 5100 50  0001 C CNN "Spice_Model"
F 6 "N" H 2900 5100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2900 5100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 5300 2900 5800
Wire Wire Line
	2900 5800 3750 5800
$Comp
L Device:Q_NMOS_SGD Q2
U 1 1 5F8FB2F1
P 5100 5800
F 0 "Q2" H 5305 5891 50  0000 L CNN
F 1 "2n7000" H 5305 5800 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline" H 5305 5709 50  0000 L CNN
F 3 "~" H 5100 5800 50  0001 C CNN
F 4 "X" H 5100 5800 50  0001 C CNN "Spice_Primitive"
F 5 "2n7000" H 5100 5800 50  0001 C CNN "Spice_Model"
F 6 "Y" H 5100 5800 50  0001 C CNN "Spice_Netlist_Enabled"
F 7 "/home/maallyn/kicad-libs/2N7000.REV0.LIB" H 5100 5800 50  0001 C CNN "Spice_Lib_File"
	1    5100 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5F8FB316
P 5200 6000
F 0 "#PWR08" H 5200 5750 50  0001 C CNN
F 1 "GND" H 5205 5827 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 5200 6000 50  0001 C CNN
F 3 "" H 5200 6000 50  0001 C CNN
	1    5200 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F8FB320
P 5200 4600
F 0 "R4" H 5130 4554 50  0000 R CNN
F 1 "1000" H 5130 4645 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5130 4600 50  0001 C CNN
F 3 "~" H 5200 4600 50  0001 C CNN
	1    5200 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 4750 5200 5150
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5F8FB32E
P 5700 5150
F 0 "J6" H 5728 5176 50  0000 L CNN
F 1 "clock-output" H 5728 5085 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 5501 5062 50  0001 R CNN
F 3 "~" H 5700 5150 50  0001 C CNN
F 4 "J" H 5700 5150 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 5700 5150 50  0001 C CNN "Spice_Model"
F 6 "N" H 5700 5150 50  0001 C CNN "Spice_Netlist_Enabled"
	1    5700 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5150 5200 5150
Connection ~ 5200 5150
Wire Wire Line
	5200 5150 5200 5600
$Comp
L power:+5V #PWR07
U 1 1 5F8FB348
P 5200 3900
F 0 "#PWR07" H 5200 3750 50  0001 C CNN
F 1 "+5V" H 5215 4073 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 5200 3900 50  0001 C CNN
F 3 "" H 5200 3900 50  0001 C CNN
	1    5200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3900 5200 4450
$Comp
L Device:R R1
U 1 1 5F902E4D
P 4900 2750
F 0 "R1" H 4830 2704 50  0000 R CNN
F 1 "1000" H 4830 2795 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4830 2750 50  0001 C CNN
F 3 "~" H 4900 2750 50  0001 C CNN
	1    4900 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 2750 5900 2750
Wire Wire Line
	4050 5800 4900 5800
$Comp
L Connector:Conn_01x01_Female J5
U 1 1 5FA05738
P 7050 1650
F 0 "J5" H 7078 1676 50  0000 L CNN
F 1 "data-output" H 7078 1585 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 6851 1562 50  0001 R CNN
F 3 "~" H 7050 1650 50  0001 C CNN
F 4 "J" H 7050 1650 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 7050 1650 50  0001 C CNN "Spice_Model"
F 6 "N" H 7050 1650 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7050 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 5FA0685D
P 6150 4500
F 0 "J2" H 6178 4526 50  0000 L CNN
F 1 "clock-output" H 6178 4435 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 5951 4412 50  0001 R CNN
F 3 "~" H 6150 4500 50  0001 C CNN
F 4 "J" H 6150 4500 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 6150 4500 50  0001 C CNN "Spice_Model"
F 6 "N" H 6150 4500 50  0001 C CNN "Spice_Netlist_Enabled"
	1    6150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 1650 6450 1650
Wire Wire Line
	6450 1650 6450 2100
Connection ~ 6450 2100
Wire Wire Line
	6450 2100 6200 2100
Wire Wire Line
	5950 4500 5500 4500
Wire Wire Line
	5500 4500 5500 5150
Connection ~ 5500 5150
$Comp
L power:GND #PWR01
U 1 1 5FA09B27
P 8650 2050
F 0 "#PWR01" H 8650 1800 50  0001 C CNN
F 1 "GND" H 8655 1877 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 8650 2050 50  0001 C CNN
F 3 "" H 8650 2050 50  0001 C CNN
	1    8650 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FA09F61
P 8650 2800
F 0 "#PWR04" H 8650 2550 50  0001 C CNN
F 1 "GND" H 8655 2627 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 8650 2800 50  0001 C CNN
F 3 "" H 8650 2800 50  0001 C CNN
	1    8650 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5FA0A3D4
P 8650 3500
F 0 "#PWR05" H 8650 3250 50  0001 C CNN
F 1 "GND" H 8655 3327 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 8650 3500 50  0001 C CNN
F 3 "" H 8650 3500 50  0001 C CNN
	1    8650 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5FA0A627
P 8650 4050
F 0 "#PWR06" H 8650 3800 50  0001 C CNN
F 1 "GND" H 8655 3877 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 8650 4050 50  0001 C CNN
F 3 "" H 8650 4050 50  0001 C CNN
	1    8650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5FA0A8DA
P 8650 4800
F 0 "#PWR09" H 8650 4550 50  0001 C CNN
F 1 "GND" H 8655 4627 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 8650 4800 50  0001 C CNN
F 3 "" H 8650 4800 50  0001 C CNN
	1    8650 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J7
U 1 1 5FA0B00F
P 8650 1850
F 0 "J7" V 8588 1762 50  0000 R CNN
F 1 "gnd" V 8497 1762 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 8451 1762 50  0001 R CNN
F 3 "~" H 8650 1850 50  0001 C CNN
F 4 "J" H 8650 1850 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 8650 1850 50  0001 C CNN "Spice_Model"
F 6 "N" H 8650 1850 50  0001 C CNN "Spice_Netlist_Enabled"
	1    8650 1850
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J8
U 1 1 5FA0BC02
P 8650 2600
F 0 "J8" V 8588 2512 50  0000 R CNN
F 1 "gnd" V 8497 2512 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 8451 2512 50  0001 R CNN
F 3 "~" H 8650 2600 50  0001 C CNN
F 4 "J" H 8650 2600 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 8650 2600 50  0001 C CNN "Spice_Model"
F 6 "N" H 8650 2600 50  0001 C CNN "Spice_Netlist_Enabled"
	1    8650 2600
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 5FA0EA7D
P 8650 3300
F 0 "J9" V 8588 3212 50  0000 R CNN
F 1 "gnd" V 8497 3212 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 8451 3212 50  0001 R CNN
F 3 "~" H 8650 3300 50  0001 C CNN
F 4 "J" H 8650 3300 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 8650 3300 50  0001 C CNN "Spice_Model"
F 6 "N" H 8650 3300 50  0001 C CNN "Spice_Netlist_Enabled"
	1    8650 3300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 5FA0EF1E
P 8650 3850
F 0 "J10" V 8588 3762 50  0000 R CNN
F 1 "gnd" V 8497 3762 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 8451 3762 50  0001 R CNN
F 3 "~" H 8650 3850 50  0001 C CNN
F 4 "J" H 8650 3850 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 8650 3850 50  0001 C CNN "Spice_Model"
F 6 "N" H 8650 3850 50  0001 C CNN "Spice_Netlist_Enabled"
	1    8650 3850
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J11
U 1 1 5FA0F3F3
P 8650 4600
F 0 "J11" V 8588 4512 50  0000 R CNN
F 1 "gnd" V 8497 4512 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 8451 4512 50  0001 R CNN
F 3 "~" H 8650 4600 50  0001 C CNN
F 4 "J" H 8650 4600 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 8650 4600 50  0001 C CNN "Spice_Model"
F 6 "N" H 8650 4600 50  0001 C CNN "Spice_Netlist_Enabled"
	1    8650 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 5FA0F8D9
P 9900 1950
F 0 "#PWR010" H 9900 1800 50  0001 C CNN
F 1 "+5V" H 9915 2123 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 9900 1950 50  0001 C CNN
F 3 "" H 9900 1950 50  0001 C CNN
	1    9900 1950
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5FA0FDB9
P 9900 2900
F 0 "#PWR011" H 9900 2750 50  0001 C CNN
F 1 "+5V" H 9915 3073 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 9900 2900 50  0001 C CNN
F 3 "" H 9900 2900 50  0001 C CNN
	1    9900 2900
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 5FA1024F
P 9900 3650
F 0 "#PWR012" H 9900 3500 50  0001 C CNN
F 1 "+5V" H 9915 3823 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 9900 3650 50  0001 C CNN
F 3 "" H 9900 3650 50  0001 C CNN
	1    9900 3650
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5FA1063F
P 9900 4400
F 0 "#PWR013" H 9900 4250 50  0001 C CNN
F 1 "+5V" H 9915 4573 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" H 9900 4400 50  0001 C CNN
F 3 "" H 9900 4400 50  0001 C CNN
	1    9900 4400
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J12
U 1 1 5FA10D25
P 9900 1750
F 0 "J12" V 9838 1662 50  0000 R CNN
F 1 "5v" V 9747 1662 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 9701 1662 50  0001 R CNN
F 3 "~" H 9900 1750 50  0001 C CNN
F 4 "J" H 9900 1750 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 9900 1750 50  0001 C CNN "Spice_Model"
F 6 "N" H 9900 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9900 1750
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J13
U 1 1 5FA171C8
P 9900 2700
F 0 "J13" V 9838 2612 50  0000 R CNN
F 1 "5v" V 9747 2612 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 9701 2612 50  0001 R CNN
F 3 "~" H 9900 2700 50  0001 C CNN
F 4 "J" H 9900 2700 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 9900 2700 50  0001 C CNN "Spice_Model"
F 6 "N" H 9900 2700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9900 2700
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J14
U 1 1 5FA178F5
P 9900 3450
F 0 "J14" V 9838 3362 50  0000 R CNN
F 1 "5v" V 9747 3362 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 9701 3362 50  0001 R CNN
F 3 "~" H 9900 3450 50  0001 C CNN
F 4 "J" H 9900 3450 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 9900 3450 50  0001 C CNN "Spice_Model"
F 6 "N" H 9900 3450 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9900 3450
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J15
U 1 1 5FA17D76
P 9900 4200
F 0 "J15" V 9838 4112 50  0000 R CNN
F 1 "5v" V 9747 4112 50  0000 R CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm" V 9701 4112 50  0001 R CNN
F 3 "~" H 9900 4200 50  0001 C CNN
F 4 "J" H 9900 4200 50  0001 C CNN "Spice_Primitive"
F 5 "input" H 9900 4200 50  0001 C CNN "Spice_Model"
F 6 "N" H 9900 4200 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9900 4200
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
