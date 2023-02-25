#### Course: GOF Design Patterns  
#### Lesson  08. Patterns: State and Prototype  

***

1. Применение паттерна «<b>Прототип</b>»(<b>Prototype</b>).  

   <b>Задача</b>: Применить паттерн «<b>Прототип</b>» в проекте <b>SBomber</b> для клонирования в runtime бомб.  
   Если у самолета есть доступные бомбы, по нажатию клавиши ‘d’ бросать бомбу и клонировать её с немного смещенными по х координатами. Клонирование реализовать в классе Bomb.  

2. (*)Анимированный скроллинг.  

   <b>Задача</b>: добавить в конец игры анимированную прокрутку титров со списком создателей.  
   Предположим, проект <b>SBomber</b> создан группой разработчиков и дизайнеров. Любое нажатие на клавиатуре прервёт прокрутку титров.  
   Как и в самой игре, воспользуемся готовыми функциями:  

    > TimeStart();  
    > MyTools::ClrScr();  
    > MyTools::GotoXY(x, y);  
    > TimeFinish();  

   Сделаем так, чтобы скорость анимации прокрутки зависела от времени, потраченного на рисование одного кадра. Список фамилий можно сделать константным массивом char строк <b>ppScroll</b>:  
   ```C++
    static const size_t ScrollHeight = 30;
    static const size_t ScrollWidth  = 30;
    static const char* ppScroll[ScrollHeight] =
            {"                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "     Project manager:         ",
             "         Ivan Vasilevich      ",
             "                              ",
             "     Developers:              ",
             "         Nikolay Gavrilov     ",
             "         Dmitriy Sidelnikov   ",
             "         Eva Brown            ",
             "                              ",
             "     Designers:               ",
             "         Anna Pachenkova      ",
             "         Elena Shvaiber       ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              ",
             "                              "};


    void SBomber::AnimateScrolling()
    {
        WriteToLog(string(__FUNCTION__) + " was invoked");
        const size_t windowHeight = 10; // Размер окна для скроллинга
        const size_t startX = MyTools::GetMaxX() / 2 - ScrollWidth / 2;
        const size_t startY = MyTools::GetMaxY() / 2 - windowHeight / 2;
        double curPos = 0;
        do {
            TimeStart();
            MyTools::ClrScr();

            // вывод windowHeight строк из ppScroll используя смещение curPos
            // ...

            MyTools::GotoXY(0, 0);
            TimeFinish();
            curPos += deltaTime * 0.0015;

        } while (!_kbhit() && int(curPos) <= (ScrollHeight - windowHeight));
        MyTools::ClrScr();
    }
   ```  
   Закончите этот алгоритм. Функция <b>AnimateScrolling()</b> должна вызываться из <b>main</b> после основного цикла игры:  
   ```C++
            // ...
            game.DrawFrame();
            game.MoveObjects();
            game.CheckObjects();
            game.TimeFinish();

        } while (!game.GetExitFlag());
        game.AnimateScrolling(); // Вызов анимированного скроллинга
        MyTools::CloseLogFile();

        return 0;
    }
   ```  
***

#### Глоссарий  

   - «<b>Состояние</b>» (англ. <b>State</b>) — поведенческий шаблон проектирования. Позволяет объекту во время выполнения программы менять своё поведение в зависимости от своего состояния. Для пользователей объекта это выглядит так, будто класс объекта изменился.  
   - «<b>Прототип</b>» (англ. <b>Prototype</b>) — порождающий паттерн проектирования, который позволяет клонировать объекты, абстрагируясь от подробностей их реализации.  



