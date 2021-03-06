#include "SimScreen.h"

#include "BlipSim.h"
#include "ApplicationConfiguration.h"
#include "LedController.h"

static int row_count = 8;
static int column_count = 10;
static SimScreen *simstance = NULL;

SimScreen::SimScreen ()
{
  setMouseCursor(MouseCursor::CrosshairCursor);
  if(simstance == NULL)
    simstance = this;
}

SimScreen::~SimScreen()
{
  if(simstance == this)
    simstance = NULL;
}

void SimScreen::position(const Point<float> p){
  BlipSim* blipsim = ApplicationConfiguration::getBlipSim();  
  blipsim->position(p.getX()/getWidth()*1024, p.getY()/getHeight()*1024);
}

void SimScreen::mouseDown (const MouseEvent& e)
{
  position(getMouseXYRelative().toFloat());
}

void SimScreen::mouseDrag (const MouseEvent& e)
{
  if(contains(e.getPosition()))
    position(getMouseXYRelative().toFloat());
}

void SimScreen::mouseUp (const MouseEvent& e){
  ApplicationConfiguration::getBlipSim()->release();
}

void SimScreen::mouseExit (const MouseEvent& e){
//   ApplicationConfiguration::getBlipSim()->release();
}

void SimScreen::paint (Graphics& g)
{
  BlipSim* blipsim = ApplicationConfiguration::getBlipSim();
  g.fillAll(Colours::black);
  if(blipsim->isPressed()){
    g.setColour(Colours::grey);
    float x = blipsim->getPosition().x*getWidth()/1024;
    float y = getHeight() - blipsim->getPosition().y*getHeight()/1024;
    g.drawLine(x, 0, x, getHeight());
    g.drawLine(0, y, getWidth(), y);
  }
  g.setColour(Colours::red);
  float width = std::min((float)getWidth()/column_count, (float)getHeight()/row_count)*0.8;
  float margin = width/2;
  g.setOrigin(margin, margin);
  float dx = (getWidth()-margin) / column_count;
  float dy = (getHeight()-margin) / row_count;
  for(int col=0; col<column_count; ++col){
    for(int row=0; row<row_count; ++row){
      g.setOpacity(0.4);
      g.drawEllipse(col*dx, row*dy, width, width, 4);
      uint8_t value = blipsim->getLed(col, row_count-row-1);
      // adjust for non-linear LED brightness
//       value = std::min(value*4, 0xff);
      value = (uint8_t)std::min((sqrt((float)value)*16.0), 255.0);
//       g.setColour(c.withBrightness(value/255.0));
      g.setOpacity(value/255.0);
      g.fillEllipse(col*dx, row*dy, width, width);
    }
  }
}

void SimScreen::resized()
{  
}

void LedController::init(){
  back_buffer = buf1;
  counter.init();
}

void LedController::flip(){
//   uint8_t* front_buffer = flipped ? buf2 : buf1;
//   back_buffer = flipped ? buf1 : buf2;  
//   // memcpy(to, from, bytes)
//   memcpy(back_buffer, front_buffer, LED_BUFFER_LENGTH);
//   flipped = !flipped;
  const MessageManagerLock mmLock;
  if(simstance){
    simstance->repaint();
  }
}

void LedController::displayCurrentRow(void){
  counter.tick();
}

void LedController::sendBufferData(uint8_t row){
}
