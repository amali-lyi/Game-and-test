#include <iostream>
#include <string>

using namespace std;

class Character
{
private:
    string name;
    float health;
    float max_health;
    bool is_dead;

    void UpdateIsDead()
    {
        this->is_dead = getHealth() <= 0;

        if (is_dead)
        {
            cout << this->name << " has died!" << endl;
        }
    }

public:
    Character(string name, float health)
    {
        this->name = name;
        this->health = health;
        this->max_health = health;
        UpdateIsDead();
    }

    void getInfo()
    {
        cout << "Name: " << name
            << "; Health: " << health << "/" << max_health << ";\n";
    }

    float getHealth()
    {
        return health;
    }

    string getName()
    {
        return name;
    }

    bool isDead()
    {
        return is_dead;
    }

    void setHealth(float health)
    {
        this->health = health;

        if (health < 0)
        {
            this->health = 0;
        }

        if (health > max_health)
        {
            this->health = max_health;
        }

        UpdateIsDead();
    }

    void heal(float heal)
    {
        setHealth(getHealth() + heal);
    }

    void damage(float damage)
    {
        setHealth(getHealth() - damage);
    }
};

class Warrior : public Character
{
private:
    float strength;

public:
    Warrior(string name, float health, float strength)
        : Character(name, health)
    {
        this->strength = strength;
    }

    void attack(Character* victim)
    {
        victim->damage(strength);
    }

    float getDamage()
    {
        return strength;
    }

    void getInfo()
    {
        cout << "Name: " << getName()
            << "; Health: " << getHealth()
            << "; Strength: " << getDamage() << ";\n";
    }
};

class Zealot : public Character
{
private:
    float mana;

public:
    Zealot(string name, float health, float mana)
        : Character(name, health)
    {
        this->mana = mana;
    }

    void heal(Character* target, float heal)
    {
        if (heal > mana)
        {
            cout << "Not enough mana!" << endl;
            return;
        }

        target->heal(heal);
        this->mana -= heal;
    }

    float getMana()
    {
        return mana;
    }

    void getInfo()
    {
        cout << "Name: " << getName()
            << "; Health: " << getHealth()
            << "; Mana: " << getMana() << ";\n";
    }
};

class Necromancer : public Zealot
{
public:
    Necromancer(string name, float health, float mana)
        : Zealot(name, health, mana) {
    }

    void revive(Character* target)
    {
        if (!target->isDead())
        {
            cout << target->getName() << " is not dead!\n";
            return;
        }

        float reviveHealth = 10;
        target->setHealth(reviveHealth);

        cout << target->getName() << " has been revived with "
            << reviveHealth << " HP!\n";
    }
};

class Thief : public Warrior
{
public:
    Thief(string name, float health, float strength)
        : Warrior(name, health, strength) {
    }

    void stealLife(Character* target)
    {
        float damage = getDamage()/2;

        target->damage(damage);
        this->heal(damage);

        cout << getName() << " stole" << damage
            << " HP from " << target->getName() << "!\n";
    }
};

int main()
{
    Warrior w1("uno", 100, 150);
    Warrior w2("dos", 100, 30);
    Zealot zealot1("tres", 100, 10);
    Necromancer necro("necro", 100, 50);
    Thief thief("thief", 100, 40);

    cout << "initial state:\n";
    w1.getInfo();
    w2.getInfo();
    zealot1.getInfo();
    cout << "--------------------\n";

    w1.attack(&w2);
    w1.attack(&w2);

    cout << "after killing w2:\n";
    w2.getInfo();
    cout << "--------------------\n";
    necro.revive(&w2);

    cout << "after revive:\n";
    w2.getInfo();
    cout << "--------------------\n";
    thief.stealLife(&w1);

    cout << "after life steal:\n";
    w1.getInfo();
    thief.getInfo();
    cout << "--------------------\n";
    zealot1.heal(&w1, 5);

    cout << "after healing:\n";
    w1.getInfo();
    zealot1.getInfo();

    return 0;
}