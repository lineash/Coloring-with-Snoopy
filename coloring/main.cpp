//
//  main.cpp
//  coloring
//
//  Created by line.ash on 2021/11/29.
//

#include <iostream>
#include <bangtal>
using namespace bangtal;

extern ScenePtr mainScene;
ScenePtr color_scene1, color_scene2, color_end;
ObjectPtr color_startButton, color_endButton;
ObjectPtr color_story[7], color_howto;
ObjectPtr color_colorButton[6];
ObjectPtr color_drawing_base;
ObjectPtr color_blue;
ObjectPtr color_white[6];
ObjectPtr color_ivory;
ObjectPtr color_brown;
ObjectPtr color_yellow;
ObjectPtr color_red;
int blue = 0, white = 0, yellow = 0, brown = 0, red = 0, ivory = 0;
bool coloring_check_clear()
{
    if(blue>0 && white > 5 && yellow > 0 && brown > 0 && red > 0 && ivory > 0)
    {
        return true;
    }
    return false;
}
ScenePtr coloring_game_init() //이 함수로 시작하면 됩니당. coloring_game_init()->enter(); 천재민정 파이팅^^
{
    //int blue = 0, white = 0, yellow = 0, brown = 0, red = 0, ivory = 0;
    //씬1 생성
    color_scene1 = Scene::create("color_scene1", "color_scene1.png");
    
    color_startButton = Object::create("color_startButton.png", color_scene1, 880, 200);
    color_endButton = Object::create("color_endButton.png", color_scene1, 880, 100);
    
    color_startButton->setScale(0.25);
    color_endButton->setScale(0.25);
    
    //씬2 생성
    color_scene2 = Scene::create("color_scene2", "background.png");
    for(int i = 0; i<6 ; i++)
    {
        char buf[30];
        sprintf(buf, "color_button_%d.png", i);
        color_colorButton[i] = Object::create(buf, color_scene2, 1150, 42 + 113*i);
        color_colorButton[i]->setOnMouseCallback([&, i](ObjectPtr object, int x, int y, MouseAction action)->bool{
            switch (i) {
                case 5:
                    if(blue < 1)
                    {
                        color_blue = Object::create("drawing_11.png", color_scene2, 300, 73);
                        blue++;
                    }
                    break;
                case 4:
                    if(white < 6)
                    {
                        char buf[40];
                        sprintf(buf, "drawing_white_%d.png", white);
                        color_white[white] = Object::create(buf, color_scene2, 300, 73);
                        white+=1;
                    }
                    break;
                case 3:
                    if(yellow < 1)
                    {
                        color_yellow = Object::create("drawing_5.png", color_scene2, 300, 73);
                        yellow++;
                    }
                    break;
                case 2:
                    if(brown < 1)
                    {
                        color_brown = Object::create("drawing_4.png", color_scene2, 300, 73);
                        brown++;
                    }
                    break;
                case 1:
                    if(red < 1)
                    {
                        color_red = Object::create("drawing_1.png", color_scene2, 300, 73);
                        red++;
                    }
                    break;
                case 0:
                    if(ivory < 1)
                    {
                        color_ivory = Object::create("drawing_2.png", color_scene2, 300, 73);
                        ivory++;
                    }
                    break;
                default:
                    break;
            }
            if(coloring_check_clear()==true)
            {
                //게임 클리어!
                blue = 0;
                white = 0;
                yellow = 0;
                brown = 0;
                red = 0;
                ivory = 0;//값 초기화
                color_end = Scene::create("scene_end", "color_end.png");
                ObjectPtr color_endGame = Object::create("color_endButton.png", color_end, 880, 200);
                color_endGame->setScale(0.25);
                color_endGame->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool{
                    
                    //여기가 게임 끝입니다. 맨위에 전역변수 선언해주고 mainScene -> enter(); 하면 될거에여
                    endGame();
                    //mainScene->enter();
                    return true;
                });
                color_end->enter();
            }
            return true;
        });
    }
    
    color_drawing_base = Object::create("drawing_0.png", color_scene2, 300, 73);
    color_howto = Object::create("color_howto.png", color_scene2, 0, 0);
    color_howto->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool{
        color_howto->hide();
        return true;
    });
    
    
    for(int i = 6; i >= 0; i--)
    {
        char buf[30];
        sprintf(buf, "color_story%d.png", i);
        color_story[i] = Object::create(buf, color_scene2, 0, 0);
        color_story[i]->setOnMouseCallback([&, i](ObjectPtr object, int x, int y, MouseAction action)->bool{
            color_story[i]->hide();
            return true;
        });
    }
    
    
    color_startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
        color_scene2->enter();
        
        return true;
    });
    color_endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
        
        //게임 취소 엔드게임
        endGame();
        return true;
    });
    
    return color_scene1;
}

int main() {
    
    
    //게임옵션설정
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    
    //게임시작
    startGame(coloring_game_init());
    
    return 0;
}
