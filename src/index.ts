let addon: NodeAddon;

interface NodeAddon {
    // Window functions
    windowFocusTopMost(): string;
    windowFocusOnNthWindow(n: number): string;
    windowGetAllTitles(): Array<string>;

    // Keyboard functions
    keyboardKeyPress(keyCode: number): void;
    keyboardKeyDown(keyCode: number): void;
    keyboardKeyUp(keyCode: number): void;

    // Mouse functions
    mouseMove(x: number, y: number): void;
    mouseDown(button: MouseButtons): void;
    mouseUp(button: MouseButtons): void;
    mouseClick(button: MouseButtons): void;
}

type MouseButtons = "left" | "middle" | "right" | number;

interface WindowObject {
    focusOnTopMost(): string;
    focusOnNthWindow(n: number): string;
    getAllTitles(): Array<string>;
}

interface KeyboardObject {
    keyPress(keyCode: number): void;
    keyDown(keyCode: number): void;
    keyUp(keyCode: number): void;
}

interface MouseObject {
    move(x: number, y: number): void;
    down(button: MouseButtons): void;
    up(button: MouseButtons): void;
    click(button: MouseButtons): void;
    translateButton(button: MouseButtons): number;
}

let windowObject: WindowObject;
let keyboardObject: KeyboardObject;
let mouseObject: MouseObject;

try {
    const { platform } = process;
    addon = require(`../build/Release/rinku_native_addons_${platform}.node`);
    windowObject = {
        focusOnTopMost(): string {
            return addon.windowFocusTopMost();
        },
        focusOnNthWindow(n: number): string {
            return addon.windowFocusOnNthWindow(n);
        },
        getAllTitles(): Array<string> {
            return addon.windowGetAllTitles();
        }
    };
    keyboardObject = {
        keyPress(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyPress(keyCode);
        },
        keyDown(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyDown(keyCode);
        },
        keyUp(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyUp(keyCode);
        }
    };
    mouseObject = {
        move(x: number, y: number): void {
            addon.mouseMove(x, y);
        },
        down(button: MouseButtons): void {
            button = this.translateButton(button);
            addon.mouseDown(button)  
        },
        up(button: MouseButtons): void {
            button = this.translateButton(button);
            addon.mouseUp(button);
        },
        click(button: MouseButtons): void {
            button = this.translateButton(button);
            addon.mouseClick(button);
        },
        translateButton(button: MouseButtons): number {
            switch (button) {
                case "left":
                    return 0;
                case "right":
                    return 2;
                case "middle":
                    return 1;
                default:
                    if (button > 2 || button < 0) {
                        throw new Error("Invalid argument!");
                    } else {
                        return button;
                    }
            }
        }
    };
} catch (err) {
    console.error(
        "[rinku_node_addon] Unsupported platform! All primary functions are disabled!"
    );
}

export {
    windowObject as window,
    keyboardObject as keyboard,
    mouseObject as mouse
};
