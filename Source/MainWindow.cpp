/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic outline for a simple desktop window.

  ==============================================================================
*/

#include "MainWindow.h"


//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons, true)
{
    centreWithSize (400, 700);
    setVisible (true);
    setResizable(true, true); // resizable, with resize corner (instead of border)
    preset = new PresetComponent();
    setContentOwned(preset, true);
//     setContentComponent(preset);
//     addAndMakeVisible(preset);
}

MainAppWindow::~MainAppWindow()
{
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
