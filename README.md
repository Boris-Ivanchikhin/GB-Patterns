#### Course: GOF Design Patterns  
#### Lesson 05.  Patterns: Facade, Visitor and Observer  

***

1. Применение паттерна «<b>Посетитель</b>» (<b>Visitor</b>).  

   Сделать логирование динамических объектов с помощью паттерна «Посетитель».

2. Применение паттерна «<b>Наблюдатель</b>» (<b>Observer</b>).  

   <b>Задача</b>: Сделать бомбы Observable объектом с функцией <b>AddObserver</b>, у которой есть наблюдатели — массив объектов, которые можно разрушать. А наблюдатели имеют функцию <b>HandleInsideCheck</b>. При пересечении бомбы с землёй будет вызываться функция:  

    > pBomb->CheckDestoyableObjects();  

   В которой в цикле для всех наблюдателей вызывается функция-событие <b>HandleInsideCheck</b>. Если проверка вернула true, то возвращаем указатель на этот <b>DestroyableGroundObject</b> в класс <b>SBomber</b> для подсчёта очков за уничтожение объекта и удаление объекта из массива статических объектов. Если ни один объект не был уничтожен, пусть возвращается <b>nullptr</b>.
То есть необходимо переделать функцию:  
   ```C++
    void SBomber::CheckDestoyableObjects(Bomb * pBomb)
    {
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
        {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
            {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
            }
        }
    }
   ```  
   Перенеся эту функциональность в класс Bomb. А также нужно изменить следующую функцию, откуда будет вызываться вышестоящая функция:  
    ```C++
    void SBomber::CheckBombsAndGround()
    {
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
        {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
            {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
            }
        }
    }
   ```  
