#include "circuit.h"
#include <LiquidCrystal.h>
#include "StringLinkedList.h"
#include "NodeList.h"

/* Report notes: 
I had to count the number of digits in a number using recursion. I have to keep the book names short because of the limited space on the LCD.
Had to get previous node manually in the removecurrent function for StringLinkedList.
addSorted sorts array alphebetically.
Checking for NULL is really important in this program. I did that alot.
*/

const int LCD_WIDTH = 16;

bool checkout = false;

StringLinkedList catalogue;
NodeList checkoutArr;
NodeList::Iterator checkMove(checkoutArr.begin());

Circuit circuit(5,2,13,4);
LiquidCrystal lcd(7,8,9,10,11,12);
int count = 0;

void resetScreen(){
  lcd.clear();
  if (checkout){
    lcd.setCursor(0,0);
    if(*checkMove == NULL){
      lcd.print("Nothing!");
    }else{
      lcd.print(*checkMove);
    }
    lcd.setCursor(0,1);
    lcd.print("Checkout");
  }else{
    lcd.setCursor(0,1);
    lcd.print("Catalogue");
    lcd.setCursor(0,0);
    lcd.print(catalogue.getCurrent());
  }
}
void moveCheckout(){
  checkMove++;
  if(checkMove == checkoutArr.end()){
    checkMove = checkoutArr.begin();
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(LCD_WIDTH,2);
  catalogue.addSorted("Emily");
  catalogue.addSorted("Bob");
  catalogue.addSorted("Pih");
  catalogue.addSorted("Goat");
  checkoutArr.insertFront("test1");
  checkoutArr.insertFront("test2");
  checkoutArr.insertFront("test3");
  delay(1000);
  catalogue.resetCurrent();
  resetScreen();
}

void loop() {
  // Get button pressed before if statements.
  bool b1 = circuit.isButton1Pressed();
  bool b2 = circuit.isButton2Pressed();
  bool b3 = circuit.isButton3Pressed();
  if (b1 || b2 || b3){
    circuit.ledSet(true);
  }else{
    circuit.ledSet(false);
  }

  if(b1){
    if (checkout){
      moveCheckout();
    }else{
      catalogue++;
    }
    resetScreen();
  }

  if(b2){
    if (checkout){
      String original = *checkMove;
      if (original != NULL){
        checkoutArr.erase(checkMove);
        checkMove = checkoutArr.begin();
        catalogue.addSorted(original);
      }
    }else{
      String original = catalogue.getCurrent();
      if (original != "Nothing!"){
        catalogue.removeCurrent();
        checkoutArr.insertFront(original);
      }
    }
    resetScreen();
  }

  if(b3){
    if (checkout){
      checkMove = checkoutArr.begin();
      catalogue.resetCurrent();
    }else{
      catalogue.resetCurrent();
      checkMove = checkoutArr.begin();
    }
    checkout = !checkout;
    resetScreen();
  }
  lcd.setCursor(LCD_WIDTH-countDigit(millis() / 1000),1);
  lcd.print(millis() / 1000);
}
