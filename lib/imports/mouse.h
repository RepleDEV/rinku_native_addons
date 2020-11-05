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
using v8::Boolean;

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
        static void down(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int key = (int) args[0].As<Number>()->Value();

            INPUT input;

            input.type = INPUT_MOUSE;
            if (key == 0) {
                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            } else if (key == 1) {
                input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            } else if (key == 2) {
                input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            }

            SendInput(1, &input, sizeof(INPUT));
        }
        static void up(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int key = (int) args[0].As<Number>()->Value();

            INPUT input;

            input.type = INPUT_MOUSE;
            if (key == 0) {
                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            } else if (key == 1) {
                input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            } else if (key == 2) {
                input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            }

            SendInput(1, &input, sizeof(INPUT));
        }
        static void click(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }
            
            int key = (int) args[0].As<Number>()->Value();

            INPUT inputs[2] = {0};

            inputs[0].type = INPUT_MOUSE;
            inputs[1].type = INPUT_MOUSE;
            if (key == 0) {
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            } else if (key == 1) {
                inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
                inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            } else if (key == 2) {
                inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            }

            SendInput(2, inputs, sizeof(INPUT));
        }
};

#endif