import os

os.system('''/home/pi/sakis3g connect --console --

interactive USBINTERFACE='0' APN='tata.docomo.internet' 

APN_USER='BaseStation' APN_PASS='raspberry' ''')

os.system('sudo service hostapd start')

os.system('sudo service udhcpd start')

os.system('sudo ifup wlan0')

os.system('sudo iptables -t nat -A POSTROUTING -o ppp0 -j 

MASQUERADE')

os.system('sudo iptables -A FORWARD -i ppp0 -o wlan0 -m 

state --state RELATED,ESTABLISHED -j ACCEPT')

os.system('sudo iptables -A FORWARD -i wlan0 -o ppp0 -j 

ACCEPT')
