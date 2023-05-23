#!/bin/bash
# Utilisez l'image Tomcat comme base
FROM tomcat:latest

# Copiez l'archive Jenkins war dans le répertoire webapps de Tomcat
COPY jenkins.war /usr/local/tomcat/webapps/

# Déclarez le port d'écoute 8080
EXPOSE 8080


