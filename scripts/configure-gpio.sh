#!/bin/bash

#Set up for A62 found here: https://wikitech.seco.com/index.php/A62_Pinout_Configuration_options
#Set up variables for configuring pins 1, 2, 3 on A62
#Pin A is 2, Pin B is 1, the Switch is set up on pin 3

#to set the environment variables PIN_A_PATH, PIN_B_PATH, PIN_SWITCH_PATH source this script instead of just running it. 
b_b=2
b_nn=25
a_b=1
a_nn=9
switch_b=2
switch_nn=23
gpio_path=/sys/class/gpio
dir_out=out
dir_in=in
edge_both=both

#Export the GPIO pin, change the direction to "in", and change edge to "both"
configure_pin() {
	#calculate the number of the pin on the A62 board
	pin_num=$((($1-1)*32+$2))
	pin_addr=gpio$pin_num

	#check to see if the pin is already exported
	if [ ! -d "$gpio_path/$pin_addr" ]; then
		#export the pin so that we can read its value
		echo "$pin_num" > $gpio_path/export
	fi

	#if the pin was successfully exported, then change the pin direction to in
	if [ -d "$gpio_path/$pin_addr" ]; then
		echo "Exported pin GPIO$1_IO$2"
		if [[ $(< $gpio_path/$pin_addr/direction ) != $dir_in ]]; then
			echo "$dir_in" > $gpio_path/$pin_addr/direction
			echo "Changed pin direction to \"in\""
		fi
		#set edge to both to only be notified when value changes  helpful documentation: https://embeddeduse.com/2018/09/18/monitoring-sys-files-qfilesystemwatcher/
		echo "$edge_both" > $gpio_path/$pin_addr/edge
	else
		echo "Unable to export pin GPIO$1_IO$2"
	fi
}

#Set environment variable to the gpio value path if the gpio directory exists
set_env_vars(){
	pin_num="$((($2-1)*32+$3))"
	pin_addr="gpio$pin_num"
	if [ -d $gpio_path/$pin_addr ] && [ ${BASH_SOURCE[0]} != ${0} ]; then
		export $1=$gpio_path/gpio$((($2-1)*32+$3))/value
		echo "Exported environment variable $1=$gpio_path/gpio$((($2-1)*32+$3))/value"
	fi
}

configure_pin $a_b $a_nn
configure_pin $b_b $b_nn
configure_pin $switch_b $switch_nn

set_env_vars PIN_A_PATH $a_b $a_nn
set_env_vars PIN_B_PATH $b_b $b_nn
set_env_vars PIN_SWITCH_PATH $switch_b $switch_nn
