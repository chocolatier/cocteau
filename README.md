# Cocteau

## About

Cocteau is the artefact I built as a part of the the ANU's IoT@BIT study tour, during the (Australian) Summer of 2018 to 2019. It is a prototype for an art project exploring the themes of privacy and surveillance in the context of the Internet of Things. It places emphasis on the concept of a "Dossier Society" - A Society where everything an individual does is tracked and collected into "dossiers". 

Conceptually, anything that reads data from the environment and can transmit it to other parts of the internet can be added to Cocteau. However, my project focuses on Audio and Video capture. 

It consists of Raspberry Pis with Cameras and Microphones mounted on Arduino controlled rovers. The rovers explore the surroundings until the Raspberry Pi asks it to stop. The Raspberry Pi listens to and looks at the surroundings, transcribing everything it hears and taking photos at regular intervals. 

# Dependencies

## Arduino

* SharpIR

https://github.com/guillaume-rico/SharpIR

## Python 

* Wand 
* Google Voice API
* Azure API 