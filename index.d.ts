/// <reference types="node" />

declare type MouseButtons = 
    "left" | 
    "middle" | 
    "right" | 
    number;

/**
 * Window functions
 */
declare interface WindowObject {
    /**
     * Set window focus to window with highest z-order.
     */
    focusOnTopMost(): string;
    /**
     * Set window focus to the n-th z-order.
     * @param n Z-Order
     */
    focusOnNthWindow(n: number): string;
    /**
     * Gets all active window titles.
     * 
     * @returns A string array according to their z-order.
     */
    getAllTitles(): Array<string>;
}

/**
 * Keyboard functions
 */
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

/**
 * Mouse functions
 */
declare interface MouseObject {
    /**
     * Simulate mouse movements. Might not work on multi-monitor setups.
     * @param x X Coordinate
     * @param y Y Coordinate
     */
    move(x: number, y: number): void;
    /**
     * Simulate mouse DOWN. 
     * @param button Mouse button to click
     */
    down(button: MouseButtons): void;
    /**
     * Simulate mouse UP
     * @param button Mouse button to click
     */
    up(button: MouseButtons): void;
    /**
     * Simulate mouse CLICK
     * @param button Mouse button to click
     */
    click(button: MouseButtons): void;
    /**
     * Translates AND validates mouse button types.
     * @param button Mouse button to click
     */
    translateButton(button: MouseButtons): number;
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
