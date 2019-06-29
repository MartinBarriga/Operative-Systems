#! /usr/bin/python

import subprocess
import os
import pexpect




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

contraUsuario = "root"
nombreUsuario = "martin"
rutaMysql = "/Applications/xampp/xamppfiles/bin/mysql -u root -p"
contraMysql = ""
DireccionMac = "/users/martin/documents"
DireccionLinux = "/home/martin/Escritorio/Sistemas_Operativos/"
NombreArchivo = "Ejercicio1Mac.py"
#rutaMysqlLinux = "mysql -u root -p"
#contraMysqlLinux = "root"
#nombreUsuarioLinux = ""
#contraUsuarioLinux = ""
subprocess.call(['mkdir', '/home/martin/Documentos/ArchivosDe' + ipHost])
for ipHost in Hosts:
	p = pexpect.spawn('ssh '+ nombreUsuario +'@' + ipHost)
	respuestaP = p.expect(['Are you sure you want to continue connecting', 'Password:',pexpect.EOF])
	if(respuestaP == 0):
		p.sendline('yes')
		respuestaP = p.expect(['Are you sure you want to continue connecting', 'Password:',pexpect.EOF])
	if(respuestaP == 1):
		p.sendline(contraUsuario)
		p.sendline(rutaMysql)
		respuestaM = p.expect(['Enter password: ',pexpect.EOF])

		if(respuestaM == 0):
			p.sendline(contraMysql)
			p.sendline('create database SistemasOperativos;')
			p.sendline("grant all privileges on SistemasOperativos.* to'"+nombreUsuario+"'@'localhost'"+ 'identified by "'+contraUsuario+'";')
			p.sendline('flush privileges;')
			p.sendline('exit')
		else:
			print("ERROR: No se encontro el path de mysql")
		p.sendline('exit')	
	elif(i==2):
		print("ERROR: SSH No se pudo conectar con el host") 
	#p.interact()	
	os.system("sshpass -p '" + contraUsuario + "' scp -o StrictHostKeyChecking=no " + DireccionLinux + NombreArchivo + " " + nombreUsuario + "@" + ipHost + ":" + DireccionMac)
	subprocess.call(shlex.split("sshpass -p '" + contraUsuario +"' ssh -o StrictHostKeyChecking=no " + nombreUsuario + "@" + ipHost + " python " + DireccionMac + NombreArchivo))
	subprocess.call(shlex.split("sshpass -p '" + contraUsuario + "' scp " + nombreUsuario + "@" + ipHost + ":" + DireccionMac + "JPG.tar /home/martin/Documentos/ArchivosDe" + ipHost))
	subprocess.call(shlex.split("sshpass -p '" + contraUsuario + "' scp " + nombreUsuario + "@" + ipHost + ":" + DireccionMac + "PDF.tar /home/martin/Documentos/ArchivosDe" + ipHost))
	subprocess.call(shlex.split("sshpass -p '" + contraUsuario + "' scp " + nombreUsuario + "@" + ipHost + ":" + DireccionMac + "Sh.tar /home/martin/Documentos/ArchivosDe" + ipHost))





