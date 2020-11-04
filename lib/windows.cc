#include <node.h>
#include <windows.h>
#include "imports/window.h"
#include "imports/keyboard.h"

namespace rinku {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Integer;
    using v8::Value;
    using v8::Number;

    void init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "windowFocusTopMost", Window::FocusTopmost);
        NODE_SET_METHOD(exports, "keyboardKeyPress", Keyboard::keyPress);
        NODE_SET_METHOD(exports, "keyboardKeyDown", Keyboard::keyDown);
        NODE_SET_METHOD(exports, "keyboardKeyUp", Keyboard::keyUp);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}