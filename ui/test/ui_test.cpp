#include <Application.h>
#include <SmartUI.h>
#include <Util.h>
using namespace SmartUI;

int main(int argc, char** argv) {
  Application* app = new Application();
  SmartUI::Window* win = new SmartUI::Window();
  win->setWidth(600);
  win->setHeight(600);
  win->setBgColor(Util::getRandomColor());

  View* v1 = new View();
  v1->setPosition(100, 100);
  v1->setSize(300, 300);
  v1->setBgColor(Util::getRandomColor());
  v1->setCliping(false);

  View* v2 = new View();
  v2->setPosition(0, 100);
  v2->setSize(100, 100);
  v2->setBgColor(Util::getRandomColor());

  View* v3 = new View();
  v3->setPosition(250, 250);
  v3->setSize(100, 100);
  v3->setBgColor(Util::getRandomColor());

  View* v4 = new View();
  v4->setPosition(150, 50);
  v4->setSize(100, 100);
  v4->setBgColor(Util::getRandomColor());
  v4->setVisible(false);

  v1->addChild(v3);
  v1->addChild(v2);
  v1->addChild(v4);
  win->addChild(v1);

  win->show();
  app->exec();
}
