#include <node.h>
#include "tpx3entrypoint.h"
#include <iostream>
#include <stdio.h>
#include <v8.h>
#include <uv.h>

namespace tpx3data {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Exception;
using v8::Number;
using namespace v8;

struct Work {
	uv_work_t request;
	Persistent<Function> callback;


	double startTime;
	double timeSlice;
	std::string fileName;
	std::string result;
};

bool CheckIfNum(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();
	if (!args[0]->IsNumber()){
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong arguments")
			));
		return false;
	}
	return true;
}

bool CheckArgs(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();
	if (args.Length() < 2){
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong number of arguments")
			));
		return false;
	}

	if (!args[0]->IsNumber() || !args[1]->IsNumber()){
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong arguments")
			));
		return false;
	}
	return true;
}

void GetInterval(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();

	if (!CheckArgs(args)){
		return;		
	}
	TPX3EntryPoint * tep;

	if (args.Length() <= 2){
		tep = new TPX3EntryPoint();
	} else {
		tep = new TPX3EntryPoint(*String::Utf8Value(args[2]->ToString()));	
	}

	std::string s = tep->GetInterval(args[0]->NumberValue(), args[1]->NumberValue());
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, s.c_str()));
	delete tep;
}

static void WorkAsync(uv_work_t *req){
	Work* work = static_cast<Work *>(req->data);
	TPX3EntryPoint * tep = new TPX3EntryPoint(work->fileName);
	work->result = tep->GetInterval(work->startTime, work->timeSlice);
	delete tep;
}

static void WorkAsyncComplete(uv_work_t *req, int status){
	Isolate * isolate = Isolate::GetCurrent();
	v8::HandleScope handleScope(isolate);

	Work * work = static_cast<Work *>(req->data);

	Handle<Value> argv[] = { String::NewFromUtf8(isolate, work->result.c_str()) };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, argv);

	work->callback.Reset();

	delete work;
}

void GetIntervalAsync(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();
	//
	//
	Work * work = new Work();
	work->request.data = work;
	work->startTime = args[0]->NumberValue();
	work->timeSlice = args[1]->NumberValue();
	work->fileName = *String::Utf8Value(args[2]->ToString());

	Local<Function> callback = Local<Function>::Cast(args[3]);
	work->callback.Reset(isolate, callback);

	uv_queue_work(uv_default_loop(), &work->request, WorkAsync, WorkAsyncComplete);


	args.GetReturnValue().Set(Undefined(isolate));
}

void Convert(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();

	TPX3EntryPoint * tep = new TPX3EntryPoint();

	std::string s = tep->Convert(*String::Utf8Value(args[0]->ToString()), *String::Utf8Value(args[1]->ToString()));

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, s.c_str()));
	delete tep;
}

void GetTrigger(const FunctionCallbackInfo<Value>& args){
	Isolate * isolate = args.GetIsolate();

	if (!CheckIfNum(args)){
		return;
	}

	TPX3EntryPoint * tep = new TPX3EntryPoint();
	std::string s = tep->GetTrigger(args[0]->NumberValue());

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, s.c_str()));
	delete tep;
}


void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getInterval", GetInterval);
  NODE_SET_METHOD(exports, "getIntervalAsync", GetIntervalAsync);
  NODE_SET_METHOD(exports, "getTrigger", GetTrigger);
  NODE_SET_METHOD(exports, "convert", Convert);
}

NODE_MODULE(addon, init)

} 