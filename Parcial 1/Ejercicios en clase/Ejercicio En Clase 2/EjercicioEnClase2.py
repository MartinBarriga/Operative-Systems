#! /usr/bin/python3
import subprocess
import os

def copia(tipo):
	if(tipo == "jpg"):
		tipoM = "JPG"
	elif(tipo == "pdf"):
		tipoM = "PDF"
	else:
		tipoM = "Sh"		

	subprocess.call(['mkdir', '/home/martin/Documentos/' + tipoM])
	lista = subprocess.getoutput('sudo find / -name "*."' + tipo)
	i = 0
	j = 0

	for caracter in lista:

		if(caracter == '\n'):

			os.system("sudo cp " + lista[j:i] + " /home/martin/Documentos/"+tipoM)
			j = i + 1

		i = i + 1


copia("jpg")
copia("pdf")
copia ("sh")