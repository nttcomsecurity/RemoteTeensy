void multipleKey(int modifier, int key1, int key2 = 0) {
  Keyboard.set_modifier(modifier);
  Keyboard.set_key1(key1);
  Keyboard.set_key2(key2);
  Keyboard.send_now();
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.set_key2(0);
  Keyboard.send_now();
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//test : 0x10=8 0x40=32 76
void remoteKeyboard(String input) {
  String temp_special;
  int k1;
  int k2;
  int k3;

  if(input != "") 
  {
    input.replace("\r", "");
    input.replace("\n", "");
    Serial.println(input);

    //Magic string S#S (modifier, key1, key2) or S#M (modifier, modifier, key)
    if (input.substring(0,2) == "S#") {

    
    if ((input.substring(2,3) == "S") or (input.substring(2,3) == "M"))   {
      temp_special = input.substring(3);
      
      k1 = getValue(temp_special, ':', 0).toInt();
      //if (k1 == "") k1 = 0;
      k2 = getValue(temp_special, ':', 1).toInt();
      //if (k2 == "") k2 = 0;
      if (getValue(temp_special, ':', 2) != "") { k3 = getValue(temp_special, ':', 2).toInt(); } //else { k3 = 0; }

      //Debug
      Serial.println(k1);
      Serial.println(k2);
      Serial.println(k3);

      //Send modifiers and keys
      if (input.substring(2,3) == "M") {
          k1 = k1 | k2;
          k2 = k3;
          k3 = 0;
          multipleKey(k1 | k2, k3, 0);  
      }
      
      multipleKey(k1, k2, k3);

    //If just a string, everything is sent without processing  
    } } else {
      Keyboard.print(input);
    }     
  } 
  }
