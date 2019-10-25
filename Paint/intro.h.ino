void intro(hd44780_I2Cexp lcd){
  String projectName = PROJECT_NAME;
  String version = VERSION;
  
	lcd.clear(); 
	lcd.setCursor(0, 0);
	lcd.print("TMEeducation.com");
  
	lcd.setCursor(0, 1);
  for(int i = 0; i < (16 - projectName.length()) / 2; i++){
    lcd.print(" ");
  }
	lcd.print(PROJECT_NAME);
  
	delay(2500);
  
	lcd.setCursor(0, 1);
  lcd.print("                ");
  
  lcd.setCursor(0, 1);
  for(int i = 0; i < (16 - version.length()) / 2; i++){
    lcd.print(" ");
  }
	lcd.print(VERSION);

	delay(2500);  
  lcd.clear();
  delay(100);
}
