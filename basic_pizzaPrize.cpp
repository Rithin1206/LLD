
// Run in leetcode playground

class AbstarctSize{
    public:
        int radius;
        string name;
        int multiplier;
    AbstarctSize(){
        
    }
    virtual int getMultiplier()=0;
};

class SmallSize : public AbstarctSize{
    public:
    
    SmallSize(){
        this->radius = 10;
        this->name ="small";
        this->multiplier = 1;
    }
    
    int getMultiplier() override{
        return this->multiplier;
    }
};

class LargeSize : public AbstarctSize{
    public:
    
    LargeSize(){
        this->radius = 14;
        this->name ="large";
        this->multiplier = 3;
    }
    
    int getMultiplier() override{
        return this->multiplier;
    }
};

class AbstractBase{
    public:
    int price;
    string name;
    
    AbstractBase(){}
    
    virtual int getPrice() =0;
};

class CheeseBase : public AbstractBase{
    public:
    CheeseBase(){
        this->name = "cheese";
        this->price = 20;
    }
    
    int getPrice() override{
        return this->price;
    }
    
};

class DoughBase : public AbstractBase{
    public:
    DoughBase(){
        this->name = "dough";
        this->price = 20;
    }
    
    int getPrice() override{
        return this->price;
    }
    
};

class AbstractTopping{
  public:
    string name;
    int price;
    
    AbstractTopping(){
        
    }
    
    virtual int getPrice() =0;
};

class ChickenTopping : public AbstractTopping{
    public:
     ChickenTopping(){
         this->price = 20;
         this->name = "chicken topping";
     }
    
    int getPrice() override{
        return this->price;
    }
};

class MushroomTopping : public AbstractTopping{
    public:
     MushroomTopping(){
         this->price = 15;
         this->name = "mushroom topping";
     }
    
    int getPrice() override{
        return this->price;
    }
};

class CheeseTopping : public AbstractTopping{
    public:
     CheeseTopping(){
         this->price = 10;
         this->name = "cheese topping";
     }
    
    int getPrice() override{
        return this->price;
    }
};


class Pizza{
    private:
        AbstarctSize* size;
        vector<AbstractTopping*> toppings;
        AbstractBase* base;
    public:
        Pizza(AbstarctSize* _size, vector<AbstractTopping*> _toppings, AbstractBase* _base){
            this->size = _size;
            this->base = _base;
            this->toppings = _toppings;
        }
    int getPrice(){
        int total_price =0;

        total_price += base->getPrice();
        for(auto &t: toppings){
            total_price += t->getPrice();
        }
        
        total_price = total_price* this->size->getMultiplier();
        return total_price;
    }
};


int main() {
    vector<AbstractTopping* > toppings ={new ChickenTopping(), new CheeseTopping(), new MushroomTopping()};
    AbstractBase* b= new DoughBase();
    Pizza* p = new Pizza(new LargeSize(), toppings, b);
    cout<< p->getPrice();
}