import processing.serial.*;
Serial myPort;
String myText="";
void setup(){
size(300, 300);
myPort = new Serial(this, "COM6", 115200);
myPort.bufferUntil('n');
}
void serialEvent (Serial myPort){
myText = myPort.readStringUntil('n');

print(myText);
}
