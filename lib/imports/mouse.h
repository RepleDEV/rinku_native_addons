#ifndef MOUSE_H_
#define MOUSE_H_

#include <windows.h>
#include <string>

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Integer;
using v8::Value;
using v8::Number;

class Mouse {
    public: 
        static void move(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 2 || (!args[0]->IsNumber() || !args[1]->IsNumber())) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int x = (int) args[0].As<Number>()->Value();
            int y = (int) args[1].As<Number>()->Value();

            SetCursorPos(x, y);
        }
};

#endif