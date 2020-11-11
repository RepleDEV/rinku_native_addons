#ifndef MOUSE_H_
#define MOUSE_H_

#include <napi.h>
#include <windows.h>
#include <string>

using Napi::String;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Number;
using Napi::TypeError;
using Napi::Value;

class Mouse {
    public: 
        static Value move(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 2) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT AMOUNT"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            } else if (!info[0].IsNumber() || !info[1].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPES"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int x = (int) info[0].As<Number>().DoubleValue();
            int y = (int) info[1].As<Number>().DoubleValue();

            SetCursorPos(x, y);

            return env.Undefined();
        }
        static Value down(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT LENGTH"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPE"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int key = (int) info[0].As<Number>().DoubleValue();

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

            return env.Undefined();
        }
        static Value up(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT LENGTH"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPE"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int key = (int) info[0].As<Number>().DoubleValue();

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

            return env.Undefined();
        }
        static Value click(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT LENGTH"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPE"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int key = (int) info[0].As<Number>().DoubleValue();

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

            return env.Undefined();
        }
};

#endif