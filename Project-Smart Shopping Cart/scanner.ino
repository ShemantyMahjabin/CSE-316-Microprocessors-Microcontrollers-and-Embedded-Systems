///*
//   MH‑ET LIVE Scanner V3 → Arduino (Serial‑only till)
//   -------------------------------------------------
//   • Scanner S‑TX → D2 , S‑RX → D3
//   • KEY pad to D8 only if you are NOT using Induction mode
//*/
//
//#include <SoftwareSerial.h>
//
///* ---------- pins ---------- */
//constexpr byte PIN_RX  = 2;        // scanner TX -> Arduino RX
//constexpr byte PIN_TX  = 3;        // Arduino TX (rarely used)
//constexpr byte PIN_KEY = 8;        // optional trigger
//
//SoftwareSerial scanner(PIN_RX, PIN_TX);
//
///* ---------- product database ---------- */
//struct Product {
//  const char *code;
//  const char *name;
//  uint16_t    price;     // in taka
//};
//
//Product products[] = {
//  { "8941161113050", "Water",    40   },
//  { "3606000577138", "Cera ve", 3000  },
//  { "0123456789012", "Biscuits", 25   },
//  { "9876543210987", "Soap",     60   }
//};
//const byte NUM_PRODUCTS = sizeof(products) / sizeof(products[0]);
//
///* ---------- globals ---------- */
//String   buf;            // builds the barcode line
//bool     ready   = false;
//uint32_t totalTk = 0;    // running cart total
//
///* ---------- setup ---------- */
//void setup() {
//  pinMode(PIN_KEY, OUTPUT);
//  digitalWrite(PIN_KEY, HIGH);      // KEY idle
//
//  Serial.begin(115200);               // PC console
//  scanner.begin(9600);              // match the scanner’s UART speed
//
//  Serial.println(F("Ready — scan items"));
//  Serial.println(F("(Send R<Enter> to reset total)"));
//}
//
///* ---------- loop ---------- */
//void loop() {
//
//  /* optional KEY pulse every 500 ms — delete if scanner is in Induction */
//  static unsigned long tTrig = 0;
//  if (millis() - tTrig >= 500) {
//    digitalWrite(PIN_KEY, LOW); delay(30); digitalWrite(PIN_KEY, HIGH);
//    tTrig = millis();
//  }
//
//  /* listener for manual reset */
//  if (Serial.available()) {
//    if (toupper(Serial.read()) == 'R') {
//      totalTk = 0;
//      Serial.println(F("Cart cleared."));
//    }
//  }
//
//  /* collect digits from scanner */
//  while (scanner.available()) {
//    char c = scanner.read();
//    if (c == '\r' || c == '\n') {
//      if (buf.length()) ready = true;
//    } else if (isDigit(c)) {
//      buf += c;
//    }
//  }
//
//  /* process full barcode */
//  if (ready) {
//    const Product *hit = nullptr;
//    for (byte i = 0; i < NUM_PRODUCTS; ++i) {
//      if (buf == products[i].code) { hit = &products[i]; break; }
//    }
//
//    if (hit) {
//      totalTk += hit->price;
//      Serial.print(F("Item: "));
//      Serial.print(hit->name);
//      Serial.print(F(" — "));
//      Serial.print(hit->price);
//      Serial.println(F(" Tk"));
//      Serial.print(F("Running total: "));
//      Serial.print(totalTk);
//      Serial.println(F(" Tk"));
//    } else {
//      Serial.print(F("Unknown barcode: "));
//      Serial.println(buf);
//    }
//
//    buf   = "";
//    ready = false;
//  }
//}


/*
   MH‑ET LIVE Scanner V3  – substring rules
   ---------------------------------------
   • Scanner S‑TX → D2 , S‑RX → D3
   • KEY pad to D8 only if *not* using Induction mode
*/
//
//#include <SoftwareSerial.h>
//
///* ----- pins ----- */
//constexpr byte PIN_RX  = 2;      // scanner TX -> Arduino RX
//constexpr byte PIN_TX  = 3;      // Arduino TX -> scanner RX (unused)
//constexpr byte PIN_KEY = 8;      // optional trigger pin
//
//SoftwareSerial scanner(PIN_RX, PIN_TX);
//
///* ----- globals ---- */
//String   buf;                    // builds incoming barcode
//bool     ready     = false;
//uint32_t totalTk   = 0;
//
///* ----- setup ----- */
//void setup() {
//  pinMode(PIN_KEY, OUTPUT);
//  digitalWrite(PIN_KEY, HIGH);   // KEY idle
//
//  Serial.begin(115200);          // PC console
//  scanner.begin(9600);           // match the scanner’s UART baud
//
//  Serial.println(F("Ready — scan items"));
//  Serial.println(F("(Type R + Enter to reset total)"));
//}
//
///* ----- loop ----- */
//void loop() {
//
//  /* optional KEY pulse every 500 ms (remove block if in Induction mode) */
//  static unsigned long tTrig = 0;
//  if (millis() - tTrig >= 500) {
//    digitalWrite(PIN_KEY, LOW); delay(30); digitalWrite(PIN_KEY, HIGH);
//    tTrig = millis();
//  }
//
//  /* manual cart reset */
//  if (Serial.available() && toupper(Serial.read()) == 'R') {
//    totalTk = 0;
//    Serial.println(F("Cart cleared."));
//  }
//
//  /* collect digits from scanner */
//  while (scanner.available()) {
//    char c = scanner.read();
//    if (c == '\r' || c == '\n') {
//      if (buf.length()) ready = true;
//    } else if (isDigit(c)) {
//      buf += c;
//    }
//  }
//
//  /* decide what the code means */
//  if (ready) {
//    if (buf.indexOf("11") != -1) {               // contains “11”
//      totalTk += 40;
//      Serial.println(F("Item: Water — 40 Tk"));
//    }
//    else if (buf.indexOf("00") != -1) {          // contains “00”
//      totalTk += 300;
//      Serial.println(F("Item: Face wash — 300 Tk"));
//    }
//    else {
//      Serial.print(F("Unknown barcode: "));
//      Serial.println(buf);
//    }
//
//    Serial.print(F("Running total: "));
//    Serial.print(totalTk);
//    Serial.println(F(" Tk"));
//    Serial.println();
//
//    buf   = "";                                  // ready for next scan
//    ready = false;
//  }
//}
//
//#include <SoftwareSerial.h>
//
///* ────────── pin map ────────── */
//constexpr byte PIN_RX  = 2;    // scanner TX -> Arduino RX
//constexpr byte PIN_TX  = 3;    // Arduino TX -> scanner RX  (unused)
//constexpr byte PIN_KEY = 8;    // trigger (LOW pulse) – remove if using Induction
//
//SoftwareSerial scanner(PIN_RX, PIN_TX);
//
///* ────────── globals ────────── */
//String   buf;                  // builds incoming barcode
//bool     gotLine     = false;
//uint32_t totalTk     = 0;
//
///* ────────── setup ──────────── */
//void setup() {
//  pinMode(PIN_KEY, OUTPUT);
//  digitalWrite(PIN_KEY, HIGH);          // KEY idle
//
//  Serial.begin(115200);                 // PC console
//  scanner.begin(9600);                  // match the scanner’s UART baud
//
//  Serial.println(F("Ready — scan items"));
//  Serial.println(F("(Type R + Enter to reset total)"));
//}
//
///* ────────── loop ───────────── */
//void loop() {
//
//  /* 1. Fire ONE trigger 250 ms after last decode ----- */
//  if ( buf.length() == 0 && !gotLine) {
//    digitalWrite(PIN_KEY, LOW); delay(0); digitalWrite(PIN_KEY, HIGH);
//  }
//
//  /* 2. Manual cart reset */
//  if (Serial.available() && toupper(Serial.read()) == 'R') {
//    totalTk = 0;
//    Serial.println(F("Cart cleared."));
//  }
//
//  /* 3. Collect digits */
//  while (scanner.available()) {
//    char c = scanner.read();
//    if (c == '\r' || c == '\n') {
//      if (buf.length()) gotLine = true;          // ignore empty CR/LF
//    } else if (isDigit(c)) {
//      buf += c;
//    }
//  }
//
//  /* 4. Process complete barcode line */
//  if (gotLine) {
//    if (buf.indexOf("11") != -1) {               // contains “11”
//      totalTk += 40;
//      Serial.println(F("Item: Water — 40 Tk"));
//    }
//    else if (buf.indexOf("00") != -1) {          // contains “77”
//      totalTk += 3000;
//      Serial.println(F("Face wash — 3000 Tk"));
//    }
//    else if(buf.indexOf("704") != -1) {          // contains “77”
//      totalTk += 500;
//      Serial.println(F("body wash 500Tk"));
//    }
//    else {
//      Serial.print(F("Unknown barcode: "));
//      Serial.println(buf);
//    }
//
//    Serial.print(F("Running total: "));
//    Serial.print(totalTk);
//    Serial.println(F(" Tk\n"));
//
//    /* flush any leftover CR/LF */
//    while (scanner.available()) scanner.read();
//
//    buf        = "";
//    gotLine    = false;                       // arm next trigger guard
//  }
//}


//#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
//
///* ─── scanner pins ─── */
//constexpr byte PIN_RX  = 2;     // scanner TX -> Arduino RX
//constexpr byte PIN_TX  = 3;     // Arduino TX -> scanner RX (unused)
//constexpr byte PIN_KEY = 8;     // trigger pulse (LOW  ≥20 ms)
//
///* ─── LCD pins (RS,E,D4,D5,D6,D7) ─── */
//LiquidCrystal lcd(12, 11, 5, 4, 7, 6);
//SoftwareSerial scanner(PIN_RX, PIN_TX);
//
///* ─── globals ─── */
//String   buf;
//bool     gotLine   = false;
//uint32_t totalTk   = 0;
//
///* ─── setup ─── */
//void setup() {
//  pinMode(PIN_KEY, OUTPUT);
//  digitalWrite(PIN_KEY, HIGH);          // KEY idle
//
//  Serial.begin(115200);                 // PC console
//  scanner.begin(9600);                  // scanner UART baud
//
//  lcd.begin(16, 2);
//  lcd.print("Ready: scan item");
//  Serial.println(F("Ready — scan items (R = reset)"));
//}
//
///* ─── loop ─── */
//void loop() {
//
//  /* fire trigger only when buffer empty & not processing */
//  if (buf.length() == 0 && !gotLine) {
//    digitalWrite(PIN_KEY, LOW); delay(0); digitalWrite(PIN_KEY, HIGH);
//  }
//
//  /* reset cart from PC */
//  if (Serial.available() && toupper(Serial.read()) == 'R') {
//    totalTk = 0;
//    Serial.println(F("Cart cleared."));
//    lcd.clear(); lcd.print("Cart cleared");
//    //delay(1000);
//    lcd.clear(); lcd.print("Ready: scan item");
//  }
//
//  /* read scanner bytes */
//  while (scanner.available()) {
//    char c = scanner.read();
//    if (c == '\r' || c == '\n') {
//      if (buf.length()) gotLine = true;
//    } else if (isDigit(c)) {
//      buf += c;
//    }
//  }
//
//  /* decode once a full line is ready */
//  if (gotLine) {
//    const char* itemName = "Unknown";
//    uint16_t    price    = 0;
//
//    if (buf.indexOf("11") != -1) { itemName = "Water";     price =  40; }
//    else if (buf.indexOf("00") != -1){ itemName = "Facewash";  price = 3000; }
//    else if (buf.indexOf("704")!= -1){ itemName = "Body wash"; price =  500; }
//
//    if (price) {
//      totalTk += price;
//      Serial.print(F("Item: ")); Serial.print(itemName);
//      Serial.print(F(" — "));    Serial.print(price); Serial.println(F(" Tk"));
//    } else {
//      Serial.print(F("Unknown barcode: ")); Serial.println(buf);
//    }
//    Serial.print(F("Running total: ")); Serial.print(totalTk); Serial.println(F(" Tk\n"));
//
//    /* ---- LCD output ---- */
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print(itemName);
//    if (price) { lcd.print(" "); lcd.print(price); }
//    else { lcd.print(":"); lcd.print(buf.substring(0,7)); }
//
//    lcd.setCursor(0,1);
//    lcd.print("Total "); lcd.print(totalTk); lcd.print(" Tk");
//
//    /* flush leftovers, reset for next scan */
//    while (scanner.available()) scanner.read();
//    buf     = "";
//    gotLine = false;
//    //delay(250);                              // guard time before next trigger
//  }
//}
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

/* ─── scanner pins ─── */
constexpr byte PIN_RX  = 2;     // scanner TX -> Arduino RX
constexpr byte PIN_TX  = 3;     // Arduino TX -> scanner RX (unused)
constexpr byte PIN_KEY = 8;     // trigger pulse (LOW  ≥20 ms)

/* ─── LCD pins (RS,E,D4,D5,D6,D7) ─── */
LiquidCrystal lcd(12, 11, 5, 4, 7, 6);
SoftwareSerial scanner(PIN_RX, PIN_TX);

/* ─── globals ─── */
String   buf;
bool     gotLine   = false;
uint32_t totalTk   = 0;

/* ─── setup ─── */
void setup() {
  pinMode(PIN_KEY, OUTPUT);
  digitalWrite(PIN_KEY, HIGH);          // KEY idle

  Serial.begin(115200);                 // PC console
  scanner.begin(9600);                  // scanner UART baud

  lcd.begin(16, 2);
  lcd.print("Ready: scan item");
  Serial.println(F("Ready — scan items (R = reset)"));
}

/* ─── loop ─── */
void loop() {

  /* fire trigger only when buffer empty & not processing */
  if (buf.length() == 0 && !gotLine) {
    digitalWrite(PIN_KEY, LOW); delay(30); digitalWrite(PIN_KEY, HIGH);
  }

  /* reset cart from PC */
  if (Serial.available() && toupper(Serial.read()) == 'R') {
    totalTk = 0;
    Serial.println(F("Cart cleared."));
    lcd.clear(); lcd.print("Cart cleared");
    delay(1000);
    lcd.clear(); lcd.print("Ready: scan item");
  }

  /* read scanner bytes */
  while (scanner.available()) {
    char c = scanner.read();
    if (c == '\r' || c == '\n') {
      if (buf.length()) gotLine = true;
    } else if (isDigit(c)) {
      buf += c;
    }
  }

  /* decode once a full line is ready */
  if (gotLine) {
    const char* itemName = "Unknown";
    uint16_t    price    = 0;
    
//    if (buf.indexOf("11") != -1) { itemName = "Water";     price =  40; }
//    else if (buf.indexOf("00") != -1){ itemName = "Facewash";  price = 3000; }
//    else if (buf.indexOf("704")!= -1){ itemName = "Body wash"; price =  500; }
if (buf.indexOf("8941161113050") != -1) { itemName = "Water";     price =  40; }
    else if (buf.indexOf("3606000577138") != -1){ itemName = "Facewash";  price = 3000; }
    else if (buf.indexOf("07704300222")!= -1){ itemName = "Body wash"; price =  500; }
    else if (buf.indexOf("8941189600952")!= -1){ itemName = "Chips"; price =  20; }
    else if (buf.indexOf("831730003623")!= -1){ itemName = "Dal"; price =  10; }


    if (price) {
      totalTk += price;
      Serial.print(F("Item: ")); Serial.print(itemName); Serial.print(buf);
      Serial.print(F(" — "));    Serial.print(price); Serial.println(F(" Tk"));
    } else {
      Serial.print(F("Unknown barcode: ")); Serial.println(buf);
    }
    Serial.print(F("Running total: ")); Serial.print(totalTk); Serial.println(F(" Tk\n"));

    /* ---- LCD output ---- */
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(itemName);
    if (price) { lcd.print(" "); lcd.print(price); }
    else { lcd.print(":"); lcd.print(buf.substring(0,7)); }

    lcd.setCursor(0,1);
    lcd.print("Total "); lcd.print(totalTk); lcd.print(" Tk");

    /* flush leftovers, reset for next scan */
    while (scanner.available()) scanner.read();
    buf     = "";
    gotLine = false;
    delay(250);                              // guard time before next trigger
  }
}
