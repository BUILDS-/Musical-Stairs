import fullscreen.*;
import japplemenubar.*;


int row1 = 245;
int row2 = 510;
int row3 = 775;

int column1 = 170; 
int column2 = 540;
int column3 = 910;

int dimen = 200; // x&y dimensions of images, they are square so values are the same

int inst1x = column1;
int inst1y = row1;
int inst1w = dimen;
int inst1h = dimen;

int inst2x = column2;
int inst2y = row1;
int inst2w = dimen;
int inst2h = dimen;

int inst3x=column3;
int inst3y=row1;
int inst3w=dimen;
int inst3h=dimen;

int inst4x=column1;
int inst4y=row2;
int inst4w=dimen;
int inst4h=dimen;

int inst5x=column2;
int inst5y=row2;
int inst5w=dimen;
int inst5h=dimen;

int inst6x=column3;
int inst6y=row2;
int inst6w=dimen;
int inst6h=dimen;

int inst7x=column1;
int inst7y=row3;
int inst7w=dimen;
int inst7h=dimen;

int inst8x=column2;
int inst8y=row3;
int inst8w=dimen;
int inst8h=dimen;

int inst9x=column3;
int inst9y=row3;
int inst9w=dimen;
int inst9h=dimen;


int returnx=1000;
int returny=70;
int returnw=dimen/2;
int returnh=dimen/2;

int mode = 1; // auto starts with piano selected
int prevmode = 1; //previous mode to stop infinaite looping when same instrument is selected.

//button declaration
ImageButtons button1, button2, button3, button4, button5, button6, button7, button8, button9;

FullScreen fs;

//image declaration
PImage backg;

PImage img1; 
PImage img1r;
PImage img1d;

PImage img2;
PImage img2r;
PImage img2d;

PImage img3;
PImage img3r;
PImage img3d;

PImage img4;
PImage img4r;
PImage img4d;

PImage img5;
PImage img5r;
PImage img5d;

PImage img6;
PImage img6r;
PImage img6d;

PImage img7;
PImage img7r;
PImage img7d;

PImage img8;
PImage img8r;
PImage img8d;

PImage img9;
PImage img9r;
PImage img9d;

void setup() {
  size(1280, 1024);

  //Image setup
  
  //instruments, Piano, Trumpet, Guitar, Organ, Keyboard, Harpsichord, Violin, Cello, Bagpipes
  backg = loadImage("msbackground.jpg");

  img1 = loadImage("1.jpg");
  img1r = img1;
  img1d = loadImage("1d.jpg");

  img2 = loadImage("2.jpg");  
  img2r = img2;
  img2d = loadImage("2d.jpg");

  img3 = loadImage("3.jpg");
  img3r = img3;
  img3d = loadImage("3d.jpg");

  img4 = loadImage("4.jpg");
  img4r = img4;
  img4d = loadImage("4d.jpg");

  img5 = loadImage("5.jpg");
  img5r = img5;
  img5d = loadImage("5d.jpg");

  img6 = loadImage("6.jpg");
  img6r = img6;
  img6d = loadImage("6d.jpg");

  img7 = loadImage("7.jpg");
  img7r = img7;
  img7d = loadImage("7d.jpg");

  img8 = loadImage("8.jpg");
  img8r = img8;
  img8d = loadImage("8d.jpg");

  img9 = loadImage("9.jpg");
  img9r = img9;  
  img9d = loadImage("9d.jpg");





  //Button setup
  button1 = new ImageButtons(inst1x,inst1y,inst1w,inst1h,img1,img1r,img1d);
  button2 = new ImageButtons(inst2x,inst2y,inst2w,inst2h,img2,img2r,img2d);
  button3 = new ImageButtons(inst3x,inst3y,inst3w,inst3h,img3,img3r,img3d);
  button4 = new ImageButtons(inst4x,inst4y,inst4w,inst4h,img4,img4r,img4d);
  button5 = new ImageButtons(inst5x,inst5y,inst5w,inst5h,img5,img5r,img5d);
  button6 = new ImageButtons(inst6x,inst6y,inst6w,inst6h,img6,img6r,img6d);
  button7 = new ImageButtons(inst7x,inst7y,inst7w,inst7h,img7,img7r,img7d);
  button8 = new ImageButtons(inst8x,inst8y,inst8w,inst8h,img8,img8r,img8d);
  button9 = new ImageButtons(inst9x,inst9y,inst9w,inst9h,img9,img9r,img9d);

  frameRate(30);
  fs = new FullScreen(this);
  fs.enter();
}

void draw() {
  background(backg);
  manageButtons();

  // current mode image
  if (mode == 1) {
    image(img1,returnx,returny,returnh,returnw);
    if (prevmode !=1) {
      open("/usr/bin/inst1.sh");
      prevmode=1;
    }
  } 
  if (mode == 2) {
    image(img2,returnx,returny,returnh,returnw); 
    if (prevmode !=2) {
      open("/usr/bin/inst2.sh");
      prevmode=2;
    }
  }
  if (mode == 3) {
    image(img3,returnx,returny,returnh,returnw); 
    if (prevmode !=3) {
      open("/usr/bin/inst3.sh");
      prevmode=3;
    }
  }
  if (mode == 4) {
    image(img4,returnx,returny,returnh,returnw); 
    if (prevmode !=4) {
      open("/usr/bin/inst4.sh");
      prevmode=4;
    }
  }
  if (mode == 5) {
    image(img5,returnx,returny,returnh,returnw); 
    if (prevmode !=5) {
      open("/usr/bin/inst5.sh");
      prevmode=5;
    }
  }
  if (mode == 6) {
    image(img6,returnx,returny,returnh,returnw); 
    if (prevmode !=6) {
      open("/usr/bin/inst6.sh");
      prevmode=6;
    }
  }
  if (mode == 7) {
    image(img7,returnx,returny,returnh,returnw); 
    if (prevmode !=7) {
      open("/usr/bin/inst7.sh");
      prevmode=7;
    }
  }
  if (mode == 8) {
    image(img8,returnx,returny,returnh,returnw); 
    if (prevmode !=8) {
      open("/usr/bin/inst8.sh");
      prevmode = 8;
    }
  }
  if (mode == 9) {
    image(img9,returnx,returny,returnh,returnw); 
    if (prevmode !=9) {
     open("/usr/bin/inst9.sh");
     prevmode = 9;
    }
  }
}

void manageButtons() {
  button1.update();
  button1.display();
  button2.update();
  button2.display();
  button3.update();
  button3.display();
  button4.update();
  button4.display();
  button5.update();
  button5.display();
  button6.update();
  button6.display();
  button7.update();
  button7.display();
  button8.update();
  button8.display();
  button9.update();
  button9.display();
}


void mousePressed() {
  if (button1.pressed() == true) { 
    prevmode = mode; 
    mode = 1;
  }
  if (button2.pressed() == true) { 
    prevmode = mode; 
    mode = 2;
  } 
  if (button3.pressed() == true) {
    prevmode = mode;  
    mode = 3;
  }
  if (button4.pressed() == true) {
    prevmode = mode; 
    mode = 4;
  }
  if (button5.pressed() == true) {
    prevmode = mode; 
    mode = 5;
  }
  if (button6.pressed() == true) {
    prevmode = mode; 
    mode = 6;
  }
  if (button7.pressed() == true) {
    prevmode = mode;
    mode = 7;
  }
  if (button8.pressed() == true) {
    prevmode = mode;
    mode = 8;
  }
  if (button9.pressed() == true) {
    prevmode = mode;
    mode = 9;
  }
}



class Button
{
  int x, y;
  int w, h;
  color basecolor, highlightcolor;
  color currentcolor;
  boolean over = false;
  boolean pressed = false;   

  boolean pressed() {
    if(over && mousePressed) {
      pressed = true;
    } 
    else {
      pressed = false;
    }
    return pressed;
  }

  boolean overRect(int x, int y, int width, int height) {
    if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
      return true;
    } 
    else {
      return false;
    }
  }
}

class ImageButtons extends Button 
{
  PImage base;
  PImage roll;
  PImage down;
  PImage currentimage;

  ImageButtons(int ix, int iy, int iw, int ih, PImage ibase, PImage iroll, PImage idown) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    base = ibase;
    roll = iroll;
    down = idown;
    currentimage = base;
  }

  void update() 
  {
    over();
    pressed();
    if(pressed) {
      currentimage = down;
    } 
    else if (over) {
      currentimage = roll;
    } 
    else {
      currentimage = base;
    }
  }

  void over() 
  {
    if( overRect(x, y, w, h) ) {
      over = true;
    } 
    else {
      over = false;
    }
  }

  void display() 
  {
    image(currentimage, x, y);
  }
}

