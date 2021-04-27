#!/bin/bash
DOCKER_CONFIG_FILE="docker-compose.yml"
cnt=0
ports=()
echo "============================================="
echo "Please Configure Your docker-port:"
echo "format, for example:  (Enter port : 10080:80)"
echo "Input 'q' to exit"
echo "Default port mapping:"
echo -e "\t5000:5000(Web_server)"
echo -e "\t22222:22(qemu-system_ssh)"
echo "============================================="

while :
do
    read -p "Enter port : " port  
    if [ $port == "q" ]  
    then  
        echo "Done."
        echo "Please run docker (docker-compose up -d)"
        break
    fi
    ports[cnt]=$port
    let cnt++
done
echo -e "version: \"3\"" > $DOCKER_CONFIG_FILE
echo -e "services:" >> $DOCKER_CONFIG_FILE
echo -e "    qemu-docker:" >> $DOCKER_CONFIG_FILE
echo -e "        image: w22baka/w22_qemu_docker:v2.0" >> $DOCKER_CONFIG_FILE
echo -e "        tty: true" >> $DOCKER_CONFIG_FILE
echo -e "        command: /root/start.sh" >> $DOCKER_CONFIG_FILE
echo -e "        ports:" >> $DOCKER_CONFIG_FILE
echo -e "            - \"5000:5000\"" >> $DOCKER_CONFIG_FILE
echo -e "            - \"22222:22\"" >> $DOCKER_CONFIG_FILE
for ((i=0; i<=cnt-1; i++))
do
    echo -e "            - \"${ports[i]}\"" >> $DOCKER_CONFIG_FILE
done
