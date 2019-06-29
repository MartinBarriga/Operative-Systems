#! /usr/bin/python

import subprocess
import os

cadenaInterfaz = subprocess.getoutput('ifconfig')
j = 0

for indice in cadenaInterfaz :
	if(indice == ' '):
		interfaz = cadenaInterfaz[0:j]
		break
	j = j + 1

print("Interfaz: " + interfaz)


tipoInterfaz = 	os.system("cat /etc/network/interfaces | grep " + interfaz ) 

if(tipoInterfaz == 0) :
	print("La interfaz es estatica")
else:
	print("La interfaz es DHCP")


Ip = subprocess.getoutput("ifconfig | grep inet |grep -Eo '[0-9]{1,4}'.'[0-9]{1,4}'.'[0-9]{1,4}'.'[0-9]{1,4}' | head -1" )

print("Ip: " + Ip)

IpMocha = ""
contador = 0
for indice in Ip:
	IpMocha = IpMocha + indice	
	if(indice == '.'):
		contador = contador + 1
		if(contador == 3):
			break
		 
Hosts = []
for numero in range(255):
	IpGenerada = IpMocha + str(numero)
	print("Ip Generada: " + IpGenerada)
	if(IpGenerada != Ip):
		ping = os.system("ping -c 1 " + IpGenerada)
		if(ping == 0): 
			Hosts.append(IpGenerada)

print(Hosts)


