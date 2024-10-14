
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

class Pizza;
class AbstractPriceCalculator{
    public:
    virtual int calculatePrice(Pizza* p) =0;
};

class Pizza{

    public:
        AbstarctSize* size;
        vector<AbstractTopping*> toppings;
        AbstractBase* base;
        AbstractPriceCalculator* calc;
        Pizza(AbstarctSize* _size, vector<AbstractTopping*> _toppings, AbstractBase* _base){
            this->size = _size;
            this->base = _base;
            this->toppings = _toppings;
        }
    
    Pizza(){}
    
    void setSize(AbstarctSize* _size){
        this->size = _size;
    }
    void addTopping(AbstractTopping* _topping){
        this->toppings.push_back(_topping);
    }
    void setBase(AbstractBase* _base){
        this->base = _base;
    }
    
    void setPriceCalculator(AbstractPriceCalculator* _calc){
        this->calc = _calc;
    }
    
    int getPrice(){
        return this->calc->calculatePrice(this);
    }
};

class SimplePriceCalculator : public AbstractPriceCalculator{
    public:
    int calculatePrice(Pizza* p) override{
        int total_price =0;

        total_price += p->base->getPrice();
        for(auto &t: p->toppings){
            total_price += t->getPrice();
        }
        
        total_price = total_price* p->size->getMultiplier();
        return total_price;
    }
};

class PizzaBuilder{
    private:
        Pizza* p = new Pizza();
    public:
    
    PizzaBuilder* setSize(AbstarctSize* _size){
        this->p->setSize(_size);
        return this;
    }
    
    PizzaBuilder* setBase(AbstractBase* _base){
        this->p->setBase(_base);
        return this;
    }   
    
    PizzaBuilder* addTopping(AbstractTopping* _topping){
        this->p->addTopping(_topping);
        return this;
    }
    
    PizzaBuilder* setPriceCalculator(AbstractPriceCalculator* _calc){
        this->p->setPriceCalculator(_calc);
        return this;
    }
    
    Pizza* build(){
        return p;
    }
    
};

int main() {
    PizzaBuilder* pb = new PizzaBuilder();
    Pizza* p = pb->setSize(new LargeSize())
                ->setBase(new DoughBase())
                ->addTopping(new ChickenTopping())
                ->addTopping(new MushroomTopping())
                ->addTopping(new CheeseTopping())
                ->setPriceCalculator(new SimplePriceCalculator)
                ->build();        
    cout<< p->getPrice();
}