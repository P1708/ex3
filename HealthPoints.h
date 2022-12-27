//
// Created by ahmad.fadool on 12/21/22.
//

#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H
#include <iostream>

static const int ZERO_HP=0;

class HealthPoints {
public:
    class InvalidArgument {};
    /*
     *C'tor of HealthPoints class
     * @parm maxHp - the maximum health points possible for an instance of class Healthpoints
     *      maxHp is 100 by default
     *@return
     *      a new instance of Healthpoints
    */
    HealthPoints(int maxHp=100);

    /*
     * Copy-C'tor for HealthPoints class
     *
    */
    HealthPoints(const HealthPoints&)=default;

    /*
     * assignment operator for HealthPoints class
     *
    */
    HealthPoints& operator=(const HealthPoints&)=default;

    /*
     *default destructor for HealthPoints Class
     *
    */
    ~HealthPoints()=default;

    /*
     *addition operator for HealthPoints
     * @parm healthPoint - the HealthPoints instance that we want to add
     *      @parm change to its hp field
     *works in the following order "change + healthPoint"
     * healthPoint.hp is <= healthPoint.maxHp
     *@return - a new instance of HealthPoints with the same @parm healthPoint maxHp
     *      and with hp= change + healthPoint.hp
    */
    friend HealthPoints operator+(int change , const HealthPoints& healthPoint);

    /*
     *addition operator for HealthPoints
     * healthPoint=(*this)
     * @parm healthPoint is the HealthPoints instance that we want to add
     *      @parm change to its hp field
     *works in the following order "healthPoint + change"
     *@return a new instance of HealthPoints with the same @parm healthPoint maxHp
     *      and with hp= change + healthPoint.hp
    */
    HealthPoints operator+(int change);

    /*
     *subtraction operator for HealthPoints
     * @parm healthPoint - the HealthPoints instance that we want to subtract
     *      @parm change from its hp field
     *works in the following order "healthPoint - change"
     * healthPoint.hp is >= 0
     *@return - a new instance of HealthPoints with the same @parm healthPoint maxHp
     *      and with hp=healthPoint.hp - change
    */
    HealthPoints operator-(int change);
    /*
     *print operator for HealthPoints Class
     * @parm ostream& - where we want to print
     *      @parm HealthPoints& data
     *  HealthPoints hp(150);
     *  hp -= 50 ;
     *  cout<<hp;
     *  100(150) //what is printed on std::cout
    */
    friend std::ostream& operator<<(std::ostream& , const HealthPoints&);

    /*
     *addition assignment operator for HealthPoints Class
     * @parm change - the amount we want to add to this->hp
     * this->hp is <= this->maxHp
     *
     * @return - a reference for (*this) in order to support a chain of operators
    */
    HealthPoints& operator+=(int change);

    /*
     *subtraction assignment operator for HealthPoints Class
     * @parm change - the amount we want to subtract from this->hp
     * this->hp is >= this->maxHp
     *
     * @return - a reference for (*this) in order to support a chain of operators
    */
    HealthPoints& operator-=(int change);

    /*
     *Equal-to operator for HealthPoints Class
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp==hp.hp
     *         - false if this->hp!=hp.hp
    */
    bool operator==(const HealthPoints& hp) const;
    /*
     *Not-equal-to operator for HealthPoints Class
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp!=hp.hp
     *         - false if this->hp==hp.hp
    */
    bool operator!=(const HealthPoints& hp) const;


    /*
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp < hp.hp
     *         - false if this->hp >= hp.hp
    */
    bool operator<(const HealthPoints&) const;

    /*
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp > hp.hp
     *         - false if this->hp <= hp.hp
    */
    bool operator>(const HealthPoints&) const;

    /*
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp <= hp.hp
     *         - false if this->hp > hp.hp
    */
    bool operator<=(const HealthPoints&) const;

    /*
     * @parm hp - what we are comparing to (*this)
     *
     * @return - true if this->hp >= hp.hp
     *         - false if this->hp < hp.hp
    */
    bool operator>=(const HealthPoints&) const;




private:
    int hp; //current HealthPoints instance health-points
    int maxHp;

};




#endif //EX3_HEALTHPOINTS_H
