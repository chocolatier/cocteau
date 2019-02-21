# Cocteau

## About

Cocteau is the artefact I built as a part of the the ANU's IoT@BIT study tour, during the (Australian) Summer of 2018 to 2019. It is a prototype for an art project exploring the themes of privacy and surveillance in the context of the Internet of Things. It places emphasis on the concept of a "Dossier Society" - A Society where everything an individual does is tracked and collected into "dossiers". 

I have written about why privacy matters in the [course blog](https://cs.anu.edu.au/courses/china-study-tour/news/#chocolatier), which also documents my design process. Particularly in weeks [#5](https://cs.anu.edu.au/courses/china-study-tour/news/2018/12/24/chocolatier-privacy/), [#6](https://cs.anu.edu.au/courses/china-study-tour/news/2019/01/04/chocolatier-project-diary/) and [#11](https://cs.anu.edu.au/courses/china-study-tour/news/2019/02/08/chocolatier-project-diary6/). 

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

## Contact 

The best way to reach me is to open an issue on GitHub. You may also email me at \[github username\] \[at\] dedekinddomai \[dot\] nz