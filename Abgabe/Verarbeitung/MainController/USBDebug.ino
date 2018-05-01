void debugCommand(){
  String command = inputString;
  inputString = "";
  stringComplete = false;

  if(command.substring(0,2) == "poll") Serial.print("push");
  else usbCommandsCustom(command);

}

