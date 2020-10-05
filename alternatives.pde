
import meter.*;
import processing.serial.*;

Serial port;
String[] list;

Meter m,m2;

void setup() {
  size(950, 400);
  background(0);
  
  port = new Serial(this, "COM3", 9600);

  fill(120, 50, 0);
  m = new Meter(this, 25, 100);
  // Adjust font color of meter value  
  m.setTitleFontSize(15);
  m.setTitleFontName("Arial bold");
  m.setTitle("ALTITUDE (FT)");
  m.setDisplayDigitalMeterValue(true);
  
  // Meter Scale
  String[] scaleLabelsT = {"0", "2000", "4000", "6000", "8000", "10000", "12000", "14000", "16000"};
  m.setScaleLabels(scaleLabelsT);
  m.setScaleFontSize(18);
  m.setScaleFontName("Times New Roman bold");
  m.setScaleFontColor(color(0, 0, 0));
  
  m.setArcColor(color(200, 200, 200));
  m.setArcThickness(10);
  m.setMaxScaleValue(15000);
  
  m.setNeedleThickness(4);
  
  m.setMinInputSignal(0);
  m.setMaxInputSignal(15000);

  // A second meter for reference
  int mx = m.getMeterX();
  int my = m.getMeterY();
  int mw = m.getMeterWidth();
  
    m2 = new Meter(this, mx + mw + 20, my);
  m2.setTitleFontSize(15);
  m2.setTitleFontName("Arial bold");
  m2.setTitle("AIRSPEED (KNOTS)");
  m2.setDisplayDigitalMeterValue(true);
  
    String[] scaleLabelsH = {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150"};
  m2.setScaleLabels(scaleLabelsH);
  m2.setScaleFontSize(18);
  m2.setScaleFontName("Times New Roman bold");
  m2.setScaleFontColor(color(0, 0,0));
  
  m2.setArcColor(color(200, 200, 200));
  m2.setArcThickness(10);
  m2.setMaxScaleValue(150);
  
  m2.setNeedleThickness(4);
  
  m2.setMinInputSignal(0);
  m2.setMaxInputSignal(150);
}

public void draw() {
  
  textSize(30);
  fill(255, 255, 255);
  text("ALTIMETER AND AIRSPEED INDICATOR", 200, 50);
  
  if (port.available() > 0) {
    String val = port.readString();
    list = split(val, ',');
    float altt = float(list[0]);
    float airsp = float(list[1]);
       if (altt>1000 & airsp>=0){
            println("ALTITUDE: " + altt + " FT  " + "AIRSPEED: " + airsp + " KNOTS");
            m.updateMeter(int(altt));
            m2.updateMeter(int(airsp));
       }
    delay(500);
  }
}
