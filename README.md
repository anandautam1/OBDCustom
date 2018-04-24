# OBDCustom
Lab 3 – CAN BUS Communication and Control
A set of stm32f107 library which transmit data over can bus to another board.

Aim:
The aim of this laboratory is to developed a firmware on a microprocessor to emulate the lower levels communication bus typically found in a modern motor vehicle. To understand the method in which CAN bus transfer information to nodes on the network. To gain further insight on the complex nature of CAN bus transmission and the how the parameters with a given specification relate back on the physical data transmission. To decode complex communication network packets exhibited by the protocol and to use modern electronic test equipment to accomplish the task. 

Objectives:
In this laboratory a firmware for STM32F107 will be developed to simulate Controller Area Network usually employed in a modern vehicle. In early 1990 bosh developed the protocol for a typical means of communication where various device can share information. This typically results in a reduction of the overall cost and the complexity of various systems. By sharing an information to every device on enable for nodes to act upon the data simultaneously when it is necessary. 

Based on the figure it can be seen that there are two nodes within the structure. The node 1 which will be built from this exercise responsible for transmitting three messages from the potentiometer value with a data length of 4 bytes converted by the ADC (analogue to digital converter) on an address 0xBADCAFE; the led8 state with a data length of 1 on an address of 0x01A4F2B; the led 9 state with a data length of 1 on an address of 0x0024FCE.  

The responsibility of CAN node 2 on the other hand is to communicate on the same interface where led 15 on node 2 will be enabled if the node 1 user switch has been pressed where a payload of 0x01 of 1 byte is received on address 0x01AEFCA; led 14 on node 2 will be enabled if the node 1 wakeup switch has been pressed where a payload of 0x01 of 1 byte received on address 0x002BEF; 
