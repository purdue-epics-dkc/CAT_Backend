# README #
### Summary ###

* This is a stand-in backend for the EPICS DKC CAT app that parses single digit numbers in ASL. It is used for demonstrations while the machine learning tools that will run on the final backend are being developed.

### Setup ###
* Meant to be run as an [Azure Functions](https://azure.microsoft.com/en-us/services/functions/) service to the [Azure Mobile App](https://azure.microsoft.com/en-us/services/app-service/mobile/) backend.
* Uses a [Node.js C++ Addon](https://nodejs.org/api/addons.html) to process the data.
	* To get set up, run the following code from the console:
		* ```
			node-gyp configure
			node-gyp build
		```
