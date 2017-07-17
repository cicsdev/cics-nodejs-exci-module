/* Licensed Materials - Property of IBM                               */
/*                                                                    */
/* SAMPLE                                                             */
/*                                                                    */
/* (c) Copyright IBM Corp. 2017 All Rights Reserved                   */
/*                                                                    */
/* US Government Users Restricted Rights - Use, duplication or        */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp   */

#include <nan.h>
#include <string.h>
#include <unistd.h>
#include "entry.h"

#pragma convert("IBM-1047")
void Link(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 3) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}

	if (!info[0]->IsString() || !info[1]->IsString() || !info[2]->IsString()) {
		Nan::ThrowTypeError("Wrong arguments");
		return;
	}

	Nan::Utf8String uapplid(info[0]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*uapplid);                            // convert from Utf8 to Ebcdic
    char *applid = *uapplid;

    Nan::Utf8String uprogram(info[1]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*uprogram);                            // convert from Utf8 to Ebcdic
    char *program = *uprogram;

    Nan::Utf8String uchannel(info[2]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*uchannel);                            // convert from Utf8 to Ebcdic
    char *channel = *uchannel;

	/* Standard return code */
	int rc = 0;

	rc = execCicsLinkChannel(applid, program, channel);

	/* Free off our storage */
	free(applid);
	free(program);
	free(channel);

	/* Return from here */
	v8::Local<v8::Number> num = Nan::New(rc);
	info.GetReturnValue().Set(num);
}


void PutContainer(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	/* Standard return code */
	int rc = 0;

    Nan::Utf8String uchannel(info[0]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*uchannel);                            // convert from Utf8 to Ebcdic
    char *channel = *uchannel;

    Nan::Utf8String ucontainer(info[1]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*ucontainer);                            // convert from Utf8 to Ebcdic
    char *container = *ucontainer;

    Nan::Utf8String udata(info[2]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*udata);                            // convert from Utf8 to Ebcdic
    char *data = *udata;

    int dataLength = strlen(data);

	rc = execCicsPutContainerString(container, channel, data, dataLength);

	free(channel);
    free(container);
    free(data);

	/* Return from here */
	v8::Local<v8::Number> num = Nan::New(rc);
	info.GetReturnValue().Set(num);
}

void GetContainer(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	v8::Isolate * isolate = info.GetIsolate();

	Nan::Utf8String uchannel(info[0]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*uchannel);                            // convert from Utf8 to Ebcdic
    char *channel = *uchannel;

    Nan::Utf8String ucontainer(info[1]->ToString()); // Create a Nan wrapped Utf8 string
    __a2e_s(*ucontainer);                            // convert from Utf8 to Ebcdic
    char *container = *ucontainer;

	char * data;
	int utf8 = 1208; // Tell CICS to return in UTF-8

	data = execCicsGetContainerString(container, channel, utf8);

    free(channel);
    free(container);

	/* Return from here */
	v8::Local<v8::String> retval = v8::String::NewFromUtf8(isolate, data);
	free(data);

	info.GetReturnValue().Set(retval);
}
#pragma convert(pop)

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("programLink").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Link)->GetFunction());

  exports->Set(Nan::New("putContainer").ToLocalChecked(),
                   Nan::New<v8::FunctionTemplate>(PutContainer)->GetFunction());

  exports->Set(Nan::New("getContainer").ToLocalChecked(),
                   Nan::New<v8::FunctionTemplate>(GetContainer)->GetFunction());
}

NODE_MODULE(cicsEXCIBindings, Init)
