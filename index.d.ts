/// <reference types="node" />

declare interface WindowObject {
    /**
     * Set window focus to window with highest z-order.
     */
    focusOnTopMost(): string;
}

declare interface KeyboardObject {
    /**
     * Simulate keypress.
     * @param keyCode KeyCode to press. Value must be below 2^8 (256).
     */
    keyPress(keyCode: number): void;
    /**
     * Simulate keydown.
     * @param keyCode KeyCode to hold down. Value must be below 2^8 (256)
     */
    keyDown(keyCode: number): void;
    /**
     * Simulate keyup.
     * @param keyCode KeyCode to toggle up. Value must be below 2^8 (256)
     */
    keyUp(keyCode: number): void;
}

declare interface MouseObject {
    move(x: number, y: number): void;
}

/**
 * Window functions.
 */
declare const windowObject: WindowObject;

/**
 * Keyboard functions
 */
declare const keyboardObject: KeyboardObject;

/**
 * Mouse functions
 */
declare const mouseObject: MouseObject;

export {
    windowObject as window,
    keyboardObject as keyboard,
    mouseObject as mouse
};
