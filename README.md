# cics-nodejs-exci-module
Sample Node.js for z/OS node module demonstrating how to access CICS from z/OS Unix System Services (USS) using the external CICS interface (EXCI)

__Important:__ This cics-exci node module is provided as a SAMPLE and is intended __only for internal use for evaluation purposes and not for use in a production environment__. IBM provides the information and node module without obligation of support and “as is” without warranty of any kind, under the Apache 2.0 license.

To get started with this sample, it is recommended you download and install the sample web app, which can be found here: [https://github.com/cicsdev/cics-nodejs-exci-webapp-sample](https://github.com/cicsdev/cics-nodejs-exci-webapp-sample). Follow the instructions for the web app for use of this node module with an application. Alternatively, to use this sample, you can Install manually, using the instructions below.

Whichever installation method you use, you will also need to:
1.	Configure EXCI in your CICS region
1.	Set up USS for EXCI

Optionally, if you would like to make changes to the sample, you will have to re-build the Native Add-On component.

Instructions for all these steps are provided in this README.

## Features
* Node.js application running on z/OS can access CICS over EXCI
* Pass data to and from CICS over EXCI using CICS Channels and Containers
* Concurrent EXCI requests into CICS

## Sample applications
* [https://github.com/cicsdev/cics-nodejs-exci-webapp-sample](https://github.com/cicsdev/cics-nodejs-exci-webapp-sample)

## Pre-requisites
* IBM CICS Transaction Server for z/OS (CICS) V5.4 - you may run the cics-exci node against a pre-V5.4 CICS region, however the node module utilises EXCI Channels and Containers functionality implemented in CICS V5.4. As such the SDFHEXCI V5.4 library must be in your STEPLIB during execution.
* IBM SDK for Node.js - z/OS, beta 2 - [Download](https://developer.ibm.com/node/sdk/ztp/)
  * __Note:__ ensure that all setup has been completed before you try to use the cics-exci sample node. If you would like to build the cics-exci code, you will also need to install all prerequisites for compiling Node.js Native Add-ons, as described below. 

## Installation

### Cloning GitHub repository

You will first have to clone this GitHub repository onto z/OS. When cloning the GitHub repo, you have two options. Firstly, if possible, use the Git client for z/OS available for download from the [Rocket Software Open Source Tools website](http://www.rocketsoftware.com/zos-open-source/tools).

Alternatively download zipped repo, or clone, onto your local workstation and transfer the files to z/OS. Take care when transferring the files and ensure any file conversions happen as expected. Any zip files should be transferred as binary.

### Installing the sample

To install this sample, from within the repository's root directory, run:

```bash
$ npm install
```

This will pull down all dependencies and install. Once the installation is done copy the contents of this directory into the node_modules directory for any Node.js application that needs to use it. For example:

```bash
$ mkdir /u/user/myNodeApp/node_modules/cics-exci/
$ cp -R * /u/user/myNodeApp/node_modules/cics-exci/
```

__Note:__ The node module includes a Node.js Native Add-on used to access EXCI functionality. This Native Add-on is supplied as a prebuilt binary hosted in this GitHub repository, and downloaded at install time. The code is also supplied in the GitHub repository and can be built manually. For instructions on building the Native Add-on see the instructions at the bottom of this page.

## Using the sample

### Configuring EXCI to work with the sample

*It is advised that you consult with your CICS Systems Programmer to determine how to setup EXCI in your CICS region, and verify that it is working correctly before you use the cics-exci node module.*

#### EXCI setup instructions

You will need to configure the External CICS Interface (EXCI) in your CICS region. Instructions for how to do this can be found here: [Setting up EXCI for static routing](https://www.ibm.com/support/knowledgecenter/en/SSGMCP_5.4.0/configuring/interfaces/dfhtm_staticrouting.html). These instructions include installing the required CONNECTION and SESSION resources for EXCI.

Additionally, as with any EXCI application, you may need to create a custom EXCI options table. You can use this to, for example, override the CICSSVC if required. For more information on the using the DFHXCOPT EXCI options table see the CICS Knowledge Center: [Using the EXCI options table, DFHXCOPT](https://www.ibm.com/support/knowledgecenter/en/SSGMCP_5.4.0/configuring/interfaces/dfhtmf0.html)

#### USS EXCI setup instructions

You will need the EXCI load library in the STEPLIB in USS. You can set this by executing the following command:

```bash
$ export STEPLIB=CICSTS54.CICS.SDFHEXCI:$STEPLIB
```

__Note:__ Substitute the `CICSTS54.CICS` high-level qualifier to match the location of the `SDFHEXCI` load library.

If you require a DFHXCOPT options table, once this has been built, you will need to include the data set containing the DFHXCOPT load module in the USS STEPLIB, in addition to the SDFHEXCI library. You can do this by executing the following command:

```bash
$ export STEPLIB=USERID.LOADLIB:$STEPLIB
```

Where *USERID.LOADLIB* is the data set containing the built DFHXCOPT member.

## Building the cics-exci-bindings Native Add-on
For convenience, the Native Add-on portion of the cics-exci, which includes using the cics-exci-64bit-connector sample to implement EXCI, has been prebuilt and is downloaded as binary when the cics-exci node module is installed. If you would like to extend or view the code for this module, you can build the Native Add-on manually by following the instructions below.

### Pre-reqs
* cics-exci-64bit-connector - the sample EXCI 64-bit connector is included in the node module as a precompiled static library archive. If you would like to see the code for this, extend, or troubleshoot with the connector, you can find the code on GitHub here: [cics-exci-64bit-connector](https://github.com/cicsdev/cics-exci-64bit-connector)
* Node.js Native Add-on support
  * Python v2.7.6 - [available as an open source ported language from Rocket Software](http://www.rocketsoftware.com/zos-open-source)
  * Make v4.0 or higher - [available as an open source ported tool from Rocket Software](http://www.rocketsoftware.com/zos-open-source/tools)
  * node-gyp - required to build a Node.js Native Add-on. Install by running `npm install -g node-gyp`
  * nan (Native Abstractions for Node.js) - required for Node.js Native Add-on development. Install by running `npm install nan`

### Building and installing the Native Add-on

Before building you need to set the `LD_FLAGS` environment variable to point to the SDFHEXCI V5.4 library. You can you this as follows:

```bash
$ export LDFLAGS=\"-l//\'CICTS54.CICS.SDFHEXCI\'\"
```

__Note:__ Substitute the `CICSTS54.CICS` high-level qualifier to match the location of the `SDFHEXCI` load library.

You are now ready to build the node module. To do this, run the following:

```bash
$ npm install --build-from-source
```
This should output build results similar to this:

```bash
> cics-exci@0.1.0 install /u/user/GitHub/cics-nodejs-exci-module
> node-pre-gyp install --fallback-to-build

make: Entering directory '/u/user/GitHub/cics-nodejs-exci-module/build'
  CXX(target) Release/obj.target/cics-exci-bindings/cics-exci.o
include_end nan.h
../nan_temp.h
nan_temp.h
include_end string.h
../string_temp.h
string_temp.h
include_end unistd.h
../unistd_temp.h
unistd_temp.h
include_end entry.h
../entry_temp.h
entry_temp.h
In file included from ../cics-exci_temp.cc:11:
In file included from ../node_modules/nan/nan.h:24:
/u/marholl/.node-gyp/6.11.0/include/node/node_version.h:14:9: warning: 'USTR' macro redefined [-Wmacro-redefined]
#define USTR(x) u8##x
        ^
../cics-exci_temp.cc:1:9: note: previous definition is here
#define USTR(x) U8##x
        ^
1 warning generated.
  SOLINK_MODULE(target) Release/obj.target/cics-exci-bindings.node
  COPY Release/cics-exci-bindings.node
  COPY /u/user/GitHub/cics-nodejs-exci-module/lib/cics-exci-bindings/cics-exci-bindings.node
  TOUCH Release/obj.target/action_after_build.stamp
make: Leaving directory '/u/user/GitHub/cics-nodejs-exci-module/build'
cics-exci@0.1.0 /u/user/GitHub/cics-nodejs-exci-module
```
This has manually built the node module, which can now be used in a Node.js application hosted in z/OS batch.
