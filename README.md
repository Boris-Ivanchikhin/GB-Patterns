#### Course: GOF Design Patterns  
#### Lesson 03.  Patterns: Strategy, Iterator, Adapter  

***

1. Применить шаблон «<b>Итератор</b>» в игре <b>SBomber</b>.  

   C помощью паттерна «Итератор» искать и обходить всех бомбы в массиве динамических объектов. В классе SBomber есть функция FindAllBombs::  
   ```C++
    vector<Bomb*> SBomber::FindAllBombs() const
    {
        vector<Bomb*> vecBombs;
        for (size_t i = 0; i < vecDynamicObj.size(); i++)
        {
            Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
            if (pBomb != nullptr)
            {
                vecBombs.push_back(pBomb);
            }
        }
    
        return vecBombs;
    }
   ```  
   Можно для неё использовать паттерн «Итератор» и вынести сам алгоритм поиска бомб в массиве динамических объектов. Назвать класс можно BombIterator. Также можно добавить в класс SBomber функции begin и end, которые будут использоваться в FindAllBombs.
Возвращение массива бомб можно оставить, как в функции SBomber::CheckBombsAndGround(). Если бомба пересекла линию земли, она удаляется из массива динамических объектов, что может нарушить работу итератора по этому же массиву.  
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
   Нужно либо сделать итератор устойчивым к таким удалениям, чтобы не создавать массив с указателями на бомбы. Либо, что проще, — оставить текущую реализацию функции FindAllBombs и вынести поиск бомб в класс итератора.  

2. (*)Применить шаблон <b>«Адаптер»</b>.  

   <b>Задача</b>: адаптировать несовместимый по интерфейсам класс в игре SBomber с помощью паттерна «Адаптер».
Посмотрим на диаграмму классов проекта SBomber. Обратим внимание на классы: GameObject, DestroyableGroundObject и Tank. Допустим, класс Tank был реализован независимо от нашего проекта SBomber, имеет несовместимый интерфейс и название TankAdaptee. Перенесём в него всю функциональность из класса GameObject и добавим другие интерфейсные функции: isInRange и Paint вместо isInside и Draw.  
   ```C++
    class TankAdaptee
    {
    public:
    
        TankAdaptee() : x(0.0), y(0.0), width(0) { }
    
        void Paint();
        bool __fastcall isInRange(double x1, double x2) const;
    
        inline uint16_t GetScore() const { return score; }
        
        inline void SetPos(double nx, double ny) { x = nx; y = ny; }
        inline double GetY() const { return y; }
        inline double GetX() const { return x; }
    
        inline void SetWidth(uint16_t widthN) { width = widthN; }
        inline uint16_t GetWidth() const { return width; }

    protected:
    
        double x, y;
        uint16_t width;
        const uint16_t score = 30;
    };
   ```  
   Для использования в нашей игре класс нужно адаптировать, не изменяя его. Создадим для него класс-обёртку TankAdapter — наследник класса DestroyableGroundObject, который должен содержать экземпляр tank класса TankAdaptee.  
   Также в GameObject сделаем виртуальными следующие функции:  
   ```C++
    void SetPos(double nx, double ny) { x = nx; y = ny; }
    double GetY() const { return y; }
    double GetX() const { return x; }
    void SetWidth(uint16_t widthN) { width = widthN; }
    uint16_t GetWidth() const { return width; }   ```
   ```  
   Переопределим их в «Адаптере», чтобы они взаимодействовали с теми же функциями адаптируемого класса TankAdaptee. Например:  
   ```C++
    void TankAdapter::SetPos(double nx, double ny)  
    {  
        tank.SetPos(nx, ny);
    }
    
    uint16_t TankAdapter::GetWidth() const  
    {  
        return tank.GetWidth();  
    }
    
    void TankAdapter::Draw() const  
    {  
        tank.Paint();  
    };
    
    bool __fastcall TankAdapter::isInside(double x1, double x2) const  
    {
        tank.isInRange(x1, x2);  
    };
   ```  
   Нам нужно полностью обернуть объект класса TankAdaptee и адаптировать его, не ломая уже реализованное поведение танков в игре.  
   Танки для нашего уровня — объекты класса TankAdapter — мы будем создавать в конструкторе класса SBomber. И они будут корректно работать, потому что включены в нашу иерархию классов, где есть совместимый интерфейс с поддержкой полиморфизма.