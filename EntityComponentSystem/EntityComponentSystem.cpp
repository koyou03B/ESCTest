#include <iostream>
#include"Scene.h"

int main()
{
   Scene& scene = GetScene();
   scene.Init();
   scene.Update();
   scene.Render();

}
