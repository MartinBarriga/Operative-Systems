#! /usr/bin/python3
# coding = utf-8
import subprocess
import os


def copia(tipo):
	if(tipo == "jpg"):
		tipoM = "JPG"
	elif(tipo == "pdf"):
		tipoM = "PDF"
	else:
		tipoM = "Sh"		
	DireccionLinux = "/home/martin/Documentos/"
	DireccionMac = "/Users/martin/Documents/"
	subprocess.call(['mkdir', DireccionMac + tipoM])
	lista = subprocess.getoutput('sudo find /Users/martin -name "*."' + tipo) #Cuando use linux le pongo sólo el /
	i = 0
	j = 0

	for caracter in lista:

		if(caracter == '\n'):

			os.system("sudo cp " + lista[j:i] + " "+DireccionMac+tipoM)
			j = i + 1

		i = i + 1
	os.system("tar -cvf " + DireccionMac + tipoM + ".tar " + DireccionMac )

copia("jpg") 
copia("pdf") 
copia("sh") 	