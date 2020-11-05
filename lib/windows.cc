#include <node.h>
#include <windows.h>

#include "imports/window.h"
#include "imports/keyboard.h"
#include "imports/mouse.h"

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
        // Window functions
        NODE_SET_METHOD(exports, "windowFocusTopMost", Window::FocusTopmost);
        
        // Keyboard functions
        NODE_SET_METHOD(exports, "keyboardKeyPress", Keyboard::keyPress);
        NODE_SET_METHOD(exports, "keyboardKeyDown", Keyboard::keyDown);
        NODE_SET_METHOD(exports, "keyboardKeyUp", Keyboard::keyUp);

        // Mouse functions
        NODE_SET_METHOD(exports, "mouseMove", Mouse::move);
        NODE_SET_METHOD(exports, "mouseDown", Mouse::down);
        NODE_SET_METHOD(exports, "mouseUp", Mouse::up);
        NODE_SET_METHOD(exports, "mouseClick", Mouse::click);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}