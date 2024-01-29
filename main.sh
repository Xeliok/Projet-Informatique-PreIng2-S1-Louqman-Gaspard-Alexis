#! /bin/bash

#--------------------------------------------------check temp and images files-------------------------------------------------------#

dossier_temp="temp"
dossier_images="images"

if [ ! -d "$dossier_temp" ]; then #condition to check if temp file exist
	mkdir -p "$dossier_temp" #create temp file if it doesn't exist 	
elif [ "$(ls -A $dossier_temp)" ]; then #condition to check if temp file is empty
	rm -r "$dossier_temp"/* #delete data from temp file
fi

if [ ! -d "$dossier_images" ]; then #condition to check if images file exist
	mkdir -p "$dossier_images" #create images file if it doesn't exist
fi

#---------------------------------------------------------check string---------------------------------------------------------------#

if [ ! -f $1 ]; then
	echo 'ERROR, 1st string is not a valid file path'
	exit
fi

shift #skip the 1st string

for string in "$@"; do
	if [[ $string != '-h' && $string != '-d1' && $string != '-d2' && $string != '-l' && $string != '-t' && $string != '-s' ]]; then #condition to check if string is valid 
	echo 'ERROR, option does no exist'
	exit
fi
done 


######################################################################################################################################
#--------------------------------------------------------------HELP------------------------------------------------------------------#
######################################################################################################################################


for string in "$@"; do

	if [ $string = '-h' ]; then #condition to check if -h is used
	        echo "-d1: drivers with the most trips"
	        echo "-d2: drivers with the greatest distance"
	        echo "-l: the 10 longuest routes"
	        echo "-t: the 10 most traveled cities"
	        echo "-s: routes with the highest maximum distance - the minimum distance, with their average"
	        exit

	fi
done


######################################################################################################################################
#--------------------------------------------------------------HELP------------------------------------------------------------------#
######################################################################################################################################

#for string in "$@"; do

#	if [[ $string = '-s' ]]; then
#	elif [[  $string = '-d1' ]]; then
#	elif [[  $string = '-d2' ]]; then
#	elif [[  $string = '-l' ]]; then
#	elif [[  $string = '-t' ]]; then
#	exit
#	fi
#done

